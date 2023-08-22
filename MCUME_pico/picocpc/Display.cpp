#include "Display.h"
#include "Bus.h"

void Display::Display::populateBitstream(uint8_t pixel) {
    _x = _position % WIDTH;
    _y = _position / WIDTH;

    _bitstream[_x + _y * WIDTH] = VGA_RGB(firmware_palette[hardware_colours[pixel]].R,
                                       firmware_palette[hardware_colours[pixel]].G,
                                       firmware_palette[hardware_colours[pixel]].B);
    _position++;
    if(_position == WIDTH * HEIGHT)
    {
        _position = 0;
        _bus->setVSyncWait(true);
    }
}

void Display::Display::drawFrame()
{
    emu_DrawScreen(_bitstream, WIDTH, HEIGHT, WIDTH);
    emu_DrawVsync();
}
