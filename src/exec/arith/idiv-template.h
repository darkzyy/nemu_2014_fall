#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"

make_helper(concat(idiv_rm2r_,SUFFIX)){
	ModR_M m;
	m.val = instr_fetch(eip+1,1);
	if(m.mod==3){
		DATA_TYPE_S tmp1_,tmp2_;
		int64_t tmp1,tmp2,tmp3;
		if(DATA_BYTE==1){
			tmp1_=reg_w(0);
			tmp1=tmp1_;
		}
		else{
			tmp1_=REG(0);
			tmp2_=REG(2);
			tmp1=tmp1_;
			tmp2=tmp2_;
			tmp1=tmp1|(tmp2<<8*DATA_BYTE);
		}
		tmp2_=REG(m.R_M);
		tmp2=tmp2_;
		tmp3=tmp1%tmp2;
		tmp1/=tmp2;
		REG(0)=tmp1;
		REG(2)=tmp3;
		print_asm("idiv" str(SUFFIX) " %%%s,%%%s", REG_NAME(m.R_M), REG_NAME(0));
		return 1+1;
	}
	else{
		swaddr_t addr;
		int len=read_ModR_M(eip+1, &addr);
		DATA_TYPE_S tmp1_,tmp2_;
		int64_t tmp1,tmp2,tmp3;
		if(DATA_BYTE==1){
			tmp1_=reg_w(0);
			tmp1=tmp1_;
		}
		else{
			tmp1_=REG(0);
			tmp2_=REG(2);
			tmp1=tmp1_;
			tmp2=tmp2_;
			tmp1=tmp1|(tmp2<<8*DATA_BYTE);
		}
		tmp2_=MEM_R(addr);
		tmp2=tmp2_;
		tmp3=tmp1%tmp2;
		tmp1/=tmp2;
		REG(0)=tmp1;
		REG(2)=tmp3;
		print_asm("idiv" str(SUFFIX) " %s,%%%s",ModR_M_asm, REG_NAME(0));
		return 1+len;
	}
}

#include "exec/template-end.h"
