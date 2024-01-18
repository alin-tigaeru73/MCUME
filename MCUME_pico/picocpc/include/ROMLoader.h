//
// Created by alint on 03/12/2023.
//
#ifndef ROMLOADER_H
#define ROMLOADER_H

#include <iostream>
#include <vector>
#include <array>
#include <string>

extern "C" {
    #include <emuapi.h>
}

class ROMLoader {
public:
    ROMLoader() = default;

    static void load(std::array<char, 16384>& rom, const char* filepath) ;
};


#endif //ROMLOADER_H
