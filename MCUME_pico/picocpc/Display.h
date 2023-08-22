#ifndef DISPLAY_H
#define DISPLAY_H

#ifndef PICO_H_
#include "pico.h"
#include "pico/stdlib.h"
#endif
#include "emuapi.h"

#define WIDTH           320
#define HEIGHT          200
#define VGA_RGB(r,g,b)   ( (((r>>5)&0x07)<<5) | (((g>>5)&0x07)<<2) | (((b>>6)&0x3)<<0) )

class Bus;

namespace Display
{
    struct RGB {
        int R, G, B;
    };
    struct RGB firmware_palette[27] = {
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
    uint8_t hardware_colours[32] = {
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
