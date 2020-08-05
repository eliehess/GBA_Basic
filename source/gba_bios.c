#include "gba_bios.h"

/*
 * Fires off an ASM call. SWI (software interrupt) instruction is executed using the 0x05 condition,
 * which is the instruction require to trigger the VBlankInterWait interrupt 
 * (http://problemkaputt.de/gbatek.htm#biosfunctions)
 */
void vBlankIntrWait() {
  // 0x5 is VBlankIntrWait in the function table.
  asm volatile("swi 0x05");
}

/*
 * Call when an interrupt is triggered. INT_VBLANK is the only interrupt we care about, so that's
 * all we need to look for. There can only be one function registered with the interrupt handler;
 * if we wanted to handle more than just the INT_VBLANK interrupt, we would need to add more code
 * to test which interrupt has been triggered, and handle it appropriately.
 */
ARM void interruptHandler() {
	REG_IF = INT_VBLANK;
	REG_IFBIOS |= INT_VBLANK;
}

/*
 * Demonstrates how to set up for a VBLANK interrupt to be handled.
 * 1: Disable interrupt manager to prevent interrupts from triggering
 * 2: Register interrupt function
 * 3: Set appropriate display status flags
 * 4: Set expected interrupt flag to INT_VBLANK
 * 5: Re-enable interrupt manager
 */
void registerVBlankIsr() {
	REG_IME = 0x00;
	REG_INTERRUPT = (fnptr) interruptHandler;
	REG_DISPSTAT |= DSTAT_VBL_IRQ;
	REG_IE |= INT_VBLANK;
	REG_IME = 0x01;
}
