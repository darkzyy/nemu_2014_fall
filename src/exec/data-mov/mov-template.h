#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"

make_helper(concat(mov_i2r_, SUFFIX)) {
	int reg_code = instr_fetch(eip, 1) & 0x7;
	DATA_TYPE imm = instr_fetch(eip + 1, DATA_BYTE);
	REG(reg_code) = imm;

	print_asm("mov" str(SUFFIX) " $0x%x,%%%s", imm, REG_NAME(reg_code));
	return DATA_BYTE + 1;
}

make_helper(concat(mov_i2rm_, SUFFIX)) {
	ModR_M m;
	DATA_TYPE imm;
	m.val = instr_fetch(eip + 1, 1);
	if(m.mod == 3) {
		imm = instr_fetch(eip + 1 + 1, DATA_BYTE);
		REG(m.R_M) = imm;
		print_asm("mov" str(SUFFIX) " $0x%x,%%%s", imm, REG_NAME(m.R_M));
		return 1 + DATA_BYTE + 1;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1, &addr);
		imm = instr_fetch(eip + 1 + len, DATA_BYTE);
		MEM_W(addr, imm);
		print_asm("mov" str(SUFFIX) " $0x%x,%s", imm, ModR_M_asm);
		return len + DATA_BYTE + 1;
	}
}

make_helper(concat(mov_r2rm_, SUFFIX)) {
	ModR_M m;
	m.val = instr_fetch(eip + 1, 1);
	if(m.mod == 3) {
		REG(m.R_M) = REG(m.reg);
		print_asm("mov" str(SUFFIX) " %%%s,%%%s", REG_NAME(m.reg), REG_NAME(m.R_M));
		return 2;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1, &addr);
		MEM_W(addr, REG(m.reg));

		print_asm("mov" str(SUFFIX) " %%%s,%s", REG_NAME(m.reg), ModR_M_asm);
		return len + 1;
	}
}

make_helper(concat(mov_rm2r_, SUFFIX)) {
	ModR_M m;
	m.val = instr_fetch(eip + 1, 1);
	if(m.mod == 3) {
		REG(m.reg) = REG(m.R_M);
		print_asm("mov" str(SUFFIX) " %%%s,%%%s", REG_NAME(m.R_M), REG_NAME(m.reg));
		return 2;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1, &addr);
		REG(m.reg) = MEM_R(addr);

		print_asm("mov" str(SUFFIX) " %s,%%%s", ModR_M_asm, REG_NAME(m.reg));
		return len + 1;
	}
}

make_helper(concat(mov_a2moffs_, SUFFIX)) {
	swaddr_t addr = instr_fetch(eip + 1, 4);
	MEM_W(addr, REG(R_EAX));

	print_asm("mov" str(SUFFIX) " %%%s,0x%x", REG_NAME(R_EAX), addr);
	return 5;
}

make_helper(concat(mov_moffs2a_, SUFFIX)) {
	swaddr_t addr = instr_fetch(eip + 1, 4);
	REG(R_EAX) = MEM_R(addr);

	print_asm("mov" str(SUFFIX) " 0x%x,%%%s", addr, REG_NAME(R_EAX));
	return 5;
}

make_helper(concat(mov_c2r_,SUFFIX)) {
	ModR_M m;
	m.val = instr_fetch(eip+1,1);
	reg_l(m.R_M)=c_reg(m.reg);
	print_asm("mov %%%s,%%%s" , c_reg_str[m.reg], REG_NAME(m.R_M));
	return 2;
}

extern void init_tlb();
make_helper(concat(mov_r2c_,SUFFIX)) {
	ModR_M m;
	m.val = instr_fetch(eip+1,1);
	if(m.reg==3)
	  init_tlb();
	c_reg(m.reg)=reg_l(m.R_M);
	print_asm("mov %%%s,%%%s" , REG_NAME(m.R_M), c_reg_str[m.reg]);
	return 2;
}

extern int sreg_dirty[4];
make_helper(concat(mov_rm2sr_, SUFFIX)) {
	ModR_M m;
	m.val = instr_fetch(eip + 1, 1);
	if(m.mod == 3) {
		s_reg(m.reg) = reg_w(m.R_M);
		cpu.s_reg[m.reg].base = 0;
		cpu.s_reg[m.reg].lim = 0xffffffff;
		sreg_dirty[m.reg] = 1;
		print_asm("mov" str(SUFFIX) " %%%s,%%%s", REG_NAME(m.R_M), s_reg_str[m.reg]);
		return 2;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1, &addr);
		s_reg(m.reg) = MEM_R(addr);
		cpu.s_reg[m.reg].base = 0;
		cpu.s_reg[m.reg].lim = 0xffffffff;
		sreg_dirty[m.reg] = 1;
		print_asm("mov" str(SUFFIX) " %s,%%%s", ModR_M_asm, s_reg_str[m.reg]);
		return len + 1;
	}
}

make_helper(concat(mov_sr2rm_, SUFFIX)) {
	ModR_M m;
	m.val = instr_fetch(eip + 1, 1);
	if(m.mod == 3) {
		REG(m.R_M) = s_reg(m.reg);
		print_asm("mov" str(SUFFIX) " %%%s,%%%s", s_reg_str[m.reg], REG_NAME(m.R_M));
		return 2;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1, &addr);
		MEM_W(addr, REG(m.reg));

		print_asm("mov" str(SUFFIX) " %%%s,%s", s_reg_str[m.reg], ModR_M_asm);
		return len + 1;
	}
}

#include "exec/template-end.h"
