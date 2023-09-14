#include "Display.h"
#include "Bus.h"

struct Display::RGB Display::firmware_palette[27] = {
        {0, 0, 0}, // 0
        {0, 0, 128}, // 1
        {0, 0, 255}, // 2
        {128, 0, 0}, // 3
        {128, 0, 128}, // 4
        {128, 0, 255}, // 5
        {255, 0, 0}, // 6
        {255, 0, 128}, // 7
        {255, 0, 255}, // 8
        {0, 128, 0}, // 9
        {0, 128, 128}, // 10
        {0, 128, 255}, // 11
        {128, 128, 0}, // 12
        {128, 128, 128}, // 13
        {128, 128, 255}, // 14
        {255, 128, 0}, // 15
        {255, 128, 128}, // 16
        {255, 128, 255}, // 17
        {0, 255, 0}, // 18
        {0, 255, 128}, // 19
        {0, 255, 255}, // 20
        {128, 255, 0}, // 21
        {128, 255, 128}, // 22
        {128, 255, 255}, // 23
        {255, 255, 0}, // 24
        {255, 255, 128}, // 25
        {255, 255, 255} // 26
};

uint8_t Display::hardware_colours[32] = {
        13,
        13,
        19,
        25,
        1,
        7,
        10,
        16,
        7,
        25,
        24,
        26,
        6,
        8,
        15,
        17,
        1,
        19,
        18,
        20,
        0,
        2,
        9,
        11,
        4,
        22,
        21,
        23,
        3,
        5,
        12,
        14
};

void Display::Display::populateBitstream(uint8_t pixel) {
    _x = _position % WIDTH;
//    _y = _position / WIDTH;

    _bitstream[_x] = VGA_RGB(firmware_palette[hardware_colours[pixel]].R,
                                       firmware_palette[hardware_colours[pixel]].G,
                                       firmware_palette[hardware_colours[pixel]].B);
    _position++;
    if(_position == WIDTH)
    {
        _y++;
        _position = 0;
        _bus->setHSyncWait(true);
    }
    if(_y == HEIGHT)
    {
        _y = 0;
        _bus->setVSyncWait(true);
    }
}


void Display::Display::drawVSync()
{
    emu_DrawVsync();
}

void Display::Display::drawScanLine() {
    emu_DrawLine16(_bitstream, WIDTH, HEIGHT, _y);
}
