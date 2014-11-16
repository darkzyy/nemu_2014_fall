#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"

make_helper(concat(jmp_rel_,SUFFIX)) {
	DATA_TYPE_S tmp=instr_fetch(eip+1,DATA_BYTE);
	print_asm("jmp" " 0x%x",eip+1+DATA_BYTE+tmp);
	cpu.eip+=tmp;
	return 1+DATA_BYTE;
}
make_helper(concat(jmp_rm_,SUFFIX)) {
	DATA_TYPE_S tmp;
	ModR_M m;
	m.val=instr_fetch(eip+1,1);
	if(m.mod==3){
		tmp=REG(m.R_M);
		cpu.eip=tmp-2;
		print_asm("jmp" " *%%%s",REG_NAME(m.R_M));
		return 1+1;
	}
	else{
		swaddr_t addr;
		int len=read_ModR_M(eip+1,&addr);
		tmp=MEM_R(addr);
		cpu.eip=tmp-1-len;
		print_asm("jmp" " *%%%s",REG_NAME(m.R_M));
		return 1+len;
	}
}
#include "exec/template-end.h"
