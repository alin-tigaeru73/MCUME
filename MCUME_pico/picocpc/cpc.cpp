#ifndef CHIPS_IMPL
#define CHIPS_IMPL
#endif
#include "cpc.h"

extern "C" {
#include "emuapi.h"
#include "platform_config.h"
}

auto bus = std::make_unique<Bus>();

void cpc_Init() {
    for(const auto& hardware_colour : Display::hardware_colours) {
        emu_SetPaletteEntry(R16(Display::firmware_palette[hardware_colour].R),
                            G16(Display::firmware_palette[hardware_colour].G),
                            B16(Display::firmware_palette[hardware_colour].B),
                            hardware_colour);
    }
    bus->initialiseLowRom();
    bus->initialiseUpperRom();
#ifdef HAS_SND
    emu_sndInit();
#endif
}

void cpc_Step() {
    bus->step();
}

void cpc_Input(const uint16_t bClick) {
    // This receives the HID code for a key and whether shift and control were pressed.
    bus->setKeyPressed(bClick);
}

void cpc_Start(char* filename) {

}
