#include "Processor.h"

Processor* Processor::_processor = nullptr;

Processor *Processor::getInstance()
{
    if(_processor == nullptr)
    {
        _processor = new Processor();
    }
    return _processor;
}

char Processor::readZ80(uint16_t addr)
{
//    if(addr <= LOWER_ROM_END && ga_config.lower_rom_enable)
//    {
//        return gb_rom_464_0[addr];
//    }
//    else if(addr >= UPPER_ROM_BEGIN && ga_config.upper_rom_enable)
//    {
//        return gb_rom_464_1[addr - 0xC000];
//    }
//    else
//    {
//        return RAM[addr];
//    }
    return 0;
}

void Processor::writeZ80(uint16_t addr, uint8_t value)
{
//    RAM[addr] = value;
}

void Processor::outZ80(uint16_t port, uint8_t Value)
{
//    if(!(port & 0x8000)) write_gate_array(Value);           // The Gate Array is selected when bit 15 is set to 0.
//    if(!(port & 0x4000)) write_crt_controller(port, Value); // The CRTC is selected when bit 14 is set to 0.
}

uint8_t Processor::inZ80(uint16_t port)
{
//    if(!(port & 0x4000)) return read_crt_controller(port); // The CRTC is selected when bit 14 is set to 0.
//    return 0xFF;
}

void Processor::step() {

}
