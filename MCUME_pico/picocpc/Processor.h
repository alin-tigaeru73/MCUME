#ifndef PROCESSOR_H
#define PROCESSOR_H

#ifndef PICO_H_
#include "pico.h"
#include "pico/stdlib.h"
#endif

#include "z80.h"

class Processor
{
private:
    uint64_t _pins;
    static z80_t _cpu;
    static Processor* _processor;
    Processor()
    {
        _pins = z80_init(&_cpu);
    }

public:
    Processor(const Processor &other) = delete;
    void operator=(const Processor &other) = delete;
    static Processor* getInstance();
    uint64_t getPins() const
    {
        return _pins;
    }
    char readZ80(uint16_t addr);
    void writeZ80(uint16_t addr, uint8_t value);
    void outZ80(uint16_t port, uint8_t Value);
    uint8_t inZ80(uint16_t port);
    void step();
};


#endif //PROCESSOR_H
