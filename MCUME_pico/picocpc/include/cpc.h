#ifndef CPC_H
#define CPC_H

#ifndef PICO_H_
#include "pico.h"
#include "pico/stdlib.h"
#endif

#include "Bus.h"

extern void cpc_Init();
extern void cpc_Step();
extern void cpc_Start(char* filename);
extern void cpc_Input(uint16_t bClick);

#endif