#include "ROMLoader.h"

void ROMLoader::load(std::array<char, 16384>& rom, const char* filepath) {
    emu_LoadFile(filepath, rom.data(), 16384);

//    int f = emu_FileOpen(filepath, "r+b");
//
//    for(int i = 0; i < 16384; i++) {
//        rom[i] = emu_FileGetc(f);
//    }

//    int read = emu_FileRead(rom.data(), flen);
//    if(read != 0) {
//        printf("ROMLoader: Error reading file %s\n", filepath);
//    }
//    emu_FileClose(f);
}
