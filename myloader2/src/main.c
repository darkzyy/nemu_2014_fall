#include "trap.h"

extern void loader();

void init() {
	/*perform the remaining initialization*/

	loader();
	nemu_assert(0);
}
