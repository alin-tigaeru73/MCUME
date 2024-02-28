#include "KeyManager.h"

KeyManager::Key KeyManager::KeyManager::decodeKey(const uint16_t hidKey) {
    // Returns the FKC for the given HID key. From it we can get the line and bit by doing div and mod by 8.
    bool isShiftPressed = (hidKey >> 8) & 1;
    bool isCtrlPressed = (hidKey >> 9) & 1;

    return {isShiftPressed, isCtrlPressed, hidToFKC.at(hidKey & 0xFF)};
}

void KeyManager::KeyManager::setKeyPressed(Key key) {
    const uint8_t line = key.fkc / 8;
    const uint8_t bit = key.fkc % 8;

    // Clear the "bit"-th bit of the "line"-th line.
    if(key.isShifted) _lines.at(2) &= ~(1 << 5);
    if(key.isCtrl) _lines.at(2) &= ~(1 << 7);

    _lines.at(line) &= ~(1 << bit);
}

void KeyManager::KeyManager::setKeyLineReleased(const uint8_t line) {
     if(_lines.at(line) != 255) _lines.at(line) = 255;
}

uint8_t KeyManager::KeyManager::getLine(const uint8_t line) const {
    if(line < 10) return _lines.at(line);

    return 0xFF;
}

bool KeyManager::KeyManager::existsInMap(uint16_t hidKey) {
    return hidToFKC.find(hidKey & 0xFF) != hidToFKC.end();
}
