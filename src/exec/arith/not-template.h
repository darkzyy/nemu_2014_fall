#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"
#include "exec/flags.h"

make_helper(concat(not_,SUFFIX)){
	ModR_M m;
	m.val = instr_fetch(eip+1,1);
	if(m.mod==3){
		DATA_TYPE_S tmp=REG(m.R_M);
		tmp=~tmp;
		REG(m.R_M)=tmp;
		print_asm("not" str(SUFFIX) " %%%s", REG_NAME(m.R_M));
		return 1+1;
	}
	else{
		swaddr_t addr;
		int len=read_ModR_M(eip+1, &addr);
		DATA_TYPE_S tmp=MEM_R(addr);
		tmp=~tmp;
		MEM_W(addr,tmp);
		return 1+len;
		print_asm("not" str(SUFFIX) " %s",ModR_M_asm);
	}
}

#include "exec/template-end.h"
