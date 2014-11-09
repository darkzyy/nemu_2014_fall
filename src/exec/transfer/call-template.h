#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"

make_helper(concat(call_rel_,SUFFIX)) {
	DATA_TYPE_S tmp=instr_fetch(eip+1,DATA_BYTE);
	REG(4)-=DATA_BYTE;
	MEM_W(REG(4),eip+1+DATA_BYTE);
	print_asm("call" " %x",eip+1+DATA_BYTE+tmp);
	cpu.eip+=tmp;
	return 1+DATA_BYTE;
}
make_helper(concat(ret_n_,SUFFIX)) {
	uint32_t mask_ret=0xffffffff;
	if(DATA_BYTE==2)
		mask_ret>>=16;
	cpu.eip=(MEM_R(REG(4))&mask_ret)-1;
	REG(4)+=DATA_BYTE;
	print_asm("ret");
	return 1;
}



#include "exec/template-end.h"
