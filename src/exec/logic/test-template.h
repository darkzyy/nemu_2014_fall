#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"
#include "exec/flags.h"

make_helper(concat(test_r2rm_,SUFFIX)) {
	ModR_M m;
	m.val =instr_fetch(eip+1,1);
	if(m.mod ==3 ) {
		DATA_TYPE tmp=REG(m.R_M);
		tmp &= REG(m.reg);
		flag_sf(tmp,DATA_BYTE);
		flag_zf(tmp,DATA_BYTE);
		flag_pf(tmp);
		cpu.EFLAGS.CF=0;
		cpu.EFLAGS.OF=0;
		print_asm("test" str(SUFFIX) " %%%s,%%%s", REG_NAME(m.reg), REG_NAME(m.R_M));
		return 2;
	}
	else{
		swaddr_t addr;
		int len=read_ModR_M(eip+1, &addr);
		DATA_TYPE_S tmp1,tmp2;
		tmp1=MEM_R(addr);
		tmp2=REG(m.reg);
		tmp1&=tmp2;
		flag_sf(tmp1,DATA_BYTE);
		flag_zf(tmp1,DATA_BYTE);
		flag_pf(tmp1);
		cpu.EFLAGS.CF=0;
		cpu.EFLAGS.OF=0;
		print_asm("test" str(SUFFIX) " %%%s,%s", REG_NAME(m.reg),ModR_M_asm);
		return 1+len;
	}
}
make_helper(concat(test_i2rm_,SUFFIX)) {
	ModR_M m;
	DATA_TYPE imm;
	m.val = instr_fetch(eip+1,1);
	if(m.mod==3) {
		DATA_TYPE tmp;
		imm= instr_fetch(eip + 1 + 1,DATA_BYTE);
		tmp=REG(m.R_M)&imm;
		flag_sf(tmp,DATA_BYTE);
		flag_zf(tmp,DATA_BYTE);
		flag_pf(tmp);
		cpu.EFLAGS.CF=0;
		cpu.EFLAGS.OF=0;
		print_asm("test" str(SUFFIX) " $0x%x,%%%s", imm, REG_NAME(m.R_M));
		return 1+1+DATA_BYTE;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1,&addr);
		DATA_TYPE tmp,tmp2;
		imm = instr_fetch(eip + 1 + len ,DATA_BYTE);
		tmp=MEM_R(addr);	
		tmp2=tmp&imm;
		flag_sf(tmp2,DATA_BYTE);
		flag_zf(tmp2,DATA_BYTE);
		flag_pf(tmp2);
		cpu.EFLAGS.CF=0;
		cpu.EFLAGS.OF=0;
		print_asm("test" str(SUFFIX) " $0x%x,%s", imm, ModR_M_asm);
		return len + 1 +DATA_BYTE;
	}
}
make_helper(concat(test_i2r_,SUFFIX)) {
	DATA_TYPE imm;
	imm= instr_fetch(eip+1,DATA_BYTE);
	DATA_TYPE tmp=REG(0)&imm;
	flag_sf(tmp,DATA_BYTE);
	flag_zf(tmp,DATA_BYTE);
	flag_pf(tmp);
	cpu.EFLAGS.CF=0;
	cpu.EFLAGS.OF=0;
	print_asm("test" str(SUFFIX) " $0x%x,%%%s", imm, REG_NAME(0));
	return 1+DATA_BYTE;
}
#include "exec/template-end.h"
