#ifndef DISPLAY_H
#define DISPLAY_H

#ifndef PICO_H_
#include "pico.h"
#include "pico/stdlib.h"
#endif
extern "C" {
#include "emuapi.h"
}

#define WIDTH           320
#define HEIGHT          200
//#define VGA_RGB(r,g,b)   ( (((r>>5)&0x07)<<5) | (((g>>5)&0x07)<<2) | (((b>>6)&0x3)<<0) )
// the previous is 8 bit, below is 16 bit
#define VGA_RGB(r,g,b)  ( (((b>>3)&0x1f)<<11) | (((g>>2)&0x3f)<<5) | (((r>>3)&0x1f)<<0) )

class Bus;

namespace Display
{
    struct RGB {
        int R, G, B;
    };
    extern struct RGB firmware_palette[27];
    extern uint8_t hardware_colours[32];

    class Display {
    private:
        Bus* _bus;
        int _position;
        int _x;
        int _y;
        unsigned short* _bitstream;
    public:
        explicit Display(Bus* bus)
                : _bus(bus),
                  _position(0),
                  _x(0),
                  _y(0),
                  _bitstream((unsigned short *)emu_Malloc(WIDTH*2))
        {
        };
        void populateBitstream(uint8_t pixel);
        void drawVSync();
        void drawScanLine();
    };
}


#endif //DISPLAY_H
