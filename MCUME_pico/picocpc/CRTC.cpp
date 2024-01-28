#include "CRTC.h"
#include "Bus.h"

bool CRTC::isHSyncActive() const {
    // HSYNC is active if the horizontal counter is in the
    // "horizontal_and_vertical_sync_widths"-defined width starting from the horizontal_sync_position register.
    return _horizontalCounter >= _registers[2] &&
           _horizontalCounter < _registers[2] + (_registers[3] & 0b1111);
}

bool CRTC::isVSyncActive() const {
    const uint8_t charHeight = _registers[9] + 1;
    const auto charLinesCounted = _charLineCounter - _registers[7];
    return charHeight * charLinesCounted >= 0 &&
           charHeight * charLinesCounted <= 16;
}

bool CRTC::isWithinDisplay() const {
    return _horizontalCounter < _registers[1] && _charLineCounter < _registers[6];
}

uint16_t CRTC::generateAddress() const {
    // Video address is created as follows:
    // Bit 0: Always 0
    // Bits 1-10: From bits 0-9 of memoryStartAddr
    // Bits 11-13: Bits 0-2 of _scanlineCounter
    // Bits 14 and 15: Bits 12 and 13 of memoryStartAddr.
    const uint16_t currentMemoryAddr = _memoryStartAddress + (_registers[1] * _charLineCounter) + _horizontalCounter;

    const uint16_t bits0To10 = (currentMemoryAddr & 0b0000001111111111) << 1;
    const uint16_t bits11To13 = (_scanlineCounter & 0b0000000000000111) << 11;
    const uint16_t bits14To15 = (currentMemoryAddr & 0b0011000000000000) << 2;
    return bits14To15 | bits11To13 | bits0To10;
}

void CRTC::step() {
    if(_microsecondCounter == 3) {
        ++_horizontalCounter;

        if(_horizontalCounter >= _registers[0]) {
            // horizontal counter is equal to the Horizontal Total Register.
            _horizontalCounter = 0;
            ++_scanlineCounter;
        }

        if(_scanlineCounter >= _registers[9]) {
            // The counter for Maximum Raster Address is equal to it.
            // The height of a character is 8 rasters, so when we reach 8 rasters we increment the char line count.
            _scanlineCounter = 0;
            ++_charLineCounter;
        }

        if(_charLineCounter >= _registers[4]) {
            // The vertical counter reaches the Vertical Total register.
            _charLineCounter = 0;
        }

        if(_charLineCounter == 0 && _horizontalCounter == 0)
        {
            _memoryStartAddress = (static_cast<uint16_t>(_registers[12]) << 8) | _registers[13];
        }

    }
    _microsecondCounter = (_microsecondCounter + 1) % 4;
}

void CRTC::write(const uint16_t addr, const uint8_t value) {
    switch(addr & 0xFF00) {
        case 0xBC00: _selectedRegister = value & 0b11111;break;
        case 0xBD00: _registers[_selectedRegister] = value;break;
        default: break;
    }
}

uint8_t CRTC::read(const uint16_t addr) const {
    switch(addr & 0xFF00) {
        case 0xBF00: return _registers[_selectedRegister];
        default: return 0; // TODO should print an error
    }
}
