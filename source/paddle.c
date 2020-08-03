#include "paddle.h"
#include "gba_drawing.h"

void initPaddle(Paddle* paddle, s32 x, s32 y, s32 width, s32 height, u16 color) {
	paddle->x = x;
	paddle->y = y;
	paddle->width = width;
	paddle->height = height;
	paddle->color = color;
}

void drawPaddle(Paddle* paddle) {
	drawRect(paddle->x, paddle->y, paddle->width, paddle->height, paddle->color);
}

void clearPaddle(Paddle* paddle) {
	// Draws a black square over the paddle. Not the most elegant solution, but it works.
	drawRect(paddle->x, paddle->y, paddle->width, paddle->height, getColor(0, 0, 0));
}

void movePaddle(Paddle* paddle, s32 val) {
	paddle->y += val;
	if (paddle->y < 0) {
		paddle->y = 0;
	}

	if (paddle->y > (SCREEN_H - paddle->height)) {
		paddle->y = SCREEN_H - paddle->height;
	}
}
