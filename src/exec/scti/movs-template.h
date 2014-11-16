#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"

make_helper(concat(movs_m_,SUFFIX)) {
	MEM_W(reg_l(R_EDI),MEM_R(reg_l(R_ESI)));
	if(cpu.EFLAGS.DF==1){
		reg_l(R_EDI)-=DATA_BYTE;
		reg_l(R_ESI)-=DATA_BYTE;
	}
	else{
		reg_l(R_EDI)+=DATA_BYTE;
		reg_l(R_ESI)+=DATA_BYTE;
	}
	print_asm("movs" str(SUFFIX) " %%%s,%%%s",REG_NAME(R_ESI),REG_NAME(R_EDI));
	return 1;
}

#include "exec/template-end.h"
