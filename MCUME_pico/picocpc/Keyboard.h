#ifndef MCUME_KEYBOARD_H
#define MCUME_KEYBOARD_H

#include <unordered_map>

class Bus;

namespace Keyboard
{
    extern const std::unordered_map<int, int> asciiKeymap;
    extern const std::unordered_map<int, int> hidKeymap;

    class Keyboard
    {
    private:
        Bus* _bus;
    public:
        explicit Keyboard(Bus* bus)
                : _bus(bus)
        {
        };
    };

} // Keyboard

#endif
