#ifndef MEMORY_H
#define MEMORY_H

#ifndef PICO_H_
#include "pico.h"
#include "pico/stdlib.h"
#endif

#include <cstring>

class Bus;

class Memory
{
private:
    Bus* _bus;
    uint8_t _ram[0x10000]{};               // 64k
public:
    explicit Memory(Bus* bus)
        : _bus(bus)
    {
        memset(_ram, 0, sizeof(_ram));
    };
    uint8_t read(uint16_t addr);
    void write(uint16_t addr, uint8_t value);
};


#endif //MEMORY_H
