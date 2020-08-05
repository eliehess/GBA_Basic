#ifndef __GBA_REG_H__
#define __GBA_REG_H__


// the base address for external (on-board) work RAM (WRAM). 256KB.
#define	EWRAM       0x02000000
#define	EWRAM_END	0x02040000 // From this address up to 0x02FFFFFF is not utilised

// the base address for internal (on-chip) work RAM (WRAM). 32KB.
#define IWRAM       0x03000000

// the base address for I/O or hardware registers
#define REG_BASE    0x04000000

// the base address for video RAM (VRAM). 96KB.
#define VRAM        0x06000000

// the base address for cart save RAM (VRAM). 64KB (max).
#define	SRAM		0x0E000000

#endif //__GBA_REG_H__