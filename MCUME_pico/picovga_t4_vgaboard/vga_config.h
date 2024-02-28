#include "platform_config.h"
#include "iopins.h"

// ****************************************************************************
//                                 
//                            VGA configuration
//
// file derived from the PicoVGA project
// https://github.com/Panda381/PicoVGA
// by Miroslav Nemecek
//
// ****************************************************************************

// === Configuration
#define MAXX		320 //640	// max. resolution in X direction (must be power of 4)
#define MAXY		240 //480	// max. resolution in Y direction

#define MAXLINE		525 //700	// max. number of scanlines (including sync and dark lines)

// === Scanline render buffers (800 pixels: default size of buffers = 2*4*(800+8+800+24)+800 = 13856 bytes
//    Requirements by format, base layer 0, 1 wrap X segment:
//	GF_GRAPH8 ... control buffer 4*4=16 bytes
#define	CBUF_MAX	8 //((MAXX+24)/4)	// max. size of control buffer of layer 0

//TP - this needs a re-code
// === VGA port pins
//	GP0 ... VGA B0 blue
//	GP1 ... VGA B1
//	GP2 ... VGA G0 green
//	GP3 ... VGA G1
//	GP4 ... VGA G2
//	GP5 ... VGA R0 red
//	GP6 ... VGA R1
//	GP7 ... VGA R2
//	GP8 ... VGA SYNC synchronization (inverted: negative SYNC=LOW=0x80, BLACK=HIGH=0x00)
//TP - I have a sneaky feeling I will need to redo this for the pico demo board as they don't just +1
//need to make sure don't mix PIN with GPIO number
// GP0 ... VGA R0 red
// GP1 ... VGA R1
// GP2 ... VGA R2
// GP3 ... VGA R3
// GP4 ... VGA R4
//
// GP6 ... VGA G0 green
// GP7 ... VGA G1
// GP8 ... VGA G2
// GP9 ... VGA G3
// GP10... VGA G4
//
// GP11... VGA B0 blue
// GP12... VGA B1
// GP13... VGA B2
// GP14... VGA B3
// GP15... VGA B4
//
// GP16... HSYNC
// GP17... VSYNC
#define VGA_GPIO_FIRST  VGABOARD_VGA_COLOR_PIN_BASE //TP added pico demo board values
#define VGA_GPIO0_R0	0
#define VGA_GPIO1_R1	1
#define VGA_GPIO2_R2	2
#define VGA_GPIO3_R3	3
#define VGA_GPIO4_R4	4

#define VGA_GPIO6_G0	6
#define VGA_GPIO7_G1	7
#define VGA_GPIO8_G2	8
#define VGA_GPIO9_G3	9
#define VGA_GPIO10_G4	10

#define VGA_GPIO11_B0	11
#define VGA_GPIO12_B1	12
#define VGA_GPIO13_B2	13
#define VGA_GPIO14_B3	14
#define VGA_GPIO15_B4	15

#define VGA_GPIO_FIRST	0 //VGA_COLORBASE	// first VGA GPIO
#define VGA_GPIO_NUM	17 //9	// number of VGA GPIOs, including HSYNC and VSYNC
#define VGA_GPIO_OUTNUM	15 //8	// number of VGA color GPIOs, without HSYNC and VSYNC
#define VGA_GPIO_LAST	(VGA_GPIO_FIRST+VGA_GPIO_NUM-1)	// last VGA GPIO
#define VGA_GPIO_SYNC	VGABOARD_VGA_SYNC_PIN_BASE //TP added pico demo board values
//#define VGA_GPIO_SYNC	VGA_SYNCBASE	// VGA SYNC GPIO

// === VGA PIO program
#define BASE_OFFSET	17	// offset of base layer program

// VGA PIO and state machines
#define VGA_PIO		pio0//1	// VGA PIO    -TP, was pio0 changed to pio1, but showed nothing and broke sdcard access
#define VGA_SM0		0	// VGA state machine of base layer 0

// LAYERS==1
#define VGA_SMALL	B0	// mask of all state machines


// VGA DMA
#define VGA_DMA		2		// VGA DMA base channel
#define VGA_DMA_CB0	(VGA_DMA+0)	// VGA DMA channel - control block of base layer
#define VGA_DMA_PIO0	(VGA_DMA+1)	// VGA DMA channel - copy data of base layer to PIO (raises IRQ0 on quiet)

#define VGA_DMA_NUM	(LAYERS*2)	// number of used DMA channels
#define VGA_DMA_FIRST	VGA_DMA		// first used DMA
#define VGA_DMA_LAST	(VGA_DMA_FIRST+VGA_DMA_NUM-1) // last used DMA
