#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"

make_helper(concat(ja_,SUFFIX)) {
	DATA_TYPE_S tmp = instr_fetch(eip+1 , DATA_BYTE);
	print_asm("ja" " %x ",eip+1+DATA_BYTE+tmp);
	if(cpu.EFLAGS.CF==0&&cpu.EFLAGS.ZF==0) {
		cpu.eip+=tmp;
	}
	return 1+DATA_BYTE;
}
make_helper(concat(jae_,SUFFIX)) {
	DATA_TYPE_S tmp = instr_fetch(eip+1 , DATA_BYTE);
	print_asm("jae" " %x ",eip+1+DATA_BYTE+tmp);
	if(cpu.EFLAGS.CF==0) {
		cpu.eip+=tmp;
	}
	return 1+DATA_BYTE;
}
make_helper(concat(jb_,SUFFIX)) {
	DATA_TYPE_S tmp = instr_fetch(eip+1 , DATA_BYTE);
	print_asm("jb" " %x ",eip+1+DATA_BYTE+tmp);
	if(cpu.EFLAGS.CF==1) {
		cpu.eip+=tmp;
	}
	return 1+DATA_BYTE;
}
make_helper(concat(jbe_,SUFFIX)) {
	DATA_TYPE_S tmp = instr_fetch(eip+1 , DATA_BYTE);
	print_asm("jbe" " %x ",eip+1+DATA_BYTE+tmp);
	if(cpu.EFLAGS.ZF==1||cpu.EFLAGS.CF==1) {
		cpu.eip+=tmp;
	}
	return 1+DATA_BYTE;
}
make_helper(concat(jcxz_,SUFFIX)) {
	DATA_TYPE_S tmp = instr_fetch(eip+1 , DATA_BYTE);
	print_asm("jcxz" " %x ",eip+1+DATA_BYTE+tmp);
	if(reg_w(0)==1) {
		cpu.eip+=tmp;
	}
	return 1+DATA_BYTE;
}
make_helper(concat(jecxz_,SUFFIX)) {
	DATA_TYPE_S tmp = instr_fetch(eip+1 , DATA_BYTE);
	print_asm("jecxz" " %x ",eip+1+DATA_BYTE+tmp);
	if(cpu.eax==1) {
		cpu.eip+=tmp;
	}
	return 1+DATA_BYTE;
}
make_helper(concat(je_,SUFFIX)) {
	DATA_TYPE_S tmp = instr_fetch(eip+1 , DATA_BYTE);
	print_asm("je" " %x ",eip+1+DATA_BYTE+tmp);
	if(cpu.EFLAGS.ZF==1) {
		cpu.eip+=tmp;
	}
	return 1+DATA_BYTE;
}
make_helper(concat(jg_,SUFFIX)) {
	DATA_TYPE_S tmp = instr_fetch(eip+1 , DATA_BYTE);
	print_asm("jg" " %x ",eip+1+DATA_BYTE+tmp);
	if(cpu.EFLAGS.ZF==0&&cpu.EFLAGS.OF==cpu.EFLAGS.SF) {
		cpu.eip+=tmp;
	}
	return 1+DATA_BYTE;
}
make_helper(concat(jge_,SUFFIX)) {
	DATA_TYPE_S tmp = instr_fetch(eip+1 , DATA_BYTE);
	print_asm("jge" " %x ",eip+1+DATA_BYTE+tmp);
	if(cpu.EFLAGS.OF==cpu.EFLAGS.SF) {
		cpu.eip+=tmp;
	}
	return 1+DATA_BYTE;
}
make_helper(concat(jl_,SUFFIX)) {
	DATA_TYPE_S tmp = instr_fetch(eip+1 , DATA_BYTE);
	print_asm("jl" " %x ",eip+1+DATA_BYTE+tmp);
	if(cpu.EFLAGS.OF!=cpu.EFLAGS.SF) {
		cpu.eip+=tmp;
	}
	return 1+DATA_BYTE;
}
make_helper(concat(jle_,SUFFIX)) {
	DATA_TYPE_S tmp = instr_fetch(eip+1 , DATA_BYTE);
	print_asm("jle" " %x ",eip+1+DATA_BYTE+tmp);
	if(cpu.EFLAGS.ZF==1||cpu.EFLAGS.OF!=cpu.EFLAGS.SF) {
		cpu.eip+=tmp;
	}
	return 1+DATA_BYTE;
}
make_helper(concat(jne_,SUFFIX)) {
	DATA_TYPE_S tmp = instr_fetch(eip+1 , DATA_BYTE);
	print_asm("jne" " %x ",eip+1+DATA_BYTE+tmp);
	if(cpu.EFLAGS.ZF==0) {
		cpu.eip+=tmp;
	}
	return 1+DATA_BYTE;
}
make_helper(concat(jno_,SUFFIX)) {
	DATA_TYPE_S tmp = instr_fetch(eip+1 , DATA_BYTE);
	print_asm("jno" " %x ",eip+1+DATA_BYTE+tmp);
	if(cpu.EFLAGS.OF==0) {
		cpu.eip+=tmp;
	}
	return 1+DATA_BYTE;
}
make_helper(concat(jns_,SUFFIX)) {
	DATA_TYPE_S tmp = instr_fetch(eip+1 , DATA_BYTE);
	print_asm("jns" " %x ",eip+1+DATA_BYTE+tmp);
	if(cpu.EFLAGS.SF==0) {
		cpu.eip+=tmp;
	}
	return 1+DATA_BYTE;
}
make_helper(concat(jo_,SUFFIX)) {
	DATA_TYPE_S tmp = instr_fetch(eip+1 , DATA_BYTE);
	print_asm("jo" " %x ",eip+1+DATA_BYTE+tmp);
	if(cpu.EFLAGS.OF==1) {
		cpu.eip+=tmp;
	}
	return 1+DATA_BYTE;
}
make_helper(concat(jpo_,SUFFIX)) {
	DATA_TYPE_S tmp = instr_fetch(eip+1 , DATA_BYTE);
	print_asm("jpo" " %x ",eip+1+DATA_BYTE+tmp);
	if(cpu.EFLAGS.PF==0) {
		cpu.eip+=tmp;
	}
	return 1+DATA_BYTE;
}
make_helper(concat(jpe_,SUFFIX)) {
	DATA_TYPE_S tmp = instr_fetch(eip+1 , DATA_BYTE);
	print_asm("jpe" " %x ",eip+1+DATA_BYTE+tmp);
	if(cpu.EFLAGS.PF==1) {
		cpu.eip+=tmp;
	}
	return 1+DATA_BYTE;
}
make_helper(concat(js_,SUFFIX)) {
	DATA_TYPE_S tmp = instr_fetch(eip+1 , DATA_BYTE);
	print_asm("js" " %x ",eip+1+DATA_BYTE+tmp);
	if(cpu.EFLAGS.SF==1) {
		cpu.eip+=tmp;
	}
	return 1+DATA_BYTE;
}


#include "exec/template-end.h"
