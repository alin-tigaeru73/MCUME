#include "GA.h"
#include "Bus.h"

bool GateArray::updateInterrupts() {
    auto interruptGenerated = false;
    if(!_currentHSync && _bus->isHSyncActive()) {
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

    if(_bus->isVSyncActive() && !_currentVSync) {
        // A VSYNC triggers a delay action of 2 HSYNCs in the GA, at the
        // completion of which the scan line count in the GA is compared to 32.
        _delayVSyncCounter = 0;
    }

    if(_delayVSyncCounter == 2) {
        interruptGenerated = _interruptCounter < 32;
        _interruptCounter = 0;
    }

    return interruptGenerated;
}

void GateArray::generatePixelData() {
    if(!_bus->isHSyncActive() && _currentHSync) {
        _bus->drawScanline();
        return;
    }

    if(!_bus->isVSyncActive() && _currentVSync) {
        _bus->drawVSync();
        return;
    }

    for(int i = 0; i < 2 && _bus->isWithinDisplay(); ++i) {
        const uint8_t encodedByte = _bus->readMemory(_bus->getVideoAddress() + i);
        switch(_screenMode) {
            case 0:
                _pixelBuffer->at(0) = ((encodedByte & 0x80) >> 7 |
                                    (encodedByte & 0x08) >> 2 |
                                    (encodedByte & 0x20) >> 3 |
                                    (encodedByte & 0x02) << 2);
                _pixelBuffer->at(1) = ((encodedByte & 0x40) >> 6 |
                                    (encodedByte & 0x04) >> 1 |
                                    (encodedByte & 0x10) >> 2 |
                                    (encodedByte & 0x01) << 3);

                for(int j = 0; j < 2; ++j) {

                    _bus->draw(_penColours[_pixelBuffer->at(j)]);
                }

                break;
            case 1:
                _pixelBuffer->at(0) = ((encodedByte & 0x80) >> 7 |
                                 (encodedByte & 0x08) >> 2);
                _pixelBuffer->at(1) = ((encodedByte & 0x40) >> 6 |
                                 (encodedByte & 0x04) >> 1);
                _pixelBuffer->at(2) = ((encodedByte & 0x02) |
                                 (encodedByte & 0x20) >> 5);
                _pixelBuffer->at(3) = ((encodedByte & 0x10) >> 4 |
                                 (encodedByte & 0x01) << 1);

                for(int j = 0; j < 4; ++j) {
                    _bus->draw(_penColours[_pixelBuffer->at(j)]);
                }

                break;
            case 2:
                for (uint8_t color = 0; color < 8; ++color) {
                    _pixelBuffer->at(color) = (encodedByte >> (7 - color)) & 1;
                    _bus->draw(_penColours[_pixelBuffer->at(color)]);
                }

                break;
        }
    }
}

bool GateArray::step() {
    _waitSignal = _microsecondCounter == 1;
    const auto interruptGenerated = updateInterrupts();
    generatePixelData();
    _currentHSync = _bus->isHSyncActive();
    _currentVSync = _bus->isVSyncActive();
    _microsecondCounter = (_microsecondCounter + 1) % 4;
    return interruptGenerated;
}

void GateArray::selectPen(const uint8_t value) {
    switch(value >> 4) {
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

void GateArray::selectPenColour(const uint8_t value) const {
    // Bits 0-4 of "value" specify the hardware colour number from the hardware colour palette.
    // (i.e. which index into the Palette array of structs.)
    _penColours[_penSelected] = value & 31;
}

void GateArray::manageRomScreenInterrupt(const uint8_t value) {
    if(_currentHSync && !_bus->isHSyncActive()) {
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

void GateArray::write(const uint8_t value) {
    switch(value >> 6) {
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

bool GateArray::getWaitSignal() const {
    return _waitSignal;
}

void GateArray::clearInterruptCounter() {
    _interruptCounter &= 0x1f;
}

bool GateArray::getLowRomStatus() const {
    return _lowRomEnabled;
}

bool GateArray::getHighRomStatus() const {
    return _highRomEnabled;
}
