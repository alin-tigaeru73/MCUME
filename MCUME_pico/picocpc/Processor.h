#ifndef PROCESSOR_H
#define PROCESSOR_H

#ifndef PICO_H_
#include "pico.h"
#include "pico/stdlib.h"
#endif
#include "z80.h"

class Bus;

class Processor
{
private:
    uint64_t _pins;
    z80_t _cpu{};
    Bus* _bus;
public:
    explicit Processor(Bus* bus)
        : _bus(bus),
          _pins(z80_init(&_cpu))
    {
    };
    uint8_t readZ80(uint16_t addr);
    void writeZ80(uint16_t addr, uint8_t value);
    void outZ80(uint16_t port, uint8_t value);
    uint8_t inZ80(uint16_t port);
    void assertWait();
    void clearWait();
    void requestInterrupt();
    void acknowledgeInterrupt();
    bool step();
};


#endif //PROCESSOR_H
