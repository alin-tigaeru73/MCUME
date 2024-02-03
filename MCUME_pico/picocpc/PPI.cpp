#include "Bus.h"
#include "PPI.h"

void PPI::PPI::writePortA(const uint8_t value) {
    if(_portA.direction == Direction::OUTPUT) {
        _portA.value = value;
    }
}

uint8_t PPI::PPI::readPortA() const {
    if(_portA.direction == Direction::INPUT) {
        return _portA.value;
    }
    return 0;
}

uint8_t PPI::PPI::readPortB() {
    if(_portB.direction == Direction::INPUT) {
        _portB.value = (0x07 << 1) | (0x01 << 4);

        if(_bus->isVSyncActive()) {
            _portB.value |= 0x01;
        }

        return _portB.value;
    }
    return 0;
}

void PPI::PPI::writePortC(const uint8_t value) {
    if(_portC.direction == Direction::OUTPUT) {
        const uint8_t firstFourBits = value & 0x0F;
        const auto bitSeven = (value & 0x80) != 0;
        const auto bitSix = (value & 0x40) != 0;
        if(bitSix && !bitSeven) {
            // Read from selected PSG register.
            _portA.direction = Direction::OUTPUT;
            writePortA(_bus->readPSG(firstFourBits));
            _portA.direction = Direction::INPUT;
        } else if(bitSeven && !bitSix) {
            // Write to selected PSG register.
            _bus->writePSG(_portA.value);
        } else if(bitSix && bitSeven) {
            // Select PSG register.
            _bus->selectPSGRegister(_portA.value);
        }
    }
}

void PPI::PPI::writeControl(const uint8_t value) {
    if(const auto bitSeven = (value & 0x80) != 0) {
        if(const auto bitFour = (value & 0x10) != 0) {
            _portA.direction = Direction::INPUT;
        } else {
            _portA.direction = Direction::OUTPUT;
        }
    } else {
        const uint8_t bitToModify = (value & 0xF) >> 1;
        const uint8_t newValue = value & 0x1;
        _portC.value = (_portC.value & ~(1 << bitToModify)) | (newValue << bitToModify);
    }
}







