#ifndef GA_H
#define GA_H

#ifndef PICO_H_
#include "pico.h"
#include "pico/stdlib.h"
#endif

extern void write_gate_array(uint8_t value);
bool ga_step();
void select_pen(uint8_t value);
void select_pen_colour(uint8_t value);
void rom_and_screen_mgmt(uint8_t value);

#define PEN_NUMBER 17  // Mode 0 has 16 pens, mode 1 has 4 pens and mode 2 has 2 pens.

class Bus;

struct GAConfig {
    uint8_t pen_selected = 0;
    uint8_t pen_colours[PEN_NUMBER]{};
    uint8_t screen_mode = 1; // 0 -> 160x200 16c; 1 -> 320x200 4c; 2 -> 640x200 2c; 3 (unofficial) -> 160x200 4c.
    bool upper_rom_enable = true;
    bool lower_rom_enable = true;
    uint8_t interrupt_counter = 0;
    uint8_t vsync_delay_count = 0;
    bool hsync_active = false;
    bool vsync_active = false;
    bool wait_signal = false;
};

struct RGB {
    int R, G, B;
};

extern struct RGB firmware_palette[27];
extern uint8_t hardware_colours[32];

class GateArray
{
private:
    Bus* _bus;
    uint8_t _penSelected;
    uint8_t _penNumber;
    uint8_t* _penColours;
    uint8_t _screenMode;
    bool _lowRomEnabled;
    bool _highRomEnabled;
    uint8_t _interruptCounter;
    uint8_t _delayVSyncCounter;
    bool _waitSignal;
    bool _currentHSync;
    bool _currentVSync;
    uint8_t _microsecondCounter;
    // TODO: figure out how to dynamically manage the _penColours array, based on screen mode
public:
    explicit GateArray(Bus* bus)
            : _bus(bus),
              _penSelected(0),
              _penNumber(17), // FIXME
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
    ~GateArray()
    {
        delete _penColours;
    }
    bool updateInterrupts();
    void generatePixelData();
    bool step();
    void selectPen(uint8_t value);
    void selectPenColour(uint8_t value);
    void manageRomScreenInterrupt(uint8_t value);
    void write(uint8_t value);
    bool checkWaitSignal() const;
    void clearInterruptCounter();
    bool checkLowRom() const;
    bool checkHighRom() const;
};
#endif
