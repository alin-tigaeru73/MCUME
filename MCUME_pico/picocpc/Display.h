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
#define VGA_RGB(r,g,b)   ( (((r>>5)&0x07)<<5) | (((g>>5)&0x07)<<2) | (((b>>6)&0x3)<<0) )

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
        unsigned char* _bitstream;
    public:
        explicit Display(Bus* bus)
                : _bus(bus),
                  _position(0),
                  _x(0),
                  _y(0),
                  _bitstream((unsigned char *)emu_Malloc(WIDTH*HEIGHT))
        {
        };
        void populateBitstream(uint8_t pixel);
        void drawFrame();
    };
}


#endif //DISPLAY_H
