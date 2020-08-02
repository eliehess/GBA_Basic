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

void plotPixel(s32 x, s32 y, u16 color);
void drawRect(s32 left, s32 top, s32 width, s32 height, u16 color);
void drawLine(s32 x, s32 y, s32 x2, s32 y2, u16 color);

static inline u16 getColor(u8 red, u8 green, u8 blue);
static inline s32 abs(s32 val);

int main() {
	//set GBA rendering context to MODE 3 Bitmap Rendering
	REG_DISPLAY_CONTROLLER = VIDEO_MODE_3 | BG_ENABLE_2;

	drawRect(160, 60, 40, 40, getColor(31, 5, 12));
	drawLine(10, 5, 230, 5, getColor(1, 24, 16));

	/*s32 t = 0;
	while (1) {
		s32 x, y;
		for (x = 0; x < SCREEN_W; x++) {
			for (y = 0; y < SCREEN_H; y++) {
				plotPixel(x, y, setColor((x & y) + (t * 5), ((x & y) + (t * 3)), (x & y) + t));
			}
		}
		t++;
	}*/

	return 0;
}

static inline u16 getColor(u8 red, u8 green, u8 blue) {
	return (red & 0x1F) | (green & 0x1F) << 5 | (blue & 0x1F) << 10;
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
