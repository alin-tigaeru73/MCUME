#ifndef CPC_H_
#define CPC_H_

#ifndef PICO_H_
#include "pico.h"
#include "pico/stdlib.h"
#endif

extern uint8_t RAM[0x10000];
extern unsigned char* bitstream;
extern struct GAConfig ga_config;

extern void cpc_Init(void);
extern void cpc_Step(void);
extern void cpc_Start(char* filename);
extern void cpc_Input(int bClick);

#endif