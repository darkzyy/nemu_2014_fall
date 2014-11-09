#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"

make_helper(concat(mul_rm2r_,SUFFIX)){
	ModR_M m;
	m.val = instr_fetch(eip+1,1);
	DATA_TYPE_S mask_=-1;
	uint64_t mask=mask_;
	if(m.mod==3){
		DATA_TYPE tmp1_,tmp2_;
		uint64_t tmp1,tmp2;
		tmp1_=REG(m.R_M);
		tmp2_=REG(0);
		tmp1=tmp1_;
		tmp2=tmp2_;
		tmp1*=tmp2;
		if(DATA_BYTE==1){
			reg_w(0)=tmp1;
		}
		else{
			REG(0)=tmp1&mask;
			REG(2)=tmp1>>(8*DATA_BYTE);
		}
		if((tmp1>>(8*DATA_BYTE))==0){
			cpu.EFLAGS.CF=0;
			cpu.EFLAGS.OF=0;
		}
		else{
			cpu.EFLAGS.CF=0;
			cpu.EFLAGS.OF=0;
		}
		print_asm("mul" str(SUFFIX) " %%%s,%%%s", REG_NAME(m.R_M), REG_NAME(0));
		return 1+1;
	}
	else{
		swaddr_t addr;
		int len=read_ModR_M(eip+1, &addr);
		DATA_TYPE tmp1_,tmp2_;
		uint64_t tmp1,tmp2;
		tmp1_=MEM_R(addr);
		tmp2_=REG(0);
		tmp1=tmp1_;
		tmp2=tmp2_;
		tmp1*=tmp2;
		if(DATA_BYTE==1){
			reg_w(0)=tmp1;
		}
		else{
			REG(0)=tmp1&mask;
			REG(2)=tmp1>>(8*DATA_BYTE);
		}
		if((tmp1>>(8*DATA_BYTE))==0){
			cpu.EFLAGS.CF=0;
			cpu.EFLAGS.OF=0;
		}
		else{
			cpu.EFLAGS.CF=0;
			cpu.EFLAGS.OF=0;
		}
		return 1+len;
		print_asm("mul" str(SUFFIX) " %s,%%%s",ModR_M_asm, REG_NAME(0));
	}
}

#include "exec/template-end.h"
