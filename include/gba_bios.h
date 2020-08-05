#ifndef __GBA_BIOS_H__
#define __GBA_BIOS_H__

#include "gba_reg.h"
#include "gba_macros.h"
#include "gba_types.h"

// master interrupt controller 0 off 1 on
#define REG_IME (*(vu16*) (0x4000208))

// interrupts for the display need to be registered here too
// for the display to fire the interrupts off
#define REG_DISPSTAT (*(vu16*) (0x4000004))

// this memory address is where the interrupt funciton pointer will be stored
#define REG_INTERRUPT *(fnptr*) (0x03007FFC)

// this is the BIOS register address that needs to be set to inform the bios 
// that any interrupts it was expecting have been dealt with.
#define REG_IFBIOS (*(vu16*) (0x3007FF8))

// interrupts that are registered or interrupts expected
#define REG_IE  (*(vu16*) (0x4000200))

// interrupt fired
#define REG_IF  (*(vu16*) (0x4000202))

/* 
 * Bits for interrupt registers:
 * 0 LCD V-Blank (0=Disable)
 * 1 LCD H-Blank (etc.)
 * 2 LCD V-Counter Match (etc.)
 * 3 Timer 0 Overflow (etc.)
 * 4 Timer 1 Overflow (etc.)
 * 5 Timer 2 Overflow (etc.)
 * 6 Timer 3 Overflow (etc.)
 * 7 Serial Communication (etc.)
 * 8 DMA 0 (etc.)
 * 9 DMA 1 (etc.)
 * 10 DMA 2 (etc.)
 * 11 DMA 3 (etc.)
 * 12 Keypad (etc.)
 * 13 Game Pak (external IRQ source) (etc.)
 * 14-15 Not used
 */

// Defines for Interrupts
// There are 14 Interrupts that we can register with REG_IE
#define INT_VBLANK 	    0x0001
#define INT_HBLANK 	    0x0002
#define INT_VCOUNT 	    0x0004
#define INT_TIMER0 	    0x0008
#define INT_TIMER1 	    0x0010
#define INT_TIMER2 	    0x0020
#define INT_TIMER3 	    0x0040
#define INT_COM 	    0x0080
#define INT_DMA0 	    0x0100
#define INT_DMA1	    0x0200
#define INT_DMA2 	    0x0400
#define INT_DMA3 	    0x0800
#define INT_BUTTON 	    0x1000
#define INT_CART 	    0x2000
// create pointer to video memory
#define DSTAT_VBL_IRQ   0x0008
#define DSTAT_VHB_IRQ   0x0010
#define DSTAT_VCT_IRQ   0x0020

typedef void (*fnptr) (void);

/*
 * Triggers the VBlank interrupt wait
 */
void vBlankIntrWait();

/*
 * called by the CPU when an interrupt is triggered
 */
ARM void interruptHandler();
/*
 * register a VBLANK Interrupt
 */
void registerVBlankIsr();

#endif //__GBA_BIOS_H__