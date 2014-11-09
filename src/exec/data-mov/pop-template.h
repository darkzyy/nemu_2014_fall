#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"

make_helper(concat(leave_,SUFFIX)) {
	reg_l(4)=reg_l(5);
	reg_l(5)=MEM_R(reg_l(4));
	reg_l(4)+=DATA_BYTE;
	print_asm("leave");
	return 1;
}
make_helper(concat(pop_r_,SUFFIX)) {
	int8_t opc=instr_fetch(eip,1);
	int8_t mask_op=0x7;
	REG(opc&mask_op)=MEM_R(reg_l(4));
	reg_l(4)+=DATA_BYTE;
	print_asm("pop" str(SUFFIX) " %%%s",REG_NAME(opc&mask_op));
	return 1;
}
make_helper(concat(pop_m_,SUFFIX)) {
	swaddr_t addr;
	int len=read_ModR_M(eip+1,&addr);
	DATA_TYPE tmp= MEM_R(reg_l(4));
	MEM_W(addr,tmp);
	reg_l(4)+=DATA_BYTE;
	print_asm("push" str(SUFFIX) " %s",ModR_M_asm);
	return 1+len;
}



#include "exec/template-end.h"
