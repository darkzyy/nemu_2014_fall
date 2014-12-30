#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"
int exec(swaddr_t);

make_helper(concat(rep_,SUFFIX)) {
	int32_t opc=instr_fetch(eip+1,1);
	int instr_len=1;
	switch(opc){
		case 0xA4:
			for(;reg_l(1)>0;reg_l(1)--)
				instr_len=exec(eip+1);
			print_asm("rep movs (%%%s),(%%%s)",REG_NAME(R_ESI),REG_NAME(R_EDI));
			return instr_len+1;
			break;
		case 0xA5:
			for(;reg_l(1)>0;reg_l(1)--)
				instr_len=exec(eip+1);
			print_asm("rep movs (%%%s),(%%%s)",REG_NAME(R_ESI),REG_NAME(R_EDI));
			return instr_len+1;
			break;
		case 0xAA:
			for(;reg_l(1)>0;reg_l(1)--)
				instr_len=exec(eip+1);
			print_asm("rep stos %%%s,(%%%s)",REG_NAME(0),REG_NAME(R_EDI));
			return instr_len+1;
			break;
		case 0xAB:
			for(;reg_l(1)>0;reg_l(1)--)
				instr_len=exec(eip+1);
			print_asm("rep movs %%%s,(%%%s)",REG_NAME(0),REG_NAME(R_EDI));
			return instr_len+1;
			break;
		default :
			printf("bad rep\n");
			assert(0);
	}
}

#include "exec/template-end.h"
