#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"
#include "exec/flags.h"

make_helper(concat(dec_r_,SUFFIX)) {
	int8_t opc=instr_fetch(eip,1);
	int8_t mask_op=0x7;
	DATA_TYPE_S tmp;
	tmp=REG(opc&mask_op);
	flag_of(tmp,1,'_',DATA_BYTE);
	tmp-=1;
	flag_sf(tmp,DATA_BYTE);
	flag_zf(tmp,DATA_BYTE);
	flag_pf(tmp);
	REG(opc&mask_op)=tmp;
	print_asm("dec" str(SUFFIX) " %%%s",REG_NAME(opc&mask_op));
	return 1;
}
make_helper(concat(dec_rm_,SUFFIX)) {
	ModR_M m;
	DATA_TYPE tmp;
	m.val= instr_fetch(eip+1,1);
	if(m.mod==3){
		tmp=REG(m.R_M);
		flag_of(tmp,1,'_',DATA_BYTE);
		tmp-=1;
		flag_sf(tmp,DATA_BYTE);
		flag_zf(tmp,DATA_BYTE);
		flag_pf(tmp);
		REG(m.R_M)=tmp;
		print_asm("dec" str(SUFFIX) " %%%s",REG_NAME(m.R_M));
		return 1+1;
	}
	else{
		swaddr_t addr;
		int len=read_ModR_M(eip+1,&addr);
		tmp=MEM_R(addr);
		flag_of(tmp,1,'_',DATA_BYTE);
		tmp-=1;
		flag_sf(tmp,DATA_BYTE);
		flag_zf(tmp,DATA_BYTE);
		flag_pf(tmp);
		MEM_W(addr,tmp);
		print_asm("dec" str(SUFFIX) " %s",ModR_M_asm);
		return len+1;
	}
}

#include "exec/template-end.h"
