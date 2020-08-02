#ifndef __GBA_DRAWING_H__
#define __GBA_DRAWING_H__

#include "gba_types.h"

#define SCREEN_BUFFER ((u16*) (VRAM))

#define SCREEN_W 240
#define SCREEN_H 160

/*
 * Creates a GBA-usable color from red, green, and blue values
 */
extern u16 getColor(u8 red, u8 green, u8 blue);

/*
 * Draws a single pixel with the given x and y coordinates and color
 */
extern void plotPixel(s32 x, s32 y, u16 color);

/*
 * Draws a rectangle with the given (left, top) coordinate, width, height, and color
 */
extern void drawRect(s32 left, s32 top, s32 width, s32 height, u16 color);

/*
 * Draws a line from one given x and y coordinates to the other, with the given color
 */
extern void drawLine(s32 x, s32 y, s32 x2, s32 y2, u16 color);

#endif //__GBA_DRAWING_H__