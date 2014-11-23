#include "trap.h"

int is_leap_year(int n) {
	return (n % 4 == 0 && n% 100 !=0) ||(n% 400==0);
}

int main() {
	int a=1900;
	nemu_assert(is_leap_year(a)==0);
	HIT_GOOD_TRAP;

	return 0;
}
