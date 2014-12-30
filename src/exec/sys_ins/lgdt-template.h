#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"

make_helper(concat(lgdt_,SUFFIX)){
	swaddr_t addr = instr_fetch(eip+2,4);
	cpu.GDTR.lim=instr_fetch(addr,2);
	cpu.GDTR.base=instr_fetch(addr+2,4);
	print_asm("lgdt" " 0x%x",addr);
	return 6;
}

#include "exec/template-end.h"
