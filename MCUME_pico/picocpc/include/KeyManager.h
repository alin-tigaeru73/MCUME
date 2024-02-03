#ifndef KEYMANAGER_H
#define KEYMANAGER_H

#ifndef PICO_H_
#include "pico.h"
#include "pico/stdlib.h"
#endif
#include <unordered_map>

class Bus;

namespace KeyManager {
    inline std::unordered_map<uint8_t , uint8_t> hidToFKC = {
        {0x52, 0x00}, // Key_CursorUp
        {0x4F, 0x01}, // Key_CursorRight
        {0x51, 0x02}, // Key_CursorDown
        {0x61, 0x03}, // Key_F9
        {0x5E, 0x04}, // Key_F6
        {0x5B, 0x05}, // Key_F3
        {0x58, 0x06}, // Key_Enter
        {0x63, 0x07}, // Key_FDot
        {0x50, 0x08}, // Key_CursorLeft
        {0x5F, 0x0A}, // Key_F7
        {0x60, 0x0B}, // Key_F8
        {0x5D, 0x0C}, // Key_F5
        {0x59, 0x0D}, // Key_F1
        {0x5A, 0x0E}, // Key_F2
        {0x62, 0x0F}, // Key_F0
        {0x2F, 0x11}, // Key_OpenBracket
        {0x28, 0x12}, // Key_Return
        {0x30, 0x13}, // Key_CloseBracket
        {0x5C, 0x14}, // Key_F4
        {0x31, 0x16}, // Key_BackSlash
        {0x2A, 0x18}, // Key_Caret
        {0x2D, 0x19}, // Key_Hyphen
        {0x34, 0x1A}, // Key_At
        {0x13, 0x1B}, // Key_P
        {0x33, 0x1C}, // Key_SemiColon
        {0x38, 0x1E}, // Key_Slash
        {0x37, 0x1F}, // Key_Dot
        {0x27, 0x20}, // Key_0
        {0x26, 0x21}, // Key_9
        {0x12, 0x22}, // Key_O
        {0x0C, 0x23}, // Key_I
        {0x0F, 0x24}, // Key_L
        {0x0E, 0x25}, // Key_K
        {0x10, 0x26}, // Key_M
        {0x36, 0x27}, // Key_Comma
        {0x25, 0x28}, // Key_8
        {0x24, 0x29}, // Key_7
        {0x18, 0x2A}, // Key_U
        {0x1C, 0x2B}, // Key_Y
        {0x0B, 0x2C}, // Key_H
        {0x0D, 0x2D}, // Key_J
        {0x11, 0x2E}, // Key_N
        {0x2C, 0x2F}, // Key_Space
        {0x23, 0x30}, // Key_6
        {0x22, 0x31}, // Key_5
        {0x15, 0x32}, // Key_R
        {0x17, 0x33}, // Key_T
        {0x0A, 0x34}, // Key_G
        {0x09, 0x35}, // Key_F
        {0x05, 0x36}, // Key_B
        {0x19, 0x37}, // Key_V
        {0x21, 0x38}, // Key_4
        {0x20, 0x39}, // Key_3
        {0x08, 0x3A}, // Key_E
        {0x1A, 0x3B}, // Key_W
        {0x16, 0x3C}, // Key_S
        {0x07, 0x3D}, // Key_D
        {0x06, 0x3E}, // Key_C
        {0x1B, 0x3F}, // Key_X
        {0x1E, 0x40}, // Key_1
        {0x1F, 0x41}, // Key_2
        {0x29, 0x42}, // Key_Esc
        {0x14, 0x43}, // Key_Q
        {0x2B, 0x44}, // Key_Tab
        {0x04, 0x45}, // Key_A
        {0x39, 0x46}, // Key_CapsLock
        {0x1D, 0x47}, // Key_Z
        {0x2A, 0x4F}  // Key_Del
        // TODO backspace?
    };

    class KeyManager {
    private:
        Bus* _bus;
		std::array<uint8_t, 10> _lines{};
    public:
        explicit KeyManager(Bus* bus) : _bus(bus) {
            _lines.fill(255);
        }

        static uint8_t decodeKey(uint16_t hidKey);
        void setKeyPressed(uint8_t fkc);
        void setKeyLineReleased(uint8_t fkc);
        [[nodiscard]] uint8_t getLine(uint8_t line) const;
        [[nodiscard]] bool existsInMap(uint16_t hidKey) const;
    };


} // KeyManager

#endif
