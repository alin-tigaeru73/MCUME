#ifndef MCUME_PSG_H
#define MCUME_PSG_H

#ifndef PICO_H_
#include "pico.h"
#include "pico/stdlib.h"
#endif

extern "C" {
#include "AY8910.h"
#include "emuapi.h"
}

#define AY_CLOCK 1000000

class Bus;

class PSG {
private:
    Bus *_bus;
    AY8910 *_ay;
public:
    explicit PSG(Bus *bus)
            : _bus(bus),
              _ay(new AY8910()) {
        Reset8910(_ay, AY_CLOCK, 0);
    }

    ~PSG() {
        delete _ay;
    }

    void step();
    [[nodiscard]] uint8_t getLatch();
    void setKeyLine(uint8_t value);
    [[nodiscard]] uint8_t readKeyLine();
    [[nodiscard]] uint8_t readData();
    void write(uint8_t value);
    void writeCtrl(uint8_t value);
};


#endif //MCUME_PSG_H
