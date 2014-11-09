#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"
#include "exec/flags.h"

make_helper(concat(neg_,SUFFIX)){
	ModR_M m;
	m.val = instr_fetch(eip+1,1);
	if(m.mod==3){
		DATA_TYPE_S tmp=REG(m.R_M);
		if(tmp==0)
			cpu.EFLAGS.CF=0;
		else
			cpu.EFLAGS.CF=1;
		flag_of(0,tmp,'-',DATA_BYTE);
		tmp=-tmp;
		REG(m.R_M)=tmp;
		flag_sf(tmp,DATA_BYTE);
		flag_zf(tmp,DATA_BYTE);
		flag_pf(tmp);
		print_asm("neg" str(SUFFIX) " %%%s", REG_NAME(m.R_M));
		return 1+1;
	}
	else{
		swaddr_t addr;
		int len=read_ModR_M(eip+1, &addr);
		DATA_TYPE_S tmp=MEM_R(addr);
		if(tmp==0)
			cpu.EFLAGS.CF=0;
		else
			cpu.EFLAGS.CF=1;
		flag_of(0,tmp,'-',DATA_BYTE);
		tmp=-tmp;
		MEM_W(addr,tmp);
		flag_sf(tmp,DATA_BYTE);
		flag_zf(tmp,DATA_BYTE);
		flag_pf(tmp);
		return 1+len;
		print_asm("neg" str(SUFFIX) " %s",ModR_M_asm);
	}
}

#include "exec/template-end.h"
