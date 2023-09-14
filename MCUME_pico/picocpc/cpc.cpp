#ifndef CHIPS_IMPL
  #define CHIPS_IMPL
#endif
#include <cstring>
#include "cpc.h"

extern "C" {
#include "emuapi.h"
#include "platform_config.h"
}
#define WIDTH           320
#define HEIGHT          200
#define LOWER_ROM_END   0x4000
#define UPPER_ROM_BEGIN 0xC000

Bus* bus = nullptr;

/**
 * Creates initial emulation state (i.e. sets up color palette, clears RAM, initialises CPU)
*/
void cpc_Init(void)
{
    for(unsigned char hardware_colour : Display::hardware_colours)
    {
        emu_SetPaletteEntry(R16(Display::firmware_palette[hardware_colour].R),
                            G16(Display::firmware_palette[hardware_colour].G),
                            B16(Display::firmware_palette[hardware_colour].B),
                            hardware_colour);
    }
    bus = new Bus();
}

/**
 * Steps through emulation
*/
void cpc_Step(void)
{
    bus->step();
}

void cpc_Input(int bClick)
{

}

void cpc_Start(char* filename)
{

}