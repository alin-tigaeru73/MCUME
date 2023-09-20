#ifndef BUS_H
#define BUS_H

#ifndef PICO_H_
#include "pico.h"
#include "pico/stdlib.h"
#endif

#include <memory>
#include "Processor.h"
#include "Memory.h"
#include "CRTC.h"
#include "GA.h"
#include "Display.h"

class Bus
{
private:
    std::unique_ptr<Processor> _processor;
    std::unique_ptr<Memory> _memory;
    std::unique_ptr<CRTC> _crtc;
    std::unique_ptr<GateArray> _ga;
    std::unique_ptr<Display::Display> _display;
    bool _vsyncWait{};
    bool _hsyncWait{};
public:
    Bus()
      : _processor(std::make_unique<Processor>(this)),
        _memory(std::make_unique<Memory>(this)),
        _crtc(std::make_unique<CRTC>(this)),
        _ga(std::make_unique<GateArray>(this)),
        _display(std::make_unique<Display::Display>(this)),
        _vsyncWait(true),
        _hsyncWait(true)
    {
    };
    ~Bus() = default;
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
    void setHSyncWait(bool hsync);
    void draw(uint8_t pixel);
};

#endif
