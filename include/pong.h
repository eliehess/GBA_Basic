#ifndef __GAME_H__
#define __GAME_H__

#include "ball.h"
#include "paddle.h"

#define PADDLE_VELOCITY 2 // 2px per frame
#define PADDLE_HEIGHT 40
#define PADDLE_WIDTH 8

extern void pong();

static inline bool overlapping(Ball* ball, Paddle* paddle) {
	return (ball->x + ball->size) >= paddle->x &&
		ball->x <= (paddle->x + paddle->width) &&
		(ball->y + ball->size) >= paddle->y &&
		ball->y <= (paddle->y + paddle->height);
}

#endif //__GAME_H__