#include <string.h>

#include "bitmap.h"
#include "gba_input.h"
#include "gba_drawing.h"
#include "gba_gfx.h"
#include "gba_bios.h"

#include "img_gba_m3.h"
#include "img_gba_m4.h"
#include "img_gba_m5.h"

void bitmap() {
	u16 vidMode = VIDEO_MODE_3;

	memcpy(SCREEN_BUFFER, img_gbaM3Bitmap, img_gbaM3BitmapLen);
	REG_DISPLAY_CONTROLLER = VIDEO_MODE_3 | BG_MODE_2;

	registerVBlankIsr();

    while (1) {
		vBlankIntrWait();

        pollKeys();

        if (keyReleased(A)) {
            vidMode += 1;
            if (vidMode > VIDEO_MODE_5) {
                vidMode = VIDEO_MODE_3;
            }

            switch (vidMode) {
                case VIDEO_MODE_3: {
                    memcpy(SCREEN_BUFFER, img_gbaM3Bitmap, img_gbaM3BitmapLen);
                    break;
                }
                case VIDEO_MODE_4: {
                    memcpy(SCREEN_BUFFER, img_gba_m4_bitmap, img_gba_m4BitmapLen);
                    memcpy(MEM_PALETTE, img_gba_m4_pal, img_gba_m4PalLen);
                    break;
                }
                case VIDEO_MODE_5: {
                    memcpy(SCREEN_BUFFER, img_gba_m5Bitmap, img_gba_m5BitmapLen);
                    break;
                }
                default:
                    break;
            }
            REG_DISPLAY_CONTROLLER = vidMode | BG_MODE_2;
        }
    }
}