#include "trap.h"

extern void loader();

void init() {
	/* Perform remaining initializations */


	/* Load the program, and jump to it */
	loader();

	/* Should never reach here */
	nemu_assert(0);
}
