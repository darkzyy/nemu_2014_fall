#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"

make_helper(concat(movsb_,SUFFIX)) {
	ModR_M m;
	m.val = instr_fetch(eip + 1,1);
	int8_t tmp;
	if(m.mod == 3){
		tmp=REG(m.R_M);
		REG(m.reg)=tmp;
		print_asm("movsb" str(SUFFIX) " %%%s,%%%s",REG_NAME(m.R_M),REG_NAME(m.reg));
		return 2;
	}
	else {
		swaddr_t addr;
		int len =read_ModR_M(eip + 1, &addr);
		tmp = MEM_R(addr);
		REG(m.reg)=tmp;
		print_asm("movsb" str(SUFFIX) " %s,%%%s", ModR_M_asm, REG_NAME(m.reg));
		return len + 1;
	}
}

make_helper(concat(movsw_,SUFFIX)) {
	ModR_M m;
	m.val = instr_fetch(eip + 1,1);
	int16_t tmp;
	if(m.mod == 3){
		tmp=REG(m.R_M);
		REG(m.reg)=tmp;
		print_asm("movsw" str(SUFFIX) " %%%s,%%%s", REG_NAME(m.R_M), REG_NAME(m.reg));
		return 2;
	}
	else {
		swaddr_t addr;
		int len =read_ModR_M(eip + 1, &addr);
		tmp = MEM_R(addr);
		REG(m.reg)=tmp;
		print_asm("movsw" str(SUFFIX) " %s,%%%s", ModR_M_asm, REG_NAME(m.reg));
		return len + 1;
	}
}

#include "exec/template-end.h"
