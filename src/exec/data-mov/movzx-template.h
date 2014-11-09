#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"

make_helper(concat(movzb_,SUFFIX)) {
	ModR_M m;
	m.val = instr_fetch(eip + 1,1);
	if(m.mod == 3){
		return 2;
	}
	else {
		swaddr_t addr;
		int len =read_ModR_M(eip + 1, &addr);
		REG(m.reg) = MEM_R(addr);
		print_asm("movzb" str(SUFFIX) " %s,%%%s", ModR_M_asm, REG_NAME(m.reg));
		return len + 1;
	}
}

make_helper(concat(movzw_,SUFFIX)) {
	ModR_M m;
	m.val = instr_fetch(eip + 1,1);
	if(m.mod == 3){
		return 2;
	}
	else {
		uint32_t mask_0ext=0x0000ffff;
		swaddr_t addr;
		int len =read_ModR_M(eip + 1, &addr);
		REG(m.reg) = MEM_R(addr)&mask_0ext;
		print_asm("movzw" str(SUFFIX) " %s,%%%s", ModR_M_asm, REG_NAME(m.reg));
		return len + 1;
	}
}

#include "exec/template-end.h"
