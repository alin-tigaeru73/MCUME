#ifndef CHIPS_IMPL
  #define CHIPS_IMPL
#endif
#include <cstring>
#include "z80.h"
#include "cpc.h"
#include "CRTC.h"
#include "GA.h"
#include "roms/rom464.h"
extern "C" {
#include "emuapi.h"
#include "platform_config.h"
}
#define WIDTH           320
#define HEIGHT          200
#define LOWER_ROM_END   0x4000
#define UPPER_ROM_BEGIN 0xC000

uint8_t RAM[0x10000];               // 64k
unsigned char* bitstream = nullptr; // 16k video ram to be used by PIO.
static z80_t CPU;
uint64_t pins;
bool interrupt_generated = false;
int position = 0;
int x, y = 0;

void write_to_bitstream(char pixel)
{
    x = position % WIDTH;
    y = position / WIDTH;

    bitstream[x + y * WIDTH] = VGA_RGB(firmware_palette[hardware_colours[pixel]].R,
                                       firmware_palette[hardware_colours[pixel]].G,
                                       firmware_palette[hardware_colours[pixel]].B);
    position++;
    if(position == WIDTH * HEIGHT)
    {
        position = 0;
        vsync_wait = true;
    }
}

static void display_screen()
{
    emu_DrawScreen(bitstream, WIDTH, HEIGHT, WIDTH);
    emu_DrawVsync();
}

char read_z80(uint16_t addr)
{
    if(addr <= LOWER_ROM_END && ga_config.lower_rom_enable)
    {
        return gb_rom_464_0[addr];
    }
    else if(addr >= UPPER_ROM_BEGIN && ga_config.upper_rom_enable)
    {
        return gb_rom_464_1[addr - 0xC000];
    }
    else
    {
        return RAM[addr];
    }
}

void write_z80(uint16_t addr, uint8_t value)
{
    RAM[addr] = value;
}

void out_z80(uint16_t port, uint8_t Value)
{
    if(!(port & 0x8000)) write_gate_array(Value);           // The Gate Array is selected when bit 15 is set to 0.
    if(!(port & 0x4000)) write_crt_controller(port, Value); // The CRTC is selected when bit 14 is set to 0.
}

uint8_t in_z80(uint16_t port)
{
    if(!(port & 0x4000)) return read_crt_controller(port); // The CRTC is selected when bit 14 is set to 0.
    return 0xFF;
}

/**
 * Creates initial emulation state (i.e. sets up color palette, clears RAM, initialises CPU)
*/
void cpc_Init(void)
{
    for(unsigned char hardware_colour : hardware_colours)
    {
        emu_SetPaletteEntry(firmware_palette[hardware_colour].R,
                            firmware_palette[hardware_colour].G,
                            firmware_palette[hardware_colour].B,
                            hardware_colour);
    }
    if (bitstream == nullptr) bitstream = (unsigned char *)emu_Malloc(WIDTH*HEIGHT);

    pins = z80_init(&CPU);
    memset(RAM, 0, sizeof(RAM));
}

/**
 * Steps through emulation
*/
void cpc_Step(void)
{
    bool interrupt_acknowledged = false;
    pins = z80_tick(&CPU, pins);

    if (pins & Z80_MREQ) 
    {
        const uint16_t addr = Z80_GET_ADDR(pins);
        if (pins & Z80_RD) 
        {
            uint8_t data = read_z80(addr);
            Z80_SET_DATA(pins, data);
        }
        else if (pins & Z80_WR) 
        {
            uint8_t data = Z80_GET_DATA(pins);
            write_z80(addr, data);
        }
    }
    else if (pins & Z80_IORQ) 
    {
        const uint16_t port = Z80_GET_ADDR(pins);
        if (pins & Z80_M1) 
        {
            // an interrupt acknowledge cycle, depending on the emulated system,
            // put either an instruction byte, or an interrupt vector on the data bus
            Z80_SET_DATA(pins, 0x0038);
            interrupt_acknowledged = true;
        }
        else if (pins & Z80_RD) 
        {
            // handle IO input request at port
            in_z80(port);
        }
        else if (pins & Z80_WR) 
        {
            // handle IO output request at port
            uint8_t data = Z80_GET_DATA(pins);
            out_z80(port, data);
        }
    }

    crtc_step();
    interrupt_generated = ga_step();
    if(ga_config.wait_signal)
    {
        pins = pins | Z80_WAIT;
    }
    else
    {
        pins = pins & ~Z80_WAIT;
    }

    if(interrupt_generated)
    {
        // request an interrupt from the CPU
        pins = pins | Z80_INT;
    }

    if(interrupt_acknowledged)
    {
        pins = pins & ~Z80_INT;
        ga_config.interrupt_counter &= 0x1f;
    }

    if(!vsync_wait)
    {
        display_screen();
        vsync_wait = true;
    }
}

void cpc_Input(int bClick)
{

}

void cpc_Start(char* filename)
{

}