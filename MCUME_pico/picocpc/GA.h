#ifndef GA_H
#define GA_H

#ifndef PICO_H_

#include "pico.h"
#include "pico/stdlib.h"
#endif


class Bus;

class GateArray
{
private:
    Bus* _bus;
    uint8_t _penSelected{};
    uint8_t _penNumber{};
    uint8_t* _penColours{};
    uint8_t _screenMode{};
    bool _lowRomEnabled{};
    bool _highRomEnabled{};
    uint8_t _interruptCounter{};
    uint8_t _delayVSyncCounter{};
    bool _waitSignal{};
    bool _currentHSync{};
    bool _currentVSync{};
    uint8_t _microsecondCounter{};
public:
    explicit GateArray(Bus* bus)
            : _bus(bus),
              _penSelected(0),
              _penNumber(17),
              _screenMode(1),
              _lowRomEnabled(true),
              _highRomEnabled(true),
              _interruptCounter(0),
              _delayVSyncCounter(0),
              _waitSignal(false),
              _currentHSync(false),
              _currentVSync(false),
              _microsecondCounter(0)
    {
        _penColours = new uint8_t[_penNumber];
    };
    ~GateArray() = default;
    bool updateInterrupts();
    void generatePixelData();
    bool step();
    void selectPen(uint8_t value);
    void selectPenColour(uint8_t value);
    void manageRomScreenInterrupt(uint8_t value);
    void write(uint8_t value);
    bool getWaitSignal() const;
    void clearInterruptCounter();
    bool getLowRomStatus() const;
    bool getHighRomStatus() const;
};
#endif
