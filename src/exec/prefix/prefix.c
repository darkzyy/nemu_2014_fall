#include "exec/helper.h"

#include "nemu.h"

int exec(swaddr_t);
int exec2(swaddr_t);

char suffix = 'l';

make_helper(data_size) {
	suffix = 'w';
	int instr_len = exec(eip + 1);
	suffix = 'l';
	return instr_len + 1;
}

make_helper(new_op) {
	int instr_len2 = exec2(eip + 1);
	return instr_len2 + 1;
}
