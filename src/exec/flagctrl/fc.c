#include "exec/helper.h"

make_helper(std) {
	cpu.EFLAGS.DF=1;
	print_asm("std");
	return 1;
}
make_helper(cld) {
	cpu.EFLAGS.DF=0;
	print_asm("cld");
	return 1;
}
