#include "gba_drawing.h"
#include "gba_gfx.h"
#include "gba_math.h"

u16 getColor(u8 red, u8 green, u8 blue) {
	// Red, green, and blue can each have one of 31 possible values (i.e. 5 bits)
	// A 16-bit color value contains one alpha, five blue, five green, and 5 red bits
	// ABBBBBGGGGGRRRRR
	return (red & 0x1F) | (green & 0x1F) << 5 | (blue & 0x1F) << 10;
}

void plotPixel(s32 x, s32 y, u16 color) {
	SCREEN_BUFFER[x + (y * SCREEN_W)] = color;
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

	s32 numerator = longest / 2;
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