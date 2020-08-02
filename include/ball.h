#ifndef __BALL_H__
#define __BALL_H__

#include "gba_types.h"

/*
 * A square pong "ball"
 * Contains: x and y coordinates, x and y velocities, a side length, and a color
 */
typedef struct Ball {
	s32 x, y, dx, dy, size;
	u16 color;
} Ball;

/*
 * Creates and starts a ball with the specified x and y coordinates, size, and color
 */
extern void initBall(Ball* ball, s32 x, s32 y, s32 size, u16 color);

/*
 * Starts a ball moving in a random non-vertical direction
 */
extern void startBall(Ball* ball);

/*
 * Moves a ball according to its dx and dy
 */
extern void moveBall(Ball* ball);

/*
 * Draws a ball on the screen in its current location
 */
extern void drawBall(Ball* ball);

/*
 * Removes a ball from the screen
 */
extern void clearBall(Ball* ball);

#endif //__BALL_H__