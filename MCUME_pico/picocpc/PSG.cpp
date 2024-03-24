#include "PSG.h"

uint8_t PSG::getLatch() {
    return _ay->Latch;
}

void PSG::setKeyLine(uint8_t value) {
    _ay->KeyLine = value;
}

uint8_t PSG::readKeyLine() {
    return RdKeyLine8910(_ay);
}

uint8_t PSG::readData() {
    return RdData8910(_ay);
}

void PSG::write(uint8_t value) {
    WrData8910(_ay, value);
}

void PSG::writeCtrl(uint8_t value) {
    WrCtrl8910(_ay, value);
}

void PSG::step() {
    // this is called every 1ms (every 20 sound interrupt requests)
    Loop8910(_ay, 1);
}

