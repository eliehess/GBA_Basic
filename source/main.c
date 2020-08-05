#include "gba_macros.h"
#include "gba_types.h"
#include "gba_gfx.h"
#include "gba_drawing.h"
#include "gba_input.h"
#include "gba_bios.h"

#include "ball.h"
#include "paddle.h"
#include "game.h"

#define PADDLE_VELOCITY 2 // 2px per frame
#define PADDLE_HEIGHT 40
#define PADDLE_WIDTH 8

int main() {
	//set GBA rendering context to MODE 3 Bitmap Rendering
	REG_DISPLAY_CONTROLLER = VIDEO_MODE_3 | BG_MODE_2;

	registerVBlankIsr();

	Ball ball;
	initBall(&ball, SCREEN_W / 2, SCREEN_H / 2, 10, getColor(31, 31, 31));

	Paddle paddle1;
	initPaddle(&paddle1, 10, 60, PADDLE_WIDTH, PADDLE_HEIGHT, getColor(0, 0, 31));

	Paddle paddle2;
	initPaddle(&paddle2, SCREEN_W - 10 - PADDLE_WIDTH, 60, PADDLE_WIDTH, PADDLE_HEIGHT, getColor(31, 0, 0));

	while (1) {
		vBlankIntrWait();
		pollKeys();

		clearBall(&ball);
		clearPaddle(&paddle1);
		clearPaddle(&paddle2);

		if (overlapping(&ball, &paddle1)) {
			horizontalBounce(&ball);
		} else if (overlapping(&ball, &paddle2)) {
			horizontalBounce(&ball);
		}

		moveBall(&ball);

		if (keyDown(UP)) {
			movePaddle(&paddle1, -PADDLE_VELOCITY);
		} else if (keyDown(DOWN)) {
			movePaddle(&paddle1, PADDLE_VELOCITY);
		}

		if (keyDown(A)) {
			movePaddle(&paddle2, -PADDLE_VELOCITY);
		} else if (keyDown(B)) {
			movePaddle(&paddle2, PADDLE_VELOCITY);
		}

		drawBall(&ball);
		drawPaddle(&paddle1);
		drawPaddle(&paddle2);
	}

	return 0;
}
