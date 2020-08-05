#ifndef __GBA_INPUT_H__
#define __GBA_INPUT_H__

#include "gba_reg.h"
#include "gba_types.h"
#include "gba_macros.h"

#define REG_KEY_INPUT	*(vu16*) (REG_BASE + 0x130)
#define REG_KEY_CONTROL	*(vu16*) (REG_BASE + 0x132)

// We're only interested in the lower 10 bits, so we can mask off the rest
#define KEY_MASK 0x03FF

typedef enum KEYS {
	A       = (1 << 0),
	B       = (1 << 1),
	SELECT  = (1 << 2),
	START   = (1 << 3),
	RIGHT   = (1 << 4),
	LEFT    = (1 << 5),
	UP      = (1 << 6),
	DOWN    = (1 << 7),
	R       = (1 << 8),
	L       = (1 << 9),
	// 10-15 unused

	KEYIRQ_ENABLE   = (1 << 14),	/*!< Enable keypad interrupt */
	KEYIRQ_OR       = (0 << 15),	/*!< interrupt logical OR mode */
	KEYIRQ_AND      = (1 << 15),	/*!< interrupt logical AND mode */
} KEYS;

typedef enum AXIS {
	HORIZONTAL = 0,
	VERTICAL = 1,
} AXIS;

extern u16 currentKeys, prevKeys;

static inline void pollKeys() {
	prevKeys = currentKeys;
	currentKeys = ~REG_KEY_INPUT & KEY_MASK;
}

static inline u16 currentKeyState() {
    return currentKeys; 
}

static inline u16 prevKeyState() {
    return prevKeys; 
}

static inline u16 keyDown(u16 key) { 
    return currentKeys & key; 
}

static inline u16 keyUp(u16 key) { 
    return ~currentKeys & key; 
}

static inline u16 keyHeld(u16 key) { 
    return (currentKeys & prevKeys) & key; 
}

static inline u16 keyReleased(u16 key) { 
    return (~currentKeys & prevKeys) & key; 
}

static inline u16 keyHit(u16 key) { 
    return (currentKeys & ~prevKeys) & key; 
}

static inline u16 keyStateChange(u16 key) {
     return (currentKeys ^ prevKeys) & key; 
}

static inline s16 getAxis(AXIS val) {
	switch (val) {
	case HORIZONTAL:
		// Shift currentKeys down 4 to move the value for RIGHT to the lowest bit, and & with 1. Do the same for LEFT and subtract.
		// If right is pressed, the equation becomes 1 - 0 = 1; if left is pressed then 0 - 1 = -1.
		return ((currentKeys >> 4) & 1) - ((currentKeys >> 5) & 1);
	case VERTICAL:
		// This is the same logic as above, but with UP and DOWN.
		return ((currentKeys >> 6) & 1) - ((currentKeys >> 7) & 1);
	default:
		return 0;
	}
}

#endif //__GBA_INPUT_H__