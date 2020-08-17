#ifndef __MARIO_H__
#define __MARIO_H__

#include "gba_types.h"

#define MARIO_X_POS 20
#define MARIO_Y_POS 20
#define MARIO_HEIGHT 90
#define MARIO_WIDTH 70

/*
 * Copies bitmap data to screen based on width and height
 */
extern void copyBitmapToPageLocation(u16* vidPage, const u16* bitmap, s16 width, s16 height, s16 xOffset, s16 yOffset);

extern void mario();

extern u16* pageFlip();

#endif //__MARIO_H__