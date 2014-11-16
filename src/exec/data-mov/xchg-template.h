#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"

make_helper(concat(xchg_r2rm_,SUFFIX)) {
	ModR_M m;
	m.val=instr_fetch(eip+1,1);
	DATA_TYPE tmp;
	if(m.mod==3){
		tmp=REG(m.reg);
		REG(m.reg)=REG(m.R_M);
		REG(m.R_M)=tmp;
		print_asm("xchg" str(SUFFIX) " %%%s,%%%s",REG_NAME(m.reg),REG_NAME(m.R_M));
		return 1+1;
	}
	else{
		swaddr_t addr;
		int len=read_ModR_M(eip+1,&addr);
		tmp=REG(m.reg);
		REG(m.reg)=MEM_R(addr);
		MEM_W(addr,tmp);
		print_asm("xchg" str(SUFFIX) " %%%s,%s",REG_NAME(m.reg),ModR_M_asm);
		return len+1;
	}
}
make_helper(concat(xchg_r_,SUFFIX)) {
	int8_t opc=instr_fetch(eip,1);
	int8_t mask_op=0x7;
	opc&=mask_op;
	DATA_TYPE tmp;
	tmp=REG(0);
	REG(0)=REG(opc);
	REG(opc)=tmp;
	print_asm("xchg" str(SUFFIX) " %s,%s",REG_NAME(0),REG_NAME(opc));
	return 1;
}

#include "exec/template-end.h"
