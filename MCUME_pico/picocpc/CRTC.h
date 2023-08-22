#ifndef CRTC_H
#define CRTC_H

#ifndef PICO_H_
#include "pico.h"
#include "pico/stdlib.h"
#endif

extern int registers[16];
extern uint16_t memoryStartAddr;
extern uint8_t selected_register;
extern uint8_t horizontalCounter;
extern uint8_t charLineCounter;
extern uint8_t scanlineCounter;
extern uint8_t vertical_adjust_count;
extern uint8_t microsec_count_crtc;

extern bool is_hsync_active();
extern bool is_vsync_active();
extern bool is_within_display();
extern uint16_t crtc_generate_addr();
extern void crtc_step();
extern void write_crt_controller(unsigned short address, uint8_t value);
extern uint8_t read_crt_controller(unsigned short address);


class Bus;
class CRTC
{
private:
    Bus* _bus;
    uint8_t registers[16] = {
            63,    // horizontal_total
            40,    // horizontal_displayed
            46,    // horizontal_sync_position
            142,   // horizontal_and_vertical_sync_widths -> VVVVHHHH, so bits 0-3 correspond to hsync width, 4-7 to vsync.
            38,    // vertical_total
            0,     // vertical_total_adjust
            25,    // vertical_displayed
            30,    // vertical_sync_position
            0,     // interlace_and_skew
            7,     // max_raster_address
            0,    // cursor_start_raster
            0,    // cursor_end_raster
            48,   // display_start_addr_high
            0,    // display_start_addr_low
            0,    // cursor_addr_high
            0     // cursor_addr_low
    };
    uint16_t memoryStartAddress;
    uint8_t selectedRegister;
    uint8_t horizontalCounter;
    uint8_t charLineCounter;
    uint8_t scanlineCounter;
    uint8_t verticalAdjustCounter;
    uint8_t microsecondCounter;
public:
    explicit CRTC(Bus* bus)
      :  _bus(bus),
         memoryStartAddress(0),
         selectedRegister(0),
         horizontalCounter(0),
         charLineCounter(0),
         scanlineCounter(0),
         verticalAdjustCounter(0),
         microsecondCounter(0)
    {
    };
    bool isHSyncActive();
    bool isVSyncActive();
    bool isWithinDisplay();
    uint16_t generateAddress();
    void step();
    void write(uint16_t addr, uint8_t value);
    uint8_t read(uint16_t addr);
};

#endif