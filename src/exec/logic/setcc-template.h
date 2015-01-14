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
make_helper(concat(setae_,SUFFIX)) {
	ModR_M m;
	m.val = instr_fetch(eip+1,1);
	if(m.mod == 3){
		if(cpu.EFLAGS.CF==0) 
			reg_b(m.R_M) = 0x1;
		else
			reg_b(m.R_M) = 0x0;
		print_asm("setae" " %%%s",regsb[m.R_M]);
		return 1+1;
	}
	else{
		swaddr_t addr;
		int len = read_ModR_M(eip+1,&addr);
		if(cpu.EFLAGS.CF==0) 
		  MEM_W(addr,0x1);
		else
		  MEM_W(addr,0x0);
		print_asm("setae" " %s",ModR_M_asm);
		return 1+len;
	}
}
make_helper(concat(setb_,SUFFIX)) {
	ModR_M m;
	m.val = instr_fetch(eip+1,1);
	if(m.mod == 3){
		if(cpu.EFLAGS.CF==1) 
			reg_b(m.R_M) = 0x1;
		else
			reg_b(m.R_M) = 0x0;
		print_asm("setb" " %%%s",regsb[m.R_M]);
		return 1+1;
	}
	else{
		swaddr_t addr;
		int len = read_ModR_M(eip+1,&addr);
		if(cpu.EFLAGS.CF==1) 
		  MEM_W(addr,0x1);
		else
		  MEM_W(addr,0x0);
		print_asm("setb" " %s",ModR_M_asm);
		return 1+len;
	}
}
make_helper(concat(sete_,SUFFIX)) {
	ModR_M m;
	m.val = instr_fetch(eip+1,1);
	if(m.mod == 3){
		if(cpu.EFLAGS.ZF==1) 
			reg_b(m.R_M) = 0x1;
		else
			reg_b(m.R_M) = 0x0;
		print_asm("sete" " %%%s",regsb[m.R_M]);
		return 1+1;
	}
	else{
		swaddr_t addr;
		int len = read_ModR_M(eip+1,&addr);
		if(cpu.EFLAGS.ZF==1) 
		  MEM_W(addr,0x1);
		else
		  MEM_W(addr,0x0);
		print_asm("sete" " %s",ModR_M_asm);
		return 1+len;
	}
}
make_helper(concat(setg_,SUFFIX)) {
	ModR_M m;
	m.val = instr_fetch(eip+1,1);
	if(m.mod == 3){
		if(cpu.EFLAGS.ZF==0&&cpu.EFLAGS.OF==cpu.EFLAGS.SF) 
			reg_b(m.R_M) = 0x1;
		else
			reg_b(m.R_M) = 0x0;
		print_asm("setg" " %%%s",regsb[m.R_M]);
		return 1+1;
	}
	else{
		swaddr_t addr;
		int len = read_ModR_M(eip+1,&addr);
		if(cpu.EFLAGS.ZF==0&&cpu.EFLAGS.OF==cpu.EFLAGS.SF)
		  MEM_W(addr,0x1);
		else
		  MEM_W(addr,0x0);
		print_asm("setg" " %s",ModR_M_asm);
		return 1+len;
	}
}
make_helper(concat(setge_,SUFFIX)) {
	ModR_M m;
	m.val = instr_fetch(eip+1,1);
	if(m.mod == 3){
		if(cpu.EFLAGS.OF==cpu.EFLAGS.SF) 
			reg_b(m.R_M) = 0x1;
		else
			reg_b(m.R_M) = 0x0;
		print_asm("setge" " %%%s",regsb[m.R_M]);
		return 1+1;
	}
	else{
		swaddr_t addr;
		int len = read_ModR_M(eip+1,&addr);
		if(cpu.EFLAGS.OF==cpu.EFLAGS.SF)
		  MEM_W(addr,0x1);
		else
		  MEM_W(addr,0x0);
		print_asm("setge" " %s",ModR_M_asm);
		return 1+len;
	}
}
make_helper(concat(setl_,SUFFIX)) {
	ModR_M m;
	m.val = instr_fetch(eip+1,1);
	if(m.mod == 3){
		if(cpu.EFLAGS.OF!=cpu.EFLAGS.SF) 
			reg_b(m.R_M) = 0x1;
		else
			reg_b(m.R_M) = 0x0;
		print_asm("setl" " %%%s",regsb[m.R_M]);
		return 1+1;
	}
	else{
		swaddr_t addr;
		int len = read_ModR_M(eip+1,&addr);
		if(cpu.EFLAGS.OF!=cpu.EFLAGS.SF) 
		  MEM_W(addr,0x1);
		else
		  MEM_W(addr,0x0);
		print_asm("setl" " %s",ModR_M_asm);
		return 1+len;
	}
}
make_helper(concat(setle_,SUFFIX)) {
	ModR_M m;
	m.val = instr_fetch(eip+1,1);
	if(m.mod == 3){
		if(cpu.EFLAGS.OF!=cpu.EFLAGS.SF||cpu.EFLAGS.ZF==1) 
			reg_b(m.R_M) = 0x1;
		else
			reg_b(m.R_M) = 0x0;
		print_asm("setle" " %%%s",regsb[m.R_M]);
		return 1+1;
	}
	else{
		swaddr_t addr;
		int len = read_ModR_M(eip+1,&addr);
		if(cpu.EFLAGS.OF!=cpu.EFLAGS.SF||cpu.EFLAGS.ZF==1) 
		  MEM_W(addr,0x1);
		else
		  MEM_W(addr,0x0);
		print_asm("setle" " %s",ModR_M_asm);
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
make_helper(concat(setno_,SUFFIX)) {
	ModR_M m;
	m.val = instr_fetch(eip+1,1);
	if(m.mod == 3){
		if(cpu.EFLAGS.OF == 0)
			reg_b(m.R_M) = 0x1;
		else
			reg_b(m.R_M) = 0x0;
		print_asm("setno" " %%%s",regsb[m.R_M]);
		return 1+1;
	}
	else{
		swaddr_t addr;
		int len = read_ModR_M(eip+1,&addr);
		if(cpu.EFLAGS.OF == 0)
		  MEM_W(addr,0x1);
		else
		  MEM_W(addr,0x0);
		print_asm("setno" " %s",ModR_M_asm);
		return 1+len;
	}
}
make_helper(concat(setnp_,SUFFIX)) {
	ModR_M m;
	m.val = instr_fetch(eip+1,1);
	if(m.mod == 3){
		if(cpu.EFLAGS.PF == 0)
			reg_b(m.R_M) = 0x1;
		else
			reg_b(m.R_M) = 0x0;
		print_asm("setnp" " %%%s",regsb[m.R_M]);
		return 1+1;
	}
	else{
		swaddr_t addr;
		int len = read_ModR_M(eip+1,&addr);
		if(cpu.EFLAGS.PF == 0)
		  MEM_W(addr,0x1);
		else
		  MEM_W(addr,0x0);
		print_asm("setnp" " %s",ModR_M_asm);
		return 1+len;
	}
}
make_helper(concat(setns_,SUFFIX)) {
	ModR_M m;
	m.val = instr_fetch(eip+1,1);
	if(m.mod == 3){
		if(cpu.EFLAGS.SF == 0)
			reg_b(m.R_M) = 0x1;
		else
			reg_b(m.R_M) = 0x0;
		print_asm("setns" " %%%s",regsb[m.R_M]);
		return 1+1;
	}
	else{
		swaddr_t addr;
		int len = read_ModR_M(eip+1,&addr);
		if(cpu.EFLAGS.SF == 0)
		  MEM_W(addr,0x1);
		else
		  MEM_W(addr,0x0);
		print_asm("setns" " %s",ModR_M_asm);
		return 1+len;
	}
}
make_helper(concat(seto_,SUFFIX)) {
	ModR_M m;
	m.val = instr_fetch(eip+1,1);
	if(m.mod == 3){
		if(cpu.EFLAGS.OF == 1)
			reg_b(m.R_M) = 0x1;
		else
			reg_b(m.R_M) = 0x0;
		print_asm("seto" " %%%s",regsb[m.R_M]);
		return 1+1;
	}
	else{
		swaddr_t addr;
		int len = read_ModR_M(eip+1,&addr);
		if(cpu.EFLAGS.ZF == 1)
		  MEM_W(addr,0x1);
		else
		  MEM_W(addr,0x0);
		print_asm("seto" " %s",ModR_M_asm);
		return 1+len;
	}
}
make_helper(concat(setp_,SUFFIX)) {
	ModR_M m;
	m.val = instr_fetch(eip+1,1);
	if(m.mod == 3){
		if(cpu.EFLAGS.PF == 1)
			reg_b(m.R_M) = 0x1;
		else
			reg_b(m.R_M) = 0x0;
		print_asm("setp" " %%%s",regsb[m.R_M]);
		return 1+1;
	}
	else{
		swaddr_t addr;
		int len = read_ModR_M(eip+1,&addr);
		if(cpu.EFLAGS.PF == 0)
		  MEM_W(addr,0x1);
		else
		  MEM_W(addr,0x0);
		print_asm("setp" " %s",ModR_M_asm);
		return 1+len;
	}
}
make_helper(concat(sets_,SUFFIX)) {
	ModR_M m;
	m.val = instr_fetch(eip+1,1);
	if(m.mod == 3){
		if(cpu.EFLAGS.SF == 1)
			reg_b(m.R_M) = 0x1;
		else
			reg_b(m.R_M) = 0x0;
		print_asm("sets" " %%%s",regsb[m.R_M]);
		return 1+1;
	}
	else{
		swaddr_t addr;
		int len = read_ModR_M(eip+1,&addr);
		if(cpu.EFLAGS.SF == 1)
		  MEM_W(addr,0x1);
		else
		  MEM_W(addr,0x0);
		print_asm("sets" " %s",ModR_M_asm);
		return 1+len;
	}
}
#include "exec/template-end.h"
