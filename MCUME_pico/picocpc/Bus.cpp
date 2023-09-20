#include "Bus.h"

uint8_t Bus::readMemory(uint16_t addr)
{
    return _memory->read(addr);
}

void Bus::writeMemory(uint16_t addr, uint8_t value)
{
    _memory->write(addr, value);
}

void Bus::step()
{
    bool interruptAcknowledged = _processor->step();
    _crtc->step();
    bool interruptGenerated = _ga->step();
    if(_ga->getWaitSignal())
    {
        _processor->assertWait();
    }
    else
    {
        _processor->clearWait();
    }
    if(interruptGenerated)
    {
        _processor->requestInterrupt();
    }
    if(interruptAcknowledged)
    {
        _processor->acknowledgeInterrupt();
        clearInterruptCounterGA();
    }

    if(!_hsyncWait)
    {
        _display->drawScanLine();
        setHSyncWait(true);
    }

    if(!_vsyncWait)
    {
        _display->drawVSync();
        setVSyncWait(true);
    }
}

void Bus::writeGA(uint8_t value)
{
    _ga->write(value);
}

void Bus::writeCRTC(uint16_t port, uint8_t value)
{
    _crtc->write(port, value);
}

uint8_t Bus::readCRTC(uint16_t port)
{
    return _crtc->read(port);
}

void Bus::clearInterruptCounterGA()
{
    _ga->clearInterruptCounter();
}

bool Bus::isHSyncActive()
{
    return _crtc->isHSyncActive();
}

bool Bus::isVSyncActive()
{
    return _crtc->isVSyncActive();
}

uint16_t Bus::getVideoAddress()
{
    return _crtc->generateAddress();
}

bool Bus::isWithinDisplay()
{
    return _crtc->isWithinDisplay();
}

bool Bus::isLowRomEnabled()
{
    return _ga->getLowRomStatus();
}

bool Bus::isHighRomEnabled()
{
    return _ga->getHighRomStatus();
}

void Bus::setVSyncWait(bool vsync) {
    _vsyncWait = vsync;
}

void Bus::setHSyncWait(bool hsync) {
    _hsyncWait = hsync;
}

void Bus::draw(uint8_t pixel)
{
    _display->populateBitstream(pixel);
}
