#ifndef BUS_H
#define BUS_H

#ifndef PICO_H_
#include "pico.h"
#include "pico/stdlib.h"
#endif

#include "Processor.h"
#include "Memory.h"
#include "CRTC.h"
#include "GA.h"
#include "Display.h"

class Bus
{
private:
    Processor* _processor;
    Memory* _memory;
    CRTC* _crtc;
    GateArray* _ga;
    Display::Display* _display;
    bool _vsyncWait;
public:
    Bus()
      : _processor(new Processor(this)),
        _memory(new Memory(this)),
        _crtc(new CRTC(this)),
        _ga(new GateArray(this)),
        _display(new Display::Display(this)),
        _vsyncWait(true)
    {
    };
    ~Bus()
    {
        delete _processor;
        delete _memory;
        delete _crtc;
        delete _ga;
        delete _display;
    };
    void step();
    uint8_t readMemory(uint16_t addr);
    void writeMemory(uint16_t addr, uint8_t value);
    bool isLowRomEnabled();
    bool isHighRomEnabled();
    void writeGA(uint8_t value);
    void clearInterruptCounterGA();
    void writeCRTC(uint16_t port, uint8_t value);
    uint8_t readCRTC(uint16_t port);
    uint16_t getVideoAddress();
    bool isHSyncActive();
    bool isVSyncActive();
    bool isWithinDisplay();
    void setVSyncWait(bool vsync);
    void draw(uint8_t pixel);
};

#endif //BUS_H
