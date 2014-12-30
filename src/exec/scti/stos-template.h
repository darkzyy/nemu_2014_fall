#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"

make_helper(concat(stos_,SUFFIX)) {
	MEM_W(reg_l(R_EDI),REG(0));
	if(cpu.EFLAGS.DF == 1)
		reg_l(R_EDI) -= DATA_BYTE;
	else
		reg_l(R_EDI) += DATA_BYTE;
	print_asm("stos" str(SUFFIX) " %%%s,(%%%s)",REG_NAME(0),REG_NAME(R_EDI));
	return 1;
}

#include "exec/template-end.h"
