#ifndef CPC_H
#define CPC_H

#ifndef PICO_H_
#include "pico.h"
#include "pico/stdlib.h"
#endif

#include "Bus.h"
#include "Display.h"

extern void cpc_Init(void);
extern void cpc_Step(void);
extern void cpc_Start(char* filename);
extern void cpc_Input(int bClick);

#endif