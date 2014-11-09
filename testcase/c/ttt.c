#include "trap.h"


int main() {
	int c=3;
	c++;
	nemu_assert(c==4);

	HIT_GOOD_TRAP;

	return 0;
}
