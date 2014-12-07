#include "trap.h"

int add(int i) {
	i++;
	if(i<10) add(i);
	return i;
}

int main() {
	add(0);
	HIT_GOOD_TRAP;

	return 0;
}
