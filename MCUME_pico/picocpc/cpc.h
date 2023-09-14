#ifndef CPC_H
#define CPC_H

#ifndef PICO_H_
#include "pico.h"
#include "pico/stdlib.h"
#endif

#include "Bus.h"
#include "Display.h"

#define VGA_RGB(r,g,b)   ( (((r>>5)&0x07)<<5) | (((g>>5)&0x07)<<2) | (((b>>6)&0x3)<<0) )

extern void cpc_Init(void);
extern void cpc_Step(void);
extern void cpc_Start(char* filename);
extern void cpc_Input(int bClick);

#endif