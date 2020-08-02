#include "gba_macros.h"
#include "gba_types.h"
#include "gba_gfx.h"
#include "gba_drawing.h"

#include "ball.h"
#include "paddle.h"

int main() {
	//set GBA rendering context to MODE 3 Bitmap Rendering
	REG_DISPLAY_CONTROLLER = VIDEO_MODE_3 | BG_MODE_2;

	Ball ball;
	initBall(&ball, SCREEN_W / 2, SCREEN_H / 2, 10, getColor(31, 31, 31));

	Paddle paddle1;
	initPaddle(&paddle1, 10, 60, 8, 40, getColor(0, 0, 31));

	Paddle paddle2;
	initPaddle(&paddle2, SCREEN_W - 10, 60, 8, 40, getColor(31, 0, 0));

	while (1) {
		vsync();

		clearBall(&ball);
		clearPaddle(&paddle1);
		clearPaddle(&paddle2);

		moveBall(&ball);

		drawBall(&ball);
		drawPaddle(&paddle1);
		drawPaddle(&paddle2);
	}

	return 0;
}
