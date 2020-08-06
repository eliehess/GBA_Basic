#ifndef __GBA_GFX_H__
#define __GBA_GFX_H__

#include "gba_macros.h"
#include "gba_types.h"
#include "gba_reg.h"

#define REG_DISPLAY_CONTROLLER *((vu32*) (REG_BASE))

// Defines for setting up different video modes
#define VIDEO_MODE_0 0x0000  // Sprite Mode 0
#define VIDEO_MODE_1 0x0001  // Sprite Mode 1
#define VIDEO_MODE_2 0x0002  // Sprite Mode 2
#define VIDEO_MODE_3 0x0003	 // < Mode 3; 240x160 @ 16 bpp
#define VIDEO_MODE_4 0x0004	 // < Mode 4; 240x160 @ 8 bpp
#define VIDEO_MODE_5 0x0005  // < Mode 5; 160x128 @ 16 bpp

// Defines for enabling different backgrounds
#define BG_MODE_0	0x0100
#define BG_MODE_1	0x0200
#define BG_MODE_2	0x0400
#define BG_MODE_3	0x0800

// vcount is used for testing for vertical blank
#define REG_VCOUNT  (*(vu16*) (REG_BASE + 0x06))

#define MEM_PALETTE	((u16*) 0x05000000)  

/*
 * Sychronizes drawing
 */
extern void vsync();

#endif //__GBA_GFX_H__