#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"
#include "exec/flags.h"

make_helper(concat(shl_1_,SUFFIX)) {
	ModR_M m;
	m.val= instr_fetch(eip+1,1);
	DATA_TYPE mask=1;
	if(m.mod==3) {
		DATA_TYPE tmp=REG(m.R_M);
		cpu.EFLAGS.CF=tmp>>(8*DATA_BYTE-1);
		cpu.EFLAGS.OF=(tmp>>(8*DATA_BYTE-1))==((tmp>>(8*DATA_BYTE-2))&mask);
		tmp<<=1;
		REG(m.R_M)=tmp;
		flag_sf(tmp,DATA_BYTE);
		flag_zf(tmp,DATA_BYTE);
		flag_pf(tmp);
		print_asm("shl" str(SUFFIX) " $0x1,%%%s",REG_NAME(m.R_M));
		return 1+1;
	}
	else{
		swaddr_t addr;
		int len=read_ModR_M(eip+1,&addr);
		DATA_TYPE tmp=MEM_R(addr);
		cpu.EFLAGS.CF=tmp>>(8*DATA_BYTE-1);
		cpu.EFLAGS.OF=(tmp>>(8*DATA_BYTE-1))==((tmp>>(8*DATA_BYTE-2))&mask);
		tmp<<=1;
		MEM_W(addr,tmp);
		flag_sf(tmp,DATA_BYTE);
		flag_zf(tmp,DATA_BYTE);
		flag_pf(tmp);
		print_asm("shl" str(SUFFIX) " $0x1,%s",ModR_M_asm);
		return 1+len;
	}
}
make_helper(concat(shl_c_,SUFFIX)) {
	ModR_M m;
	m.val= instr_fetch(eip+1,1);
	DATA_TYPE mask=1;
	if(m.mod==3) {
		DATA_TYPE tmp=REG(m.R_M);
		cpu.EFLAGS.CF=tmp>>((8*DATA_BYTE-reg_b(R_CL))&mask);
		tmp<<=reg_b(R_CL);
		REG(m.R_M)=tmp;
		flag_sf(tmp,DATA_BYTE);
		flag_zf(tmp,DATA_BYTE);
		flag_pf(tmp);
		print_asm("shl" str(SUFFIX) " %%cl,%%%s",REG_NAME(m.R_M));
		return 1+1;
	}
	else{
		swaddr_t addr;
		int len=read_ModR_M(eip+1,&addr);
		DATA_TYPE tmp=MEM_R(addr);
		cpu.EFLAGS.CF=tmp>>((8*DATA_BYTE-reg_b(R_CL))&mask);
		tmp<<=reg_b(R_CL);
		MEM_W(addr,tmp);
		flag_sf(tmp,DATA_BYTE);
		flag_zf(tmp,DATA_BYTE);
		flag_pf(tmp);
		print_asm("shl" str(SUFFIX) " %%cl,%s",ModR_M_asm);
		return 1+len;
	}
}
make_helper(concat(shl_i_,SUFFIX)) {
	ModR_M m;
	m.val= instr_fetch(eip+1,1);
	DATA_TYPE mask=1;
	int8_t imm;
	if(m.mod==3) {
		DATA_TYPE tmp=REG(m.R_M);
		imm=instr_fetch(eip+1+1,1);
		cpu.EFLAGS.CF=tmp>>((8*DATA_BYTE-imm)&mask);
		tmp<<=imm;
		REG(m.R_M)=tmp;
		flag_sf(tmp,DATA_BYTE);
		flag_zf(tmp,DATA_BYTE);
		flag_pf(tmp);
		print_asm("shl" str(SUFFIX) " $0x%x,%%%s",imm,REG_NAME(m.R_M));
		return 1+1+1;
	}
	else{
		swaddr_t addr;
		int len=read_ModR_M(eip+1,&addr);
		DATA_TYPE tmp=MEM_R(addr);
		imm=instr_fetch(eip+1+len,1);
		cpu.EFLAGS.CF=tmp>>((8*DATA_BYTE-imm)&mask);
		tmp<<=imm;
		MEM_W(addr,tmp);
		flag_sf(tmp,DATA_BYTE);
		flag_zf(tmp,DATA_BYTE);
		flag_pf(tmp);
		print_asm("shl" str(SUFFIX) " $0x%x,%s",imm,ModR_M_asm);
		return 1+len+1;
	}
}
make_helper(concat(shr_1_,SUFFIX)) {
	ModR_M m;
	m.val= instr_fetch(eip+1,1);
	DATA_TYPE mask=1;
	if(m.mod==3) {
		DATA_TYPE tmp=REG(m.R_M);
		cpu.EFLAGS.CF=tmp&mask;
		cpu.EFLAGS.OF=tmp>>(8*DATA_BYTE-1);
		tmp>>=1;
		REG(m.R_M)=tmp;
		flag_sf(tmp,DATA_BYTE);
		flag_zf(tmp,DATA_BYTE);
		flag_pf(tmp);
		print_asm("shr" str(SUFFIX) " $0x1,%%%s",REG_NAME(m.R_M));
		return 1+1;
	}
	else{
		swaddr_t addr;
		int len=read_ModR_M(eip+1,&addr);
		DATA_TYPE tmp=MEM_R(addr);
		cpu.EFLAGS.CF=tmp&mask;
		cpu.EFLAGS.OF=tmp>>(8*DATA_BYTE-1);
		tmp>>=1;
		MEM_W(addr,tmp);
		flag_sf(tmp,DATA_BYTE);
		flag_zf(tmp,DATA_BYTE);
		flag_pf(tmp);
		print_asm("shr" str(SUFFIX) " $0x1,%s",ModR_M_asm);
		return 1+len;
	}
}
make_helper(concat(shr_c_,SUFFIX)) {
	ModR_M m;
	m.val= instr_fetch(eip+1,1);
	DATA_TYPE mask=1;
	if(m.mod==3) {
		DATA_TYPE tmp=REG(m.R_M);
		cpu.EFLAGS.CF=(tmp>>(reg_b(R_CL)-1))&mask;
		tmp>>=reg_b(R_CL);
		REG(m.R_M)=tmp;
		flag_sf(tmp,DATA_BYTE);
		flag_zf(tmp,DATA_BYTE);
		flag_pf(tmp);
		print_asm("shr" str(SUFFIX) " %%cl,%%%s",REG_NAME(m.R_M));
		return 1+1;
	}
	else{
		swaddr_t addr;
		int len=read_ModR_M(eip+1,&addr);
		DATA_TYPE tmp=MEM_R(addr);
		cpu.EFLAGS.CF=(tmp>>(reg_b(R_CL)-1))&mask;
		tmp>>=reg_b(R_CL);
		MEM_W(addr,tmp);
		flag_sf(tmp,DATA_BYTE);
		flag_zf(tmp,DATA_BYTE);
		flag_pf(tmp);
		print_asm("shr" str(SUFFIX) " %%cl,%s",ModR_M_asm);
		return 1+len;
	}
}
make_helper(concat(shr_i_,SUFFIX)) {
	ModR_M m;
	m.val= instr_fetch(eip+1,1);
	DATA_TYPE mask=1;
	int8_t imm;
	if(m.mod==3) {
		DATA_TYPE tmp=REG(m.R_M);
		imm=instr_fetch(eip+1+1,1);
		cpu.EFLAGS.CF=(tmp>>(imm-1))&mask;
		tmp>>=imm;
		REG(m.R_M)=tmp;
		flag_sf(tmp,DATA_BYTE);
		flag_zf(tmp,DATA_BYTE);
		flag_pf(tmp);
		print_asm("shr" str(SUFFIX) " $0x%x,%%%s",imm,REG_NAME(m.R_M));
		return 1+1+1;
	}
	else{
		swaddr_t addr;
		int len=read_ModR_M(eip+1,&addr);
		DATA_TYPE tmp=MEM_R(addr);
		imm=instr_fetch(eip+1+len,1);
		cpu.EFLAGS.CF=(tmp>>(imm-1))&mask;
		tmp>>=imm;
		MEM_W(addr,tmp);
		flag_sf(tmp,DATA_BYTE);
		flag_zf(tmp,DATA_BYTE);
		flag_pf(tmp);
		print_asm("shr" str(SUFFIX) " $0x%x,%s",imm,ModR_M_asm);
		return 1+len+1;
	}
}
make_helper(concat(sar_1_,SUFFIX)) {
	ModR_M m;
	m.val= instr_fetch(eip+1,1);
	DATA_TYPE mask=1;
	if(m.mod==3) {
		DATA_TYPE_S tmp=REG(m.R_M);
		cpu.EFLAGS.CF=tmp&mask;
		cpu.EFLAGS.OF=0;
		tmp>>=1;
		REG(m.R_M)=tmp;
		flag_sf(tmp,DATA_BYTE);
		flag_zf(tmp,DATA_BYTE);
		flag_pf(tmp);
		print_asm("sar" str(SUFFIX) " $0x1,%%%s",REG_NAME(m.R_M));
		return 1+1;
	}
	else{
		swaddr_t addr;
		int len=read_ModR_M(eip+1,&addr);
		DATA_TYPE_S tmp=MEM_R(addr);
		cpu.EFLAGS.CF=tmp&mask;
		cpu.EFLAGS.OF=0;
		tmp>>=1;
		MEM_W(addr,tmp);
		flag_sf(tmp,DATA_BYTE);
		flag_zf(tmp,DATA_BYTE);
		flag_pf(tmp);
		print_asm("sar" str(SUFFIX) " $0x1,%s",ModR_M_asm);
		return 1+len;
	}
}
make_helper(concat(sar_c_,SUFFIX)) {
	ModR_M m;
	m.val= instr_fetch(eip+1,1);
	DATA_TYPE mask=1;
	if(m.mod==3) {
		DATA_TYPE_S tmp=REG(m.R_M);
		cpu.EFLAGS.CF=(tmp>>(reg_b(R_CL)-1))&mask;
		tmp>>=reg_b(R_CL);
		REG(m.R_M)=tmp;
		flag_sf(tmp,DATA_BYTE);
		flag_zf(tmp,DATA_BYTE);
		flag_pf(tmp);
		print_asm("sar" str(SUFFIX) " %%cl,%%%s",REG_NAME(m.R_M));
		return 1+1;
	}
	else{
		swaddr_t addr;
		int len=read_ModR_M(eip+1,&addr);
		DATA_TYPE_S tmp=MEM_R(addr);
		cpu.EFLAGS.CF=(tmp>>(reg_b(R_CL)-1))&mask;
		tmp>>=reg_b(R_CL);
		MEM_W(addr,tmp);
		flag_sf(tmp,DATA_BYTE);
		flag_zf(tmp,DATA_BYTE);
		flag_pf(tmp);
		print_asm("sar" str(SUFFIX) " %%cl,%s",ModR_M_asm);
		return 1+len;
	}
}
make_helper(concat(sar_i_,SUFFIX)) {
	ModR_M m;
	m.val= instr_fetch(eip+1,1);
	DATA_TYPE mask=1;
	int8_t imm;
	if(m.mod==3) {
		DATA_TYPE_S tmp=REG(m.R_M);
		imm=instr_fetch(eip+1+1,1);
		cpu.EFLAGS.CF=(tmp>>(imm-1))&mask;
		tmp>>=imm;
		REG(m.R_M)=tmp;
		flag_sf(tmp,DATA_BYTE);
		flag_zf(tmp,DATA_BYTE);
		flag_pf(tmp);
		print_asm("sar" str(SUFFIX) " $0x%x,%%%s",imm,REG_NAME(m.R_M));
		return 1+1+1;
	}
	else{
		swaddr_t addr;
		int len=read_ModR_M(eip+1,&addr);
		DATA_TYPE_S tmp=MEM_R(addr);
		imm=instr_fetch(eip+1+len,1);
		cpu.EFLAGS.CF=(tmp>>(imm-1))&mask;
		tmp>>=imm;
		MEM_W(addr,tmp);
		flag_sf(tmp,DATA_BYTE);
		flag_zf(tmp,DATA_BYTE);
		flag_pf(tmp);
		print_asm("sar" str(SUFFIX) " $0x%x,%s",imm,ModR_M_asm);
		return 1+len+1;
	}
}




#include "exec/template-end.h"
