#include "ROMLoader.h"

void ROMLoader::load(std::array<char, 16384>& rom, const char* filepath) {
    emu_LoadFile(filepath, rom.data(), 16384);
}
