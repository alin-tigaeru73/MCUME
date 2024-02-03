#ifndef CRTC_H
#define CRTC_H

#ifndef PICO_H_
#include "pico.h"
#include "pico/stdlib.h"
#endif

class Bus;

class CRTC {
private:
    Bus* _bus;
    uint8_t _registers[16] = {
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
    uint16_t _memoryStartAddress{};
    uint8_t _selectedRegister{};
    uint8_t _horizontalCounter{};
    uint8_t _charLineCounter{};
    uint8_t _scanlineCounter{};
    uint8_t _verticalAdjustCounter{};
    uint8_t _microsecondCounter{};
public:
    explicit CRTC(Bus* bus)
      : _bus(bus),
        _memoryStartAddress(0),
        _selectedRegister(0),
        _horizontalCounter(0),
        _charLineCounter(0),
        _scanlineCounter(0),
        _verticalAdjustCounter(0),
        _microsecondCounter(0) {};
    [[nodiscard]] bool isHSyncActive() const;
    [[nodiscard]] bool isVSyncActive() const;
    [[nodiscard]] bool isWithinDisplay() const;
    [[nodiscard]] uint16_t generateAddress() const;
    void step();
    void write(uint16_t addr, uint8_t value);
    [[nodiscard]] uint8_t read(uint16_t addr) const;
};

#endif