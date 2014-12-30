#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"

make_helper(concat(seta_,SUFFIX)) {
	ModR_M m;
	m.val = instr_fetch(eip+1,1);
	if(m.mod == 3){
		if(cpu.EFLAGS.CF==0&&cpu.EFLAGS.ZF==0) 
			reg_b(m.R_M) = 0x1;
		else
			reg_b(m.R_M) = 0x0;
		print_asm("seta" " %%%s",regsb[m.R_M]);
		return 1+1;
	}
	else{
		swaddr_t addr;
		int len = read_ModR_M(eip+1,&addr);
		if(cpu.EFLAGS.CF==0&&cpu.EFLAGS.ZF==0) 
		  MEM_W(addr,0x1);
		else
		  MEM_W(addr,0x0);
		print_asm("seta" " %s",ModR_M_asm);
		return 1+len;
	}
}
make_helper(concat(setna_,SUFFIX)) {
	ModR_M m;
	m.val = instr_fetch(eip+1,1);
	if(m.mod == 3){
		if(cpu.EFLAGS.CF==1||cpu.EFLAGS.ZF==1) 
			reg_b(m.R_M) = 0x1;
		else
			reg_b(m.R_M) = 0x0;
		print_asm("setna" " %%%s",regsb[m.R_M]);
		return 1+1;
	}
	else{
		swaddr_t addr;
		int len = read_ModR_M(eip+1,&addr);
		if(cpu.EFLAGS.CF==0&&cpu.EFLAGS.ZF==0) 
		  MEM_W(addr,0x1);
		else
		  MEM_W(addr,0x0);
		print_asm("setna" " %s",ModR_M_asm);
		return 1+len;
	}
}
make_helper(concat(setne_,SUFFIX)) {
	ModR_M m;
	m.val = instr_fetch(eip+1,1);
	if(m.mod == 3){
		if(cpu.EFLAGS.ZF == 0)
			reg_b(m.R_M) = 0x1;
		else
			reg_b(m.R_M) = 0x0;
		print_asm("setne" " %%%s",regsb[m.R_M]);
		return 1+1;
	}
	else{
		swaddr_t addr;
		int len = read_ModR_M(eip+1,&addr);
		if(cpu.EFLAGS.ZF == 0)
		  MEM_W(addr,0x1);
		else
		  MEM_W(addr,0x0);
		print_asm("setne" " %s",ModR_M_asm);
		return 1+len;
	}
}
#include "exec/template-end.h"
