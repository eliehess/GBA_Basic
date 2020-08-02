#ifndef __GBA_REG_H__
#define __GBA_REG_H__

/*
* Define the base address for External (on-board) work RAM (WRAM)
* This is 256K in Size
*/
#define	EWRAM       0x02000000
#define	EWRAM_END	0x02040000 // From this address up to 0x02FFFFFF is not utilised
/*
* Define the base address for internal (on-chip) work RAM (WRAM)
* This is 32K in Size
*/
#define IWRAM       0x03000000
/*
* Define the base address for I/O or hardware registers
*
*/
#define REG_BASE    0x04000000
/*
* Define the base address for video RAM (VRAM)
* This is 96K in Size
*/
#define VRAM        0x06000000
/*
* Define the base address for cart save RAM (VRAM)
* This is 64K (Max) in Size
*/
#define	SRAM		0x0E000000

#endif //__GBA_REG_H__