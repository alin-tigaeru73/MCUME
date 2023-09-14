#include "Memory.h"
#include "Bus.h"

#include "roms/rom464.h" // TODO replace with FileReader

#define LOWER_ROM_END   0x4000
#define UPPER_ROM_BEGIN 0xC000

uint8_t Memory::read(uint16_t addr)
{
    if(addr <= LOWER_ROM_END && _bus->isLowRomEnabled())
    {
        return gb_rom_464_0[addr];
    }
    else if(addr >= UPPER_ROM_BEGIN && _bus->isHighRomEnabled())
    {
        return gb_rom_464_1[addr - UPPER_ROM_BEGIN];
    }
    else
    {
        return _ram[addr];
    }
}

void Memory::write(uint16_t addr, uint8_t value)
{
    _ram[addr] = value;
}
