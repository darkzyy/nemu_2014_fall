#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"

make_helper(concat(jmp_rel_,SUFFIX)) {
	int tmp=instr_fetch(eip+1,DATA_BYTE);
	print_asm("jmp" " %x",eip+1+DATA_BYTE+tmp);
	cpu.eip+=tmp;
	return 1+DATA_BYTE;
}


#include "exec/template-end.h"
