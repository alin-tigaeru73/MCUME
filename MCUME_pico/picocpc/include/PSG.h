#ifndef MCUME_PSG_H
#define MCUME_PSG_H

#ifndef PICO_H_
#include "pico.h"
#include "pico/stdlib.h"
#endif

extern "C" {
#include "AY8910.h"
}

#define AY_CLOCK 1000000
#define SAMPLE_RATE 22050

class Bus;

class PSG {
private:
    Bus *_bus;
    AY8910 *_ay;
    uint8_t _microsecondCounter;
public:
    explicit PSG(Bus *bus)
            : _bus(bus),
              _ay(new AY8910()),
              _microsecondCounter(0){
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
