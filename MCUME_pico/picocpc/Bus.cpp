#include "Bus.h"

uint8_t Bus::readMemory(const uint16_t addr) const {
    return _memory->read(addr);
}

void Bus::writeMemory(const uint16_t addr, const uint8_t value) const {
    _memory->write(addr, value);
}

void Bus::step() {
    const auto interruptAcknowledged = _processor->step();
    _crtc->step();
    const auto interruptGenerated = _ga->step();
    if(_ga->getWaitSignal()) {
        _processor->assertWait();
    }
    else {
        _processor->clearWait();
    }
    if(interruptGenerated) {
        _processor->requestInterrupt();
    }
    if(interruptAcknowledged) {
        _processor->acknowledgeInterrupt();
        clearInterruptCounterGA();
    }

    if(!_hsyncWait) {
        _display->drawScanLine();
        setHSyncWait(true);
    }

    if(!_vsyncWait) {
        _display->drawVSync();
        setVSyncWait(true);
    }
}

void Bus::writeGA(const uint8_t value) const {
    _ga->write(value);
}

void Bus::writeCRTC(const uint16_t port, const uint8_t value) const {
    _crtc->write(port, value);
}

uint8_t Bus::readCRTC(const uint16_t port) const {
    return _crtc->read(port);
}

void Bus::clearInterruptCounterGA() const {
    _ga->clearInterruptCounter();
}

bool Bus::isHSyncActive() const {
    return _crtc->isHSyncActive();
}

bool Bus::isVSyncActive() const {
    return _crtc->isVSyncActive();
}

uint16_t Bus::getVideoAddress() const {
    return _crtc->generateAddress();
}

bool Bus::isWithinDisplay() const {
    return _crtc->isWithinDisplay();
}

bool Bus::isLowRomEnabled() const {
    return _ga->getLowRomStatus();
}

bool Bus::isHighRomEnabled() const {
    return _ga->getHighRomStatus();
}

void Bus::setVSyncWait(const bool vsync) {
    _vsyncWait = vsync;
}

void Bus::setHSyncWait(const bool hsync) {
    _hsyncWait = hsync;
}

void Bus::draw(const uint8_t pixel) const {
    _display->populateBitstream(pixel);
}

uint8_t Bus::readPPI(const uint16_t port) const {
    if((port & 0xFF00) == 0xF400) return _ppi->readPortA();
    if((port & 0xFF00) == 0xF500) return _ppi->readPortB();

    return 0; // TODO default return value
}

uint8_t Bus::readPSG(const uint8_t value) {
    if(_ay->Latch == 14) {
        _ay->KeyLine = value;
        return RdKeyLine8910(_ay);
    }
    return RdData8910(_ay);
}

void Bus::writePPI(const uint16_t port, const uint8_t value) const {
    if((port & 0xFF00) == 0xF400) {
        _ppi->writePortA(value);
    } else if ((port & 0xFF00) == 0xF600) {
        _ppi->writePortC(value);
    } else if ((port & 0xFF00) == 0xF700) {
        _ppi->writeControl(value);
    }
}

void Bus::writePSG(const uint8_t value) const {
    WrData8910(_ay, value);
}

void Bus::selectPSGRegister(const uint8_t value) const {
    WrCtrl8910(_ay, value);
}

void Bus::setKeyPressed(const uint16_t hidKey) const {
    if(!_keyManager->existsInMap(hidKey)) return;
    const KeyManager::Key key = _keyManager->decodeKey(hidKey);
    _keyManager->setKeyPressed(key);
}

void Bus::setKeyLineReleased(const uint8_t line) {
    _keyManager->setKeyLineReleased(line);
}

uint8_t Bus::getKeyLine(const uint8_t line) const {
    return _keyManager->getLine(line);
}

void Bus::initialiseLowRom() {
    _memory->initialiseLowRom();
}

void Bus::initialiseUpperRom() {
    _memory->initialiseUpperRom();
}
