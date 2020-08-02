#include "ball.h"
#include "gba_drawing.h"
#include "gba_math.h"

void initBall(Ball* ball, s32 x, s32 y, s32 size, u16 color) {
	ball->x = x;
	ball->y = y;
	ball->size = size;
	ball->color = color;
	startBall(ball);
}

void startBall(Ball* ball) {
	// The ball cannot have an x velocity of 0
	while (ball->dx == 0) {
		ball->dx = getRandomInRange(-1, 2);
	}
	ball->dy = getRandomInRange(-1, 2);
}

void moveBall(Ball* ball) {
	ball->y += ball->dy;

	// Bounce off top
	if (ball->y < 0) {
		ball->y = 0;
		ball->dy *= -1;
	}

	// Bounce off bottom
	if (ball->y > SCREEN_H - ball->size) {
		ball->y = SCREEN_H - ball->size;
		ball->dy *= -1;
	}

	ball->x += ball->dx;

	// Return to center if touching a side
	if (ball->x < 0 || ball->x > (SCREEN_W - ball->size)) {
		ball->x = (SCREEN_W / 2) - (ball->size / 2);
		ball->y = (SCREEN_H / 2) - (ball->size / 2);
		ball->dx = 0;
		ball->dy = 0;
		startBall(ball);
	}
}

void drawBall(Ball* ball) {
	drawRect(ball->x, ball->y, ball->size, ball->size, ball->color);
}

void clearBall(Ball* ball) {
	// Draws a black square over the ball. Not the most elegant solution, but it works.
	drawRect(ball->x, ball->y, ball->size, ball->size, getColor(0, 0, 0));
}
