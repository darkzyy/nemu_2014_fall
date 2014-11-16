#include "trap.h"


int main() {
	int a=4,b=3;
	nemu_assert(a%b==1);
	HIT_GOOD_TRAP;

	return 0;
}
