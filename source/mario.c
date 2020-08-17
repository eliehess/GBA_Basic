#include "gba_macros.h"
#include "gba_types.h"
#include "gba_bios.h"
#include "gba_gfx.h"
#include "gba_drawing.h"
#include "gba_math.h"
#include "gba_input.h"

#include "mario.h"

#include "img_mario_walk_1.h"
#include "img_mario_walk_2.h"
#include "img_mario_walk_3.h"

#include <string.h>

u16* vid_page = vid_page_back;

u16* pageFlip() {
	vid_page = (u16*) ((u32) vid_page ^ VRAM_PAGE_SIZE);
	REG_DISPLAY_CONTROLLER ^= VIDEO_PAGE;	// update control register	
	return vid_page;
}

void mario() {
	registerVBlankIsr();

	// copy color palette into memory
	memcpy(MEM_PALETTE, img_mario_walk_1Pal, img_mario_walk_1PalLen);
	// set background memory to palette color 1. Fill screen with white.
	memset(vid_page_front, img_mario_walk_1Bitmap[0], SCREEN_W * SCREEN_H);
	memset(vid_page_back, img_mario_walk_1Bitmap[0], SCREEN_W * SCREEN_H);
	
	// set GBA rendering context to MODE 4 Bitmap Rendering
	REG_DISPLAY_CONTROLLER = VIDEO_MODE_4 | BG_MODE_2;

	copyBitmapToPageLocation(vid_page_front, img_mario_walk_1Bitmap, MARIO_WIDTH, MARIO_HEIGHT, MARIO_X_POS, MARIO_Y_POS);
	copyBitmapToPageLocation(vid_page_back, img_mario_walk_2Bitmap, MARIO_WIDTH, MARIO_HEIGHT, MARIO_X_POS, MARIO_Y_POS);
	s8 keyFrame = 0;
	
	while (1) {
		vBlankIntrWait();

		pollKeys();

		if (keyReleased(A)) {
			keyFrame++;
			keyFrame &= 0x3; // Ignore everything except the last two bits. Effectively, bounds keyFrame from 0-3.
			switch (keyFrame) {
				case 1:
					copyBitmapToPageLocation(vid_page_back, img_mario_walk_2Bitmap, MARIO_WIDTH, MARIO_HEIGHT, MARIO_X_POS, MARIO_Y_POS);
					break;
				case 3:
					copyBitmapToPageLocation(vid_page_back, img_mario_walk_3Bitmap, MARIO_WIDTH, MARIO_HEIGHT, MARIO_X_POS, MARIO_Y_POS);
					break;				
				default:
					break;
			}
			pageFlip();
		}
		
	}
}

void copyBitmapToPageLocation(u16* vidPage, const u16* bitmap, s16 width, s16 height, s16 xOffset, s16 yOffset) {
	u16 screenLocation = 0;
	u16 bitmapLocation = 0;
	for (s16 i = 0; i < height; i++) {
		screenLocation = ((yOffset + i) * 120) + xOffset; 
		bitmapLocation = ((i * width) >> 1) + i;

		memcpy(&vidPage[screenLocation], &bitmap[bitmapLocation], width);
	}
}