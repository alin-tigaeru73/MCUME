#ifndef EMUAPI_H
#define EMUAPI_H

#include "platform_config.h"

//#define TIMER_REND  1
#define EXTRA_HEAP  0x10

// Title:     <                        >
#define TITLE "    ZX81/ZX80 Emulator"
#define ROMSDIR "z81"

#define emu_Init(ROM) {z81_Start(ROM); z81_Init(); }
#define emu_Step(x) {z81_Step();}
#define emu_Input(x) {}

#define PALETTE_SIZE         2
#define VID_FRAME_SKIP       0x3
#define TFT_VBUFFER_YCROP    0
#define SINGLELINE_RENDERING 1

#define ACTION_NONE          0
#define ACTION_MAXKBDVAL     225
#define ACTION_EXITKBD       128
#define ACTION_RUNTFT        129
#define ACTION_RUNVGA        130


#ifdef KEYMAP_PRESENT
#ifdef PICOMPUTER
/*   
const unsigned short key_map1[] = {
  30,31,32,33,34,35,36,37,38,39,
  20,26, 8,21,23,28,25,12,18,19,
   4, 9, 7,22, 4,11,13,14,15,40,
  25, 6,27,29,224,5,17,16,225,44 
  }; 
*/

const unsigned short key_map1[] = {
  20,26,8,21,23, 28,25,12,18, 19,0x100+39,
  0x100+30, 4, 9,7, 22, 10,11,13,14, 15,40,
  0, 6,27,29,224,5, 17,16,225,44, 
  0x100+36,0x100+34,0x100+37,0x100+35
  };  

const unsigned short key_map2[] = {
  30,31,32,33,34,35,36,37,38,39,0x100+19,
//  0x100+20, 0x100+26,0x100+8, 0x100+21, 0x100+23,0x100+28,0x100+25,0x100+12, 0x100+18,0x100+19,0,
  0x100+31, 0x100+4 ,0x100+9, 0x100+7,  0x100+22,0x100+10,0x100+11,0x100+13, 0x100+14,0x100+15,0x100+40,
  0,0,0,0,0,0x100+5, 0x100+17,0x100+16,0x100+225,0x100+44, 
  0,0,0,0
  };  

const unsigned short matkeys[] = {
  0x020,0x120,0x220,0x320,0x420,0x408,0x308,0x208,0x108,0x008,0x520, // row 1
  0x510,0x010,0x110,0x210,0x310,0x410,0x401,0x301,0x201,0x101,0x001, // row 2
  0x002,0x102,0x202,0x302,0x402,0x404,0x304,0x204,0x104,0x004, // row 3
  0x508,0x501,0x502,0x504 }; // cursor keys
 
#endif
#endif


#define MASK_JOY2_RIGHT 0x0001
#define MASK_JOY2_LEFT  0x0002
#define MASK_JOY2_UP    0x0004
#define MASK_JOY2_DOWN  0x0008
#define MASK_JOY2_BTN   0x0010
#define MASK_KEY_USER1  0x0020
#define MASK_KEY_USER2  0x0040
#define MASK_KEY_USER3  0x0080
#define MASK_JOY1_RIGHT 0x0100
#define MASK_JOY1_LEFT  0x0200
#define MASK_JOY1_UP    0x0400
#define MASK_JOY1_DOWN  0x0800
#define MASK_JOY1_BTN   0x1000
#define MASK_KEY_USER4  0x2000


extern void emu_init(void);
extern void emu_start(void);
extern void emu_resetSD(void);

extern void emu_printf(char * text);
extern void emu_printi(int val);
extern void * emu_Malloc(int size);
extern void emu_Free(void * pt);

extern int emu_FileOpen(char * filename);
extern int emu_FileRead(char * buf, int size);
extern unsigned char emu_FileGetc(void);
extern int emu_FileSeek(int seek);
extern void emu_FileClose(void);
extern int emu_FileSize(char * filename);
extern int emu_LoadFile(char * filename, char * buf, int size);
extern int emu_LoadFileSeek(char * filename, char * buf, int size, int seek);
extern void emu_FileTempInit(void); 
extern void emu_FileTempRead(int addr, unsigned char * val, int n); 
extern void emu_FileTempWrite(int addr, unsigned char val); 

extern void emu_SetPaletteEntry(unsigned char r, unsigned char g, unsigned char b, int index);
extern void emu_DrawScreen(unsigned char * VBuf, int width, int height, int stride);
extern void emu_DrawLine(unsigned char * VBuf, int width, int height, int line);
extern void emu_DrawLine8(unsigned char * VBuf, int width, int height, int line);
extern void emu_DrawLine16(unsigned short * VBuf, int width, int height, int line);
extern void emu_DrawVsync(void);
extern int emu_FrameSkip(void);
extern void * emu_LineBuffer(int line);

extern void emu_InitJoysticks(void);
extern int emu_SwapJoysticks(int statusOnly);
extern unsigned short emu_DebounceLocalKeys(void);
extern int emu_ReadKeys(void);
extern int emu_GetPad(void);
extern int emu_ReadAnalogJoyX(int min, int max);
extern int emu_ReadAnalogJoyY(int min, int max);
extern int emu_ReadI2CKeyboard(void);
extern void emu_KeyboardOnUp(int keymodifer, int key);
extern void emu_KeyboardOnDown(int keymodifer, int key);

extern void emu_sndPlaySound(int chan, int volume, int freq);
extern void emu_sndPlayBuzz(int size, int val);
extern void emu_sndInit();
extern void emu_resetus(void);
extern int emu_us(void);

extern int emu_setKeymap(int index);

extern void emu_FileTempInit(void); 
extern void emu_FileTempRead(int addr, unsigned char * val, int n); 
extern void emu_FileTempWrite(int addr, unsigned char val); 
extern void emu_printh(int val);


#endif