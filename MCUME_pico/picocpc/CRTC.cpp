#include "pico.h"
#include <cstdio>

#include "CRTC.h"
#include "Bus.h"

bool CRTC::isHSyncActive()
{
    // HSYNC is active if the horizontal counter is in the
    // "horizontal_and_vertical_sync_widths"-defined width starting from the horizontal_sync_position register.
    return horizontalCounter >= registers[2] &&
           horizontalCounter < registers[2] + (registers[3] & 0b1111);
}

bool CRTC::isVSyncActive()
{
    const uint8_t charHeight = registers[9] + 1;
    auto charLinesCounted = charLineCounter - registers[7];
    return charHeight * charLinesCounted >= 0 &&
           charHeight * charLinesCounted <= 16;
}

bool CRTC::isWithinDisplay()
{
    return horizontalCounter < registers[1] && charLineCounter < registers[6];
}

uint16_t CRTC::generateAddress()
{
    // Video address is created as follows:
    // Bit 0: Always 0
    // Bits 1-10: From bits 0-9 of memoryStartAddr
    // Bits 11-13: Bits 0-2 of scanlineCounter
    // Bits 14 and 15: Bits 12 and 13 of memoryStartAddr.
    uint16_t currentMemoryAddr = memoryStartAddress + (registers[1] * charLineCounter) + horizontalCounter;

    uint16_t bits0To10 = (currentMemoryAddr & 0b0000001111111111) << 1;
    uint16_t bits11To13 = (scanlineCounter & 0b0000000000000111) << 11;
    uint16_t bits14To15 = (currentMemoryAddr & 0b0011000000000000) << 2;
    return bits14To15 | bits11To13 | bits0To10;
}

void CRTC::step()
{
    if(microsecondCounter == 3)
    {
        horizontalCounter++;

        if(horizontalCounter > registers[0])
        {
            // horizontal counter is equal to the Horizontal Total Register.
            horizontalCounter = 0;
            scanlineCounter++;
        }

        if(scanlineCounter > registers[9])
        {
            // The counter for Maximum Raster Address is equal to it.
            // The height of a character is 8 rasters, so when we reach 8 rasters we increment the char line count.

            scanlineCounter = 0;
            charLineCounter++;
        }

        if(charLineCounter > registers[4])
        {
            // The vertical counter reaches the Vertical Total register.
            charLineCounter = 0;
        }

        if(charLineCounter == 0 && horizontalCounter == 0)
        {
            memoryStartAddress = ((uint16_t) registers[12] << 8) | registers[13];
        }

    }
    microsecondCounter = (microsecondCounter + 1) % 4;
}

void CRTC::write(uint16_t addr, uint8_t value)
{
    switch(addr & 0xFF00)
    {
        case 0xBC00: selectedRegister = value & 0b11111;break;
        case 0xBD00: registers[selectedRegister] = value;break;
    }
}

uint8_t CRTC::read(uint16_t addr)
{
    switch(addr & 0xFF00)
    {
        case 0xBF00: return registers[selectedRegister];
    }
    return 0; // TODO should print an error
}
