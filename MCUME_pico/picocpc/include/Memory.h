#ifndef MEMORY_H
#define MEMORY_H

#ifndef PICO_H_
#include "pico.h"
#include "pico/stdlib.h"
#endif

#include <array>
#include <cstring>
extern "C" {
    #include <emuapi.h>
}
#include "ROMLoader.h"

class Bus;

class Memory {
private:
    Bus* _bus;
    uint8_t _ram[0x10000]{};               // 64k
    std::array<char, 16384> _lowerRom{};  // 16k
    std::array<char, 16384> _upperRom{};  // 16k
public:
    explicit Memory(Bus* bus)
        : _bus(bus) {
        memset(_ram, 0, sizeof(_ram));
        memset(_lowerRom.data(), 0, sizeof(_lowerRom));
        memset(_upperRom.data(), 0, sizeof(_upperRom));
    };
    [[nodiscard]] uint8_t read(uint16_t addr) const;
    void write(uint16_t addr, uint8_t value);
    void initialiseLowRom();
    void initialiseUpperRom();
};


#endif //MEMORY_H
