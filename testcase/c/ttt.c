#include "trap.h"


int main() {
	unsigned int c=3,d=4;
	c=c*d;
	nemu_assert(c==12);

	HIT_GOOD_TRAP;

	return 0;
}
