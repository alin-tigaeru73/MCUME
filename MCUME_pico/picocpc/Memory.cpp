#include "Memory.h"
#include "Bus.h"

#define LOWER_ROM_END   0x4000
#define UPPER_ROM_BEGIN 0xC000

#include "roms/rom464.h"

uint8_t Memory::read(const uint16_t addr) const {

    if(addr <= LOWER_ROM_END && _bus->isLowRomEnabled()) {
//        return _lowerRom[addr];
        return gb_rom_464_0[addr];
    }

    if(addr >= UPPER_ROM_BEGIN && _bus->isHighRomEnabled()) {
//        return _upperRom[addr - UPPER_ROM_BEGIN];
        return gb_rom_464_1[addr - UPPER_ROM_BEGIN];
    }

    return _ram[addr];
}

void Memory::write(const uint16_t addr, const uint8_t value) {
    _ram[addr] = value;
}

void Memory::initialiseLowRom() {
    ROMLoader::load(_lowerRom, "os_464.rom");
}

void Memory::initialiseUpperRom() {
    ROMLoader::load(_upperRom, "basic_1.0.rom");
}
