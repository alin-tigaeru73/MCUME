#ifndef CHIPS_IMPL
  #define CHIPS_IMPL
#endif
#include "cpc.h"

extern "C" {
#include "emuapi.h"
#include "platform_config.h"
}

Bus* bus = nullptr;

/**
 * Creates initial emulation state
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