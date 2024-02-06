#include "Processor.h"
#include "Bus.h"

bool Processor::step() {
    bool interruptAcknowledged = false;
    _pins = z80_tick(&_cpu, _pins);
    if (_pins & Z80_MREQ) {
        const uint16_t addr = Z80_GET_ADDR(_pins);
        if (_pins & Z80_RD) {
            const uint8_t data = readZ80(addr);
            Z80_SET_DATA(_pins, data);
        } else if (_pins & Z80_WR) {
            const uint8_t data = Z80_GET_DATA(_pins);
            writeZ80(addr, data);
        }
    }
    else if (_pins & Z80_IORQ) {
        const uint16_t port = Z80_GET_ADDR(_pins);
        if (_pins & Z80_M1) {
            // an interrupt acknowledge cycle, depending on the emulated system,
            // put either an instruction byte, or an interrupt vector on the data bus
            Z80_SET_DATA(_pins, 0x0038);
            interruptAcknowledged = true;
        } else if (_pins & Z80_RD) {
            // handle IO input request at port
            uint8_t data = inZ80(port);
            Z80_SET_DATA(_pins, data);
        } else if (_pins & Z80_WR) {
            // handle IO output request at port
            const uint8_t data = Z80_GET_DATA(_pins);
            outZ80(port, data);
        }
    }

    return interruptAcknowledged;
}

uint8_t Processor::readZ80(const uint16_t addr) const {
    return _bus->readMemory(addr);
}

void Processor::writeZ80(const uint16_t addr, const uint8_t value) const {
    _bus->writeMemory(addr, value);
}

void Processor::outZ80(const uint16_t port, const uint8_t value) const {
    if(!(port & 0x8000)) _bus->writeGA(value);
    if(!(port & 0x4000)) _bus->writeCRTC(port, value);
    if(!(port & 0x0800)) _bus->writePPI(port, value);
    // if((port & 0xFF00) == 0xDF00) _bus->selectROMNumber(value);
}

uint8_t Processor::inZ80(const uint16_t port) const {
    if(!(port & 0x4000)) return _bus->readCRTC(port);
    if(!(port & 0x0800)) return _bus->readPPI(port);

//     TODO default return value
    return 0;
}

void Processor::assertWait() {
    _pins = _pins | Z80_WAIT;
}

void Processor::clearWait() {
    _pins = _pins & ~Z80_WAIT;
}

// For the USB keyboard.
extern "C" {
#include "tusb.h"
}
void Processor::requestInterrupt() {
    _pins = _pins | Z80_INT;

    tuh_task();
}

void Processor::acknowledgeInterrupt() {
    _pins = _pins & ~Z80_INT;
}


