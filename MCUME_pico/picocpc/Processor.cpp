#include "Processor.h"
#include "Bus.h"

bool Processor::step()
{
    bool interruptAcknowledged = false;
    _pins = z80_tick(&_cpu, _pins);
    if (_pins & Z80_MREQ)
    {
        const uint16_t addr = Z80_GET_ADDR(_pins);
        if (_pins & Z80_RD)
        {
            uint8_t data = readZ80(addr);
            Z80_SET_DATA(_pins, data);
        }
        else if (_pins & Z80_WR)
        {
            uint8_t data = Z80_GET_DATA(_pins);
            writeZ80(addr, data);
        }
    }
    else if (_pins & Z80_IORQ)
    {
        const uint16_t port = Z80_GET_ADDR(_pins);
        if (_pins & Z80_M1)
        {
            // an interrupt acknowledge cycle, depending on the emulated system,
            // put either an instruction byte, or an interrupt vector on the data bus
            Z80_SET_DATA(_pins, 0x0038);
            interruptAcknowledged = true;
        }
        else if (_pins & Z80_RD)
        {
            // handle IO input request at port
            inZ80(port);
        }
        else if (_pins & Z80_WR)
        {
            // handle IO output request at port
            uint8_t data = Z80_GET_DATA(_pins);
            outZ80(port, data);
        }
    }

    return interruptAcknowledged;
}

uint8_t Processor::readZ80(uint16_t addr)
{
    return _bus->readMemory(addr);
}

void Processor::writeZ80(uint16_t addr, uint8_t value)
{
    _bus->writeMemory(addr, value);
}

void Processor::outZ80(uint16_t port, uint8_t value)
{
    if(!(port & 0x8000)) _bus->writeGA(value);           // The Gate Array is selected when bit 15 is set to 0.
    if(!(port & 0x4000)) _bus->writeCRTC(port, value); // The CRTC is selected when bit 14 is set to 0.
}

uint8_t Processor::inZ80(uint16_t port)
{
    if(!(port & 0x4000)) return _bus->readCRTC(port); // The CRTC is selected when bit 14 is set to 0.

    // TODO default return value
    return 0;
}

void Processor::assertWait()
{
    _pins = _pins | Z80_WAIT;
}

void Processor::clearWait()
{
    _pins = _pins & ~Z80_WAIT;
}

void Processor::requestInterrupt()
{
    _pins = _pins | Z80_INT;
}

void Processor::acknowledgeInterrupt()
{
    _pins = _pins & ~Z80_INT;
}


