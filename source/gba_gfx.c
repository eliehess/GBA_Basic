#include "gba_gfx.h"
#include "gba_drawing.h"

void vsync() {
    while (REG_VCOUNT >= SCREEN_H)
        ;
    while (REG_VCOUNT < SCREEN_H)
        ;
}
