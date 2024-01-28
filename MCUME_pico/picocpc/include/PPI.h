#ifndef PPI_H
#define PPI_H

#ifndef PICO_H_
#include "pico.h"
#include "pico/stdlib.h"
#endif

class Bus;

namespace PPI {

    enum class Mode {
        BASIC,
        STROBED,
        BIDIRECTIONAL
    };

    enum class Direction {
        INPUT,
        OUTPUT
    };

    struct Port {
        uint8_t value;
        Direction direction;
        Mode mode;
    };

    class PPI {

    private:
        Bus *_bus;
        Port _portA;
        Port _portB;
        Port _portC;
    public:
        explicit PPI(Bus *bus)
                : _bus(bus),
                  _portA({0, Direction::INPUT, Mode::BASIC}),
                  _portB({0, Direction::INPUT, Mode::BASIC}),
                  _portC({0, Direction::OUTPUT, Mode::BASIC}) {}

        void writePortA(uint8_t value);

        void writePortC(uint8_t value);

        void writeControl(uint8_t value);

        [[nodiscard]] uint8_t readPortA() const;

        [[nodiscard]] uint8_t readPortB();
    };
}

#endif //PPI_H
