#include <vector>

#include "pico.h"
#include "GA.h"
#include "Bus.h"

bool GateArray::updateInterrupts()
{
    auto interruptGenerated = false;
    if(_currentHSync && !_bus->isHSyncActive())
    {
        // falling edge of CRTC hsync signal.
        _interruptCounter++;
        _delayVSyncCounter++;

        if(_interruptCounter == 52)
        {
            //printf("Interrupt generated! \n");
            _interruptCounter = 0;
            interruptGenerated = true;
        }
    }

    if(!_currentVSync && _bus->isVSyncActive())
    {
        // A VSYNC triggers a delay action of 2 HSYNCs in the GA, at the
        // completion of which the scan line count in the GA is compared to 32.
        _delayVSyncCounter = 0;
    }

    if(_delayVSyncCounter == 2)
    {
        interruptGenerated = _interruptCounter < 32;
        _interruptCounter = 0;
    }

    return interruptGenerated;
}

void GateArray::generatePixelData() const
{
    if(!_currentHSync && _bus->isHSyncActive())
    {
        _bus->setHSyncWait(false);
    }

    if(!_currentVSync && _bus->isVSyncActive())
    {
        _bus->setVSyncWait(false);
    }

    if(!_bus->isWithinDisplay())
    {
        return;
    }

    for(int i = 0; i < 2; i++)
    {
        const uint16_t address = _bus->getVideoAddress() + i;
        const uint8_t encodedByte = _bus->readMemory(address);
        std::vector<uint8_t> pixels;
        switch(_screenMode)
        {
            case 0:
                pixels.push_back((encodedByte & 0x80) >> 7 |
                                    (encodedByte & 0x08) >> 2 |
                                    (encodedByte & 0x20) >> 3 |
                                    (encodedByte & 0x02) << 2);
                pixels.push_back((encodedByte & 0x40) >> 6 |
                                    (encodedByte & 0x04) >> 1 |
                                    (encodedByte & 0x10) >> 2 |
                                    (encodedByte & 0x01) << 3);
                break;
            case 1:
                pixels.push_back((encodedByte & 0x80) >> 7 |
                                    (encodedByte & 0x08) >> 2);
                pixels.push_back((encodedByte & 0x40) >> 6 |
                                    (encodedByte & 0x04) >> 1);
                pixels.push_back((encodedByte & 0x02) |
                                    (encodedByte & 0x20) >> 5);
                pixels.push_back((encodedByte & 0x10) >> 4 |
                                    (encodedByte & 0x01) << 1);
                break;
            case 2:
                for (uint8_t color = 0; color < 8; color++)
                {
                    pixels.push_back((encodedByte >> (7 - color)) & 1);
                }
                break;
        }

        for(const auto& pixel : pixels)
        {
            _bus->draw(_penColours[pixel]);
        }
    }
}

bool GateArray::step()
{
    _waitSignal = _microsecondCounter == 1;

    if(_microsecondCounter == 3)
    {
        const auto interruptGenerated = updateInterrupts();
        generatePixelData();

        _currentHSync = _bus->isHSyncActive();
        _currentVSync = _bus->isVSyncActive();
        _microsecondCounter = (_microsecondCounter + 1) % 4;
        return interruptGenerated;
    }
    _microsecondCounter = (_microsecondCounter + 1) % 4;
    return false;
}

void GateArray::selectPen(const uint8_t value)
{
    switch(value >> 4)
    {
        case 0b01:
            // Select border.
            _penSelected = 0x10;
            break;
        case 0b00:
            // Bits 0-3 dictate the pen number
            _penSelected = value & 15;
            break;
    }
}

void GateArray::selectPenColour(const uint8_t value) const
{
    // Bits 0-4 of "value" specify the hardware colour number from the hardware colour palette.
    // (i.e. which index into the Palette array of structs.)
    _penColours[_penSelected] = value & 31;
}

void GateArray::manageRomScreenInterrupt(const uint8_t value)
{
    if(_currentHSync && !_bus->isHSyncActive())
    {
        // Screen mode change, dictated by the least significant 2 bits of "value".
        // Effective at next scanline.
        _screenMode = value & 3;
    }


    // ROM enable/disable flags.
    _lowRomEnabled = ((value >> 2) & 0b1) == false;
    _highRomEnabled = ((value >> 3) & 0b1) == false;

    // Interrupt delay control.
    if ((value >> 4) & 0b1) _interruptCounter = 0;
}

/** Bit 7   Bit 6    Function
 *  --0--   --0--    Select pen
 *  --0--   --1--    Select colour of the selected pen
 *  --1--   --0--    Select screen mode, ROM configuration and interrupt control
 *  --1--   --1--    RAM management
*/
void GateArray::write(const uint8_t value)
{
    switch(value >> 6)
    {
        case 0b00:
            selectPen(value);
            break;
        case 0b01:
            selectPenColour(value);
            break;
        case 0b10:
            manageRomScreenInterrupt(value);
            break;
        case 0b11:
            // This would be RAM banking, but it is not available on the CPC464.
            break;
    }
}

bool GateArray::getWaitSignal() const
{
    return _waitSignal;
}

void GateArray::clearInterruptCounter()
{
    _interruptCounter &= 0x1f;
}

bool GateArray::getLowRomStatus() const
{
    return _lowRomEnabled;
}

bool GateArray::getHighRomStatus() const
{
    return _highRomEnabled;
}
