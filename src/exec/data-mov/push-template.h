#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"

make_helper(concat(push_r_,SUFFIX)) {
	int8_t opc=instr_fetch(eip,1);
	int8_t mask_op=0x7;
	reg_l(4)-=DATA_BYTE;
	MEM_W(reg_l(4),REG(opc&mask_op));
	print_asm("push" str(SUFFIX) " %%%s",REG_NAME(opc&mask_op));
	return 1;
}
make_helper(concat(push_m_,SUFFIX)) {
	swaddr_t addr;
	int len = read_ModR_M(eip+1,&addr);
	DATA_TYPE tmp=MEM_R(addr);
	reg_l(4)-=DATA_BYTE;
	MEM_W(reg_l(4),tmp);
	print_asm("push" str(SUFFIX) " %s",ModR_M_asm);
	return 1+len;
}


#include "exec/template-end.h"
