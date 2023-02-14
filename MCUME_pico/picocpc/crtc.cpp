#include "pico.h"
#include "pico/stdlib.h"
#include <stdio.h>

#include "crtc.h"

uint8_t registers[16] = {
    63,                 // horizontal_total
    40,                 // horitzontal_displayed
    46,                 // horizontal_sync_position
    142,                // horizontal_and_vertical_sync_widths -> VVVVHHHH, so bits 0-3 correspond to hsync width, 4-7 to vsync.
    38,                 // vertical_total
    0,                  // vertical_total_adjust
    25,                 // vertical_displayed
    30,                 // vertical_sync_position
    0,                  // interlace_and_skew
    7,                  // max_raster_address
    0,                  // cursor_start_raster
    0,                  // cursor_end_raster
    48,                 // display_start_addr_high
    0,                  // display_start_addr_low
    0,                  // cursor_addr_high
    0                   // cursor_addr_low
};
uint8_t selectedRegister = 0;
uint8_t horizontalCount = 0;
uint8_t characterLineCount = 0;
uint8_t scanlineCount = 0;
uint8_t verticalAdjustCount = 0;
uint16_t memoryAddr = 0;


void crtc_step()
{
    // printf("Horizontal count: %d \n", horizontalCount);
    horizontalCount++;
    
    if(horizontalCount > registers[0])
    {
        // horizontal counter is equal to the Horizontal Total Register.
        horizontalCount = 0;
        scanlineCount++;
        // printf("Resetting horizontal counter!\n");
    }

    if(scanlineCount > registers[9])
    {
        // The counter for Maximum Raster Address is equal to it.
        // The height of a character is 8 rasters, so when we reach 8 rasters we increment the char line count.
        scanlineCount = 0;
        characterLineCount++;
        //printf("characterLineCount: %d \n", characterLineCount);
        // printf("Resetting scanline counter!\n");
    }

    if(characterLineCount > registers[4])
    {
        // The vertical counter reaches the Vertical Total register.
        characterLineCount = 0;
    }

    if(horizontalCount == 0 && characterLineCount == 0)
    {
        memoryAddr = ((uint16_t) registers[12] << 8) | registers[13];
        // printf("memoryAddr update! New value: %x \n", memoryAddr);
    }
}

uint16_t crtc_generateAddress()
{
    // Video address is created as follows:
    // Bit 0: Always 0
    // Bits 1-10: From bits 0-9 of memoryAddr
    // Bits 11-13: Bits 0-2 of scanlineCount
    // Bits 14 and 15: Bits 12 and 13 of memoryAddr.
    uint16_t firstTenBits = (memoryAddr & 0b0000001111111111) << 1;
    uint16_t elevenToThirteenBits = (scanlineCount & 0b0000000000000111) << 11;
    uint16_t fourteenFifteenBits = (memoryAddr & 0b0011000000000000) << 2;
    //printf("memoryAddr: %x \n calculatedAddr: %x \n", memoryAddr, fourteenFifteenBits | elevenToThirteenBits | firstTenBits);

    return fourteenFifteenBits | elevenToThirteenBits | firstTenBits;
}

bool isHSyncActive()
{
    // HSYNC is active if the horizontal counter is in the 
    // "horizontal_and_vertical_sync_widths"-defined width starting from the horizontal_total register.
    return horizontalCount >= registers[0]
        && horizontalCount < registers[0] + (registers[3] & 0b1111);
}

bool isVSyncActive()
{
    int8_t characterHeight = (int8_t) registers[9] + 1;
    int8_t characterLinesCounted = (int8_t) characterLineCount - registers[7];
    // printf("characterHeight: %d \ncharacterLineCount: %d \nscanlineCount: %d \n", characterHeight, characterLineCount, scanlineCount);
    // printf("isVSyncActive value calculated: %d \n", characterHeight * characterLinesCounted + scanlineCount);
    return  characterHeight * characterLineCount + (int8_t) scanlineCount >= 0 &&
            characterHeight * characterLineCount + (int8_t) scanlineCount <= 128;
}


void writeCRTC(unsigned short address, uint8_t value)
{
    switch(address & 0xFF00)
    {
        case 0xBC00: selectedRegister = value & 0b11111;
        case 0xBD00: registers[selectedRegister] = value;
    }
}

uint8_t readCRTC(unsigned short address)
{
    switch(address & 0xFF00)
    {
        case 0xBF00: return registers[selectedRegister];
    }
    return 0;
}
