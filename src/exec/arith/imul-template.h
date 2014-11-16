#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"

make_helper(concat(imul_rm2r_,SUFFIX)){
	ModR_M m;
	m.val = instr_fetch(eip+1,1);
	DATA_TYPE_S mask_=-1;
	uint64_t mask=mask_;
	if(m.mod==3){
		DATA_TYPE_S tmp1_,tmp2_;
		int64_t tmp1,tmp2;
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
		tmp1_=tmp1;
		tmp2=tmp1_;
		if(tmp2==tmp1){
			cpu.EFLAGS.CF=0;
			cpu.EFLAGS.OF=0;
		}
		else{
			cpu.EFLAGS.CF=1;
			cpu.EFLAGS.OF=1;
		}
		print_asm("imul" str(SUFFIX) " %%%s,%%%s", REG_NAME(m.R_M), REG_NAME(0));
		return 1+1;
	}
	else{
		swaddr_t addr;
		int len=read_ModR_M(eip+1, &addr);
		DATA_TYPE_S tmp1_,tmp2_;
		int64_t tmp1,tmp2;
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
		tmp1_=tmp1;
		tmp2=tmp1_;
		if(tmp2==tmp1){
			cpu.EFLAGS.CF=0;
			cpu.EFLAGS.OF=0;
		}
		else{
			cpu.EFLAGS.CF=1;
			cpu.EFLAGS.OF=1;
		}
		print_asm("imul" str(SUFFIX) " %s,%%%s",ModR_M_asm, REG_NAME(0));
		return 1+len;
	}
}
make_helper(concat(imul_rm2re_,SUFFIX)){
	ModR_M m;
	m.val = instr_fetch(eip+1,1);
	//DATA_TYPE_S mask_=-1;
	//uint64_t mask=mask_;
	if(m.mod==3){
		DATA_TYPE_S tmp1_,tmp2_;
		int64_t tmp1,tmp2;
		tmp1_=REG(m.R_M);
		tmp2_=REG(m.reg);
		tmp1=tmp1_;
		tmp2=tmp2_;
		tmp1*=tmp2;
		REG(m.reg)=tmp1;//如果出错，检查这样赋值是否有问题
		tmp1_=tmp1;
		tmp2=tmp1_;
		if(tmp2==tmp1){
			cpu.EFLAGS.CF=0;
			cpu.EFLAGS.OF=0;
		}
		else{
			cpu.EFLAGS.CF=1;
			cpu.EFLAGS.OF=1;
		}
		print_asm("imul" str(SUFFIX) " %%%s,%%%s", REG_NAME(m.R_M), REG_NAME(m.reg));
		return 1+1;
	}
	else{
		swaddr_t addr;
		int len=read_ModR_M(eip+1, &addr);
		DATA_TYPE_S tmp1_,tmp2_;
		int64_t tmp1,tmp2;
		tmp1_=MEM_R(addr);
		tmp2_=REG(m.reg);
		tmp1=tmp1_;
		tmp2=tmp2_;
		tmp1*=tmp2;
		REG(m.reg)=tmp1;
		tmp1_=tmp1;
		tmp2=tmp1_;
		if(tmp2==tmp1){
			cpu.EFLAGS.CF=0;
			cpu.EFLAGS.OF=0;
		}
		else{
			cpu.EFLAGS.CF=1;
			cpu.EFLAGS.OF=1;
		}
		print_asm("imul" str(SUFFIX) " %s,%%%s",ModR_M_asm, REG_NAME(m.reg));
		return 1+len;
	}
}
make_helper(concat(imul_i82rm_,SUFFIX)) {
	ModR_M m;
	m.val= instr_fetch(eip+1,1);
	if(m.mod==3){
		int64_t tmp1,tmp2,tmp3;
		tmp1=REG(m.R_M);
		tmp2=instr_fetch(eip+1+1,1);
		tmp1*=tmp2;
		REG(m.reg)=tmp1;
		DATA_TYPE_S tmp_,tmp2_;
		tmp_=tmp1;
		tmp3=tmp_;
		if(tmp3==tmp1){
			cpu.EFLAGS.CF=0;
			cpu.EFLAGS.OF=0;
		}
		else{
			cpu.EFLAGS.CF=1;
			cpu.EFLAGS.OF=1;
		}
		tmp2_=tmp2;
		print_asm("imul" str(SUFFIX) " %x,%%%s,%%%s",tmp2_, REG_NAME(m.R_M), REG_NAME(m.reg));
		return 1+1+1;
	}
	else{
		swaddr_t addr;
		int len = read_ModR_M(eip+1,&addr);
		int64_t tmp1,tmp2,tmp3;
		tmp1=MEM_R(addr);
		tmp2=instr_fetch(eip+1+len,1);
		tmp1*=tmp2;
		DATA_TYPE_S tmp_,tmp2_;
		tmp_=tmp1;
		tmp3=tmp_;
		if(tmp3==tmp1){
			cpu.EFLAGS.CF=0;
			cpu.EFLAGS.OF=0;
		}
		else{
			cpu.EFLAGS.CF=1;
			cpu.EFLAGS.OF=1;
		}
		tmp2_=tmp2;
		print_asm("imul" str(SUFFIX) " %x,%s,%%%s",tmp2_,ModR_M_asm , REG_NAME(m.reg));
		return 1+len+1;
	}
}
make_helper(concat(imul_i2rm_,SUFFIX)) {
	ModR_M m;
	m.val= instr_fetch(eip+1,1);
	if(m.mod==3){
		int64_t tmp1,tmp2,tmp3;
		tmp1=REG(m.R_M);
		tmp2=instr_fetch(eip+1+1,DATA_BYTE);
		tmp1*=tmp2;
		REG(m.reg)=tmp1;
		DATA_TYPE_S tmp_,tmp2_;
		tmp_=tmp1;
		tmp3=tmp_;
		if(tmp3==tmp1){
			cpu.EFLAGS.CF=0;
			cpu.EFLAGS.OF=0;
		}
		else{
			cpu.EFLAGS.CF=1;
			cpu.EFLAGS.OF=1;
		}
		tmp2_=tmp2;
		print_asm("imul" str(SUFFIX) " %x,%%%s,%%%s",tmp2_, REG_NAME(m.R_M), REG_NAME(m.reg));
		return 1+1+DATA_BYTE;
	}
	else{
		swaddr_t addr;
		int len = read_ModR_M(eip+1,&addr);
		int64_t tmp1,tmp2,tmp3;
		tmp1=MEM_R(addr);
		tmp2=instr_fetch(eip+1+len,DATA_BYTE);
		tmp1*=tmp2;
		DATA_TYPE_S tmp_,tmp2_;
		tmp_=tmp1;
		tmp3=tmp_;
		if(tmp3==tmp1){
			cpu.EFLAGS.CF=0;
			cpu.EFLAGS.OF=0;
		}
		else{
			cpu.EFLAGS.CF=1;
			cpu.EFLAGS.OF=1;
		}
		tmp2_=tmp2;
		print_asm("imul" str(SUFFIX) " %x,%s,%%%s",tmp2_,ModR_M_asm , REG_NAME(m.reg));
		return 1+len+DATA_BYTE;
	}
}

#include "exec/template-end.h"
