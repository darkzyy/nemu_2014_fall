#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"
#include "exec/flags.h"
#define carry cpu.EFLAGS.CF
make_helper(concat(adc_i2rm_,SUFFIX)) {
	ModR_M m;
	DATA_TYPE imm;
	m.val = instr_fetch(eip+1,1);
	if(m.mod==3) {
		DATA_TYPE tmp;
		imm= instr_fetch(eip + 1 + 1,DATA_BYTE)+carry;
		flag_of(REG(m.R_M),imm,'+',DATA_BYTE);
		flag_cf(REG(m.R_M),imm,'+',DATA_BYTE);
		REG(m.R_M)+=imm;
		tmp=REG(m.R_M);
		flag_sf(tmp,DATA_BYTE);
		flag_zf(tmp,DATA_BYTE);
		flag_pf(tmp);
		print_asm("adc" str(SUFFIX) " $0x%x,%%%s", imm, REG_NAME(m.R_M));
		return 1+1+DATA_BYTE;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1,&addr);
		DATA_TYPE tmp,tmp2;
		imm = instr_fetch(eip + 1 + len ,DATA_BYTE)+carry;
		tmp=MEM_R(addr);	
		flag_of(tmp,imm,'+',DATA_BYTE);
		flag_cf(tmp,imm,'+',DATA_BYTE);
		tmp2=tmp+imm;
		MEM_W(addr,tmp2);
		flag_sf(tmp2,DATA_BYTE);
		flag_zf(tmp2,DATA_BYTE);
		flag_pf(tmp2);
		print_asm("adc" str(SUFFIX) " $0x%x,%s", imm, ModR_M_asm);
		return len + 1 +DATA_BYTE;
	}
}
make_helper(concat(adc_i2r_,SUFFIX)) {
	DATA_TYPE imm;
	imm= instr_fetch(eip+1,DATA_BYTE)+carry;
	flag_of(REG(0),imm,'+',DATA_BYTE);
	flag_cf(REG(0),imm,'+',DATA_BYTE);
	DATA_TYPE tmp=REG(0)+imm;
	REG(0)=tmp;
	flag_sf(tmp,DATA_BYTE);
	flag_zf(tmp,DATA_BYTE);
	flag_pf(tmp);
	print_asm("adc" str(SUFFIX) " $0x%x,%%%s", imm, REG_NAME(0));
	return 1+DATA_BYTE;
}
make_helper(concat(adc_r2rm_,SUFFIX)) {
	ModR_M m;
	m.val =instr_fetch(eip+1,1);
	if(m.mod ==3 ) {
		DATA_TYPE tmp=REG(m.R_M) + REG(m.reg)+carry;
		flag_of(REG(m.R_M),REG(m.reg)+carry,'+',DATA_BYTE);
		flag_cf(REG(m.R_M),REG(m.reg)+carry,'+',DATA_BYTE);
		REG(m.R_M)=tmp;
		flag_sf(REG(m.R_M),DATA_BYTE);
		flag_zf(REG(m.R_M),DATA_BYTE);
		flag_pf(REG(m.R_M));
		print_asm("adc" str(SUFFIX) " %%%s,%%%s", REG_NAME(m.reg), REG_NAME(m.R_M));
		return 2;
	}
	else{
		swaddr_t addr;
		int len=read_ModR_M(eip+1, &addr);
		DATA_TYPE_S tmp1,tmp2;
		tmp1=MEM_R(addr);
		tmp2=REG(m.reg)+carry;
		flag_of(tmp1,tmp2,'+',DATA_BYTE);
		flag_cf(tmp1,tmp2,'+',DATA_BYTE);
		MEM_W(addr,tmp1+tmp2);
		tmp1=MEM_R(addr);
		flag_sf(tmp1,DATA_BYTE);
		flag_zf(tmp1,DATA_BYTE);
		flag_pf(tmp1);
		print_asm("adc" str(SUFFIX) " %%%s,%s", REG_NAME(m.reg),ModR_M_asm);
		return 1+len;
	}

}
make_helper(concat(adc_rm2r_,SUFFIX) ) {
	ModR_M m;
	m.val = instr_fetch(eip+1,1);
	if(m.mod ==3 ) {
		DATA_TYPE tmp;
		tmp=REG(m.reg)+REG(m.R_M)+carry;
		flag_of(REG(m.reg),REG(m.R_M)+carry,'+',DATA_BYTE);
		flag_cf(REG(m.reg),REG(m.R_M)+carry,'+',DATA_BYTE);
		REG(m.reg)=tmp;
		flag_sf(tmp,DATA_BYTE);
		flag_zf(tmp,DATA_BYTE);
		flag_pf(tmp);
		print_asm("adc" str(SUFFIX) " %%%s,%%%s", REG_NAME(m.R_M), REG_NAME(m.reg));
		return 2;
	}
	else{
		swaddr_t addr;
		int len=read_ModR_M(eip+1, &addr);
		DATA_TYPE tmp1,tmp2;
		tmp1=MEM_R(addr)+carry;
		tmp2=REG(m.reg);
		flag_of(tmp2,tmp1,'+',DATA_BYTE);
		flag_cf(tmp2,tmp1,'+',DATA_BYTE);
		tmp2=tmp2+tmp1;
		REG(m.reg)=tmp2;
		flag_sf(tmp2,DATA_BYTE);
		flag_zf(tmp2,DATA_BYTE);
		flag_pf(tmp2);
		print_asm("adc" str(SUFFIX) " %s,%%%s",ModR_M_asm, REG_NAME(m.reg));
		return 1+len;
	}

}
make_helper(concat(adc_i82rm_,SUFFIX)) {
	ModR_M m;
	m.val=instr_fetch(eip+1,1);
	int8_t imm1;
	DATA_TYPE_S imm2;
	if(m.mod == 3) {
		DATA_TYPE tmp;
		imm1 = instr_fetch(eip + 1 + 1,1);
		imm2 =imm1+carry;
		flag_of(REG(m.R_M),imm2,'+',DATA_BYTE);
		flag_cf(REG(m.R_M),imm2,'+',DATA_BYTE);
		tmp = REG(m.R_M)+imm2;
		REG(m.R_M)=tmp;
		flag_sf(tmp,DATA_BYTE);
		flag_zf(tmp,DATA_BYTE);
		flag_pf(tmp);
		print_asm("adc" str(SUFFIX) " $0x%x,%%%s", imm1, REG_NAME(m.R_M));
		return 1+1+1;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1,&addr);
		DATA_TYPE tmp,tmp2;
		imm1 = instr_fetch(eip + 1 + len ,1);
		imm2 =imm1+carry;
		tmp=MEM_R(addr);	
		flag_of(tmp,imm2,'+',DATA_BYTE);
		flag_cf(tmp,imm2,'+',DATA_BYTE);
		tmp2=tmp+imm2;
		MEM_W(addr,tmp2);
		flag_sf(tmp2,DATA_BYTE);
		flag_zf(tmp2,DATA_BYTE);
		flag_pf(tmp2);
		print_asm("adc" str(SUFFIX) " $0x%x,%s", imm1, ModR_M_asm);
		return 1+len+1;
	}
}

#include "exec/template-end.h"
