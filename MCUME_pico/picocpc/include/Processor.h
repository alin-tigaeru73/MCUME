#ifndef PROCESSOR_H
#define PROCESSOR_H

#ifndef PICO_H_
#include "pico.h"
#include "pico/stdlib.h"
#endif
#include "z80.h"

class Bus;

class Processor {
private:
    uint8_t _interruptCounter{};
    uint64_t _pins{};
    z80_t _cpu{};
    Bus* _bus;
public:
    explicit Processor(Bus* bus)
        : _interruptCounter(0),
          _pins(z80_init(&_cpu)),
          _bus(bus) {};
    [[nodiscard]] uint8_t readZ80(uint16_t addr) const;
    void writeZ80(uint16_t addr, uint8_t value) const;
    void outZ80(uint16_t port, uint8_t value) const;
    [[nodiscard]] uint8_t inZ80(uint16_t port) const;
    void assertWait();
    void clearWait();
    void requestInterrupt();
    void acknowledgeInterrupt();
    bool step();
};

#endif
