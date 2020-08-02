#ifndef __PADDLE_H__
#define __PADDLE_H__

#include "gba_types.h"

/* 
 * A rectangular pong paddle
 * Contains: x and y coordinates, width, height, and a color
 */
typedef struct Paddle {
	s32 x, y, width, height;
	u16 color;
} Paddle;

/*
 * Creates a paddle with the specified x and y coordinates, width, height, and color
 */
extern void initPaddle(Paddle* paddle, s32 x, s32 y, s32 width, s32 height, u16 color);

/*
 * Draws a paddle on the screen in its current location
 */
extern void drawPaddle(Paddle* paddle);

/*
 * Removes a paddle from the screen
 */
extern void clearPaddle(Paddle* paddle);

#endif //__PADDLE_H__