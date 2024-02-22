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
#include "KeyManager.h"
#include "PPI.h"
#include "BusCConnector.h"
#include "PSG.h"

class Bus {
private:
    std::unique_ptr<Processor> _processor;
    std::unique_ptr<Memory> _memory;
    std::unique_ptr<CRTC> _crtc;
    std::unique_ptr<GateArray> _ga;
    std::unique_ptr<Display::Display> _display;
    std::unique_ptr<KeyManager::KeyManager> _keyManager;
    std::unique_ptr<PPI::PPI> _ppi;
    std::unique_ptr<PSG> _psg;
    bool _vsyncWait{};
    bool _hsyncWait{};
public:
    Bus(): _processor(std::make_unique<Processor>(this)),
           _memory(std::make_unique<Memory>(this)),
           _crtc(std::make_unique<CRTC>(this)),
           _ga(std::make_unique<GateArray>(this)),
           _display(std::make_unique<Display::Display>(this)),
           _keyManager(std::make_unique<KeyManager::KeyManager>(this)),
           _ppi(std::make_unique<PPI::PPI>(this)),
           _psg(std::make_unique<PSG>(this)),
           _vsyncWait(true),
           _hsyncWait(true) {
        // For the C connector.
        setBusInstance(this);
    }
    [[nodiscard]] bool isLowRomEnabled() const;
    [[nodiscard]] bool isHighRomEnabled() const;
    [[nodiscard]] uint8_t readMemory(uint16_t addr) const;
    [[nodiscard]] uint8_t readCRTC(uint16_t port) const;
    [[nodiscard]] uint16_t getVideoAddress() const;
    [[nodiscard]] bool isHSyncActive() const;
    [[nodiscard]] bool isVSyncActive() const;
    [[nodiscard]] bool isWithinDisplay() const;
    [[nodiscard]] uint8_t readPPI(uint16_t port) const;
    [[nodiscard]] uint8_t readPSG(uint8_t value);
    [[nodiscard]] uint8_t getKeyLine(uint8_t line) const;
    void step();
    void writeMemory(uint16_t addr, uint8_t value) const;
    void writeGA(uint8_t value) const;
    void clearInterruptCounterGA() const;
    void writeCRTC(uint16_t port, uint8_t value) const;
    void setVSyncWait(bool vsync);
    void setHSyncWait(bool hsync);
    void draw(uint8_t pixel) const;
    void initialiseLowRom();
    void initialiseUpperRom();
    void writePPI(uint16_t port, uint8_t value) const;
    void writePSG(uint8_t value) const;
    void selectPSGRegister(uint8_t value) const;
    void setKeyPressed(uint16_t hidKey) const;
    void setKeyLineReleased(uint8_t fkc);

    void psgExecute();
};

#undef EXTERNC
#endif
