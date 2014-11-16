#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"

make_helper(concat(call_rel_,SUFFIX)) {
	DATA_TYPE_S tmp=instr_fetch(eip+1,DATA_BYTE);
	reg_l(4)-=DATA_BYTE;
	MEM_W(reg_l(4),eip+1+DATA_BYTE);
	print_asm("call" " 0x%x",eip+1+DATA_BYTE+tmp);
	cpu.eip+=tmp;
	return 1+DATA_BYTE;
}
make_helper(concat(call_rm_,SUFFIX)) {
	DATA_TYPE_S tmp;
	ModR_M m;
	m.val=instr_fetch(eip+1,1);
	if(m.mod==3) {
		tmp=REG(m.R_M);
		reg_l(4)-=DATA_BYTE;
		MEM_W(reg_l(4),eip+1+1);
		print_asm("call" "0x%x",eip+1+1+tmp);
		return 1+1;
	}
	else{
		swaddr_t addr;
		int len =read_ModR_M(eip+1,&addr);
		tmp=MEM_R(addr);
		reg_l(4)-=DATA_BYTE;
		MEM_W(reg_l(4),eip+1+len);
		print_asm("call" "0x%x",eip+1+len+tmp);
		return 1+len;
	}
}


make_helper(concat(ret_n_,SUFFIX)) {
	uint32_t mask_ret=0xffffffff;
	if(DATA_BYTE==2)
		mask_ret>>=16;
	cpu.eip=(MEM_R(REG(4))&mask_ret)-1;
	reg_l(4)+=DATA_BYTE;
	print_asm("ret");
	return 1;
}
make_helper(concat(ret_ni_,SUFFIX)) {
	uint32_t mask_ret=0xffffffff;
	int16_t imm=instr_fetch(eip+1,2);
	if(DATA_BYTE==2)
		mask_ret>>=16;
	cpu.eip=(MEM_R(REG(4))&mask_ret)-3;
	reg_l(4)+=DATA_BYTE;
	reg_l(4)+=imm;
	print_asm("ret %d",imm);
	return 1+2;
}



#include "exec/template-end.h"
