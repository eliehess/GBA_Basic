#include "Intellisense.h"
#include <stdint.h>
#include <stdbool.h>

typedef uint8_t		u8;
typedef uint16_t	u16;
typedef uint32_t	u32;
typedef int8_t		s8;
typedef int16_t		s16;
typedef int32_t		s32;

typedef volatile uint8_t	vu8;
typedef volatile uint16_t	vu16;
typedef volatile uint32_t	vu32;
typedef volatile int8_t		vs8;
typedef volatile int16_t	vs16;
typedef volatile int32_t	vs32;

#define SCREEN_W 240
#define SCREEN_H 160

#define REG_DISPLAY_CONTROLLER *((vu32*) 0x4000000)
#define VIDEO_MODE_3 0x0003
#define BG_ENABLE_2  0x0400

#define SCREEN_BUFFER ((vu16*) 0x06000000)

#define REG_VCOUNT (*(vu16*) (0x04000006))

typedef struct Ball {
	s32 x, y, dx, dy, size;
	u16 color;
} Ball;

typedef struct Paddle {
	s32 x, y, width, height;
	u16 color;
} Paddle;

static inline u16 getColor(u8 red, u8 green, u8 blue);
static inline s32 abs(s32 val);
static inline void vsync();

s32 setRandomSeed(s32 seed);
s32 getRandom();
s32 getRandomInRange(s32 min, s32 max);

void startBall(Ball* ball);
void initBall(Ball* ball, s32 x, s32 y, s32 size, u16 color);
void moveBall(Ball* ball);
void drawBall(Ball* ball);
void clearBall(Ball* ball);

void initPaddle(Paddle* paddle, s32 x, s32 y, s32 width, s32 height, u16 color);
void drawPaddle(Paddle* paddle);
void clearPaddle(Paddle* paddle);

void plotPixel(s32 x, s32 y, u16 color);
void drawRect(s32 left, s32 top, s32 width, s32 height, u16 color);
void drawLine(s32 x, s32 y, s32 x2, s32 y2, u16 color);

s32 gba_rand_seed = 42;

int main() {
	//set GBA rendering context to MODE 3 Bitmap Rendering
	REG_DISPLAY_CONTROLLER = VIDEO_MODE_3 | BG_ENABLE_2;

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

void startBall(Ball* ball) {
	while (ball->dx == 0) {
		ball->dx = getRandomInRange(-1, 2);
	}
	ball->dy = getRandomInRange(-1, 2);
}

void initBall(Ball* ball, s32 x, s32 y, s32 size, u16 color) {
	ball->x = x;
	ball->y = y;
	ball->size = size;
	ball->color = color;
	startBall(ball);
}

void moveBall(Ball* ball) {
	ball->y += ball->dy;

	if (ball->y < 0) {
		ball->y = 0;
		ball->dy *= -1;
	}

	if (ball->y > SCREEN_H - ball->size) {
		ball->y = SCREEN_H - ball->size;
		ball->dy *= -1;
	}

	ball->x += ball->dx;

	if (ball->x < 0 || ball->x > SCREEN_W - ball->size) {
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
	drawRect(ball->x, ball->y, ball->size, ball->size, getColor(0, 0, 0));
}

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
	drawRect(paddle->x, paddle->y, paddle->width, paddle->height, getColor(0, 0, 0));
}

s32 setRandomSeed(s32 seed) {
	s32 old_seed = gba_rand_seed;
	gba_rand_seed = seed;
	return old_seed;
}

s32 getRandom() {
	gba_rand_seed = 1664525 * gba_rand_seed + 1013904223;
	return (gba_rand_seed >> 16) & 0x7FFF;
}

s32 getRandomInRange(s32 min, s32 max) {
	return (getRandom() * (max - min) >> 15) + min;
}

void plotPixel(s32 x, s32 y, u16 color) {
	SCREEN_BUFFER[(y * SCREEN_W) + x] = color;
}

void drawRect(s32 left, s32 top, s32 width, s32 height, u16 color) {
	for (s32 y = 0; y < height; y++) {
		for (s32 x = 0; x < width; x++) {
			plotPixel(left + x, top + y, color);
		}
	}
}

void drawLine(s32 x1, s32 y1, s32 x2, s32 y2, u16 color) {
	s32 w = x2 - x1;
	s32 h = y2 - y1;

	s32 dx1 = 0, dx2 = 0, dy1 = 0, dy2 = 0;

	if (w < 0) 
		dx1 = dx2 = -1;
	else if (w > 0) 
		dx1 = dx2 = 1;

	if (h < 0)
		dy1 = dy2 = -1;
	else if (h > 0)
		dy1 = dy2 = 1;

	s32 longest = abs(w);
	s32 shortest = abs(h);

	if (shortest > longest) {
		//swap values without creating a new variable
		longest ^= shortest;
		shortest ^= longest;
		longest ^= shortest;

		if (h < 0) 
			dy2 = -1;
		else if (h > 0) 
			dy2 = 1;
		
		dx2 = 0;
	}

	s32 numerator = longest >> 1;
	for (s32 i = 0; i <= longest; i++) {
		plotPixel(x1, y1, color);

		numerator += shortest;
		if (numerator > longest) {
			numerator -= longest;
			x1 += dx1;
			y1 += dy1;
		} else {
			x1 += dx2;
			y1 += dy2;
		}
	}
}

static inline s32 abs(s32 val) {
	s32 mask = val >> 31;
	return (val ^ mask) - mask;
}

static inline u16 getColor(u8 red, u8 green, u8 blue) {
	return (red & 0x1F) | (green & 0x1F) << 5 | (blue & 0x1F) << 10;
}

static inline void vsync() {
	while (REG_VCOUNT >= SCREEN_H);
	while (REG_VCOUNT < SCREEN_H);
}
