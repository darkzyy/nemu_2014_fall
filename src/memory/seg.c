#include "common.h"
#include "memory.h"
#include "cpu/reg.h"
#include "debug.h"

extern uint32_t hwaddr_read(hwaddr_t addr, size_t len);
int sreg_dirty[4]={1,1,1,1};
lnaddr_t segment_translate(swaddr_t addr, size_t len, int32_t current_sreg){
	if(cpu.CR0.PE){
		if(sreg_dirty[current_sreg] == 0){
			test(cpu.s_reg[current_sreg].lim >= addr+len,"out of limit: \naddr:0x%x\nlen: %x\nlimit:0x%x\ncurrent_sreg:%s",addr,len, cpu.s_reg[current_sreg].lim,s_reg_str[current_sreg]);
		}
		else{
			uint32_t mask_BASE0=0x0000ffff;
			uint32_t mask_BASE1=0x00ff0000;
			uint32_t mask_BASE2=0xff000000;
			uint16_t selector_tmp = cpu.s_reg[current_sreg].selector;
			assert((selector_tmp>>3)<=cpu.GDTR.lim);
			uint32_t gdt_tmp[4];
			int i;
			for(i=0;i<4;i++)
			  gdt_tmp[i] = hwaddr_read( cpu.GDTR.base+((selector_tmp >>3)<<3)+2*i , 2);
			uint32_t base_tmp = (gdt_tmp[1]&mask_BASE0)|
				((gdt_tmp[2]<<16)&mask_BASE1)|
				((gdt_tmp[3]<<16)&mask_BASE2);
			//uint32_t lim_tmp = (gdt_tmp[0]|(gdt_tmp[3]<<16));
			cpu.s_reg[current_sreg].base = base_tmp;
			//cpu.s_reg[current_sreg].lim = lim_tmp;
			test(cpu.s_reg[current_sreg].lim >= addr+len,"out of limit: \naddr:0x%x\nlen: %x\nlimit:0x%x\ncurrent_sreg:%s",addr,len, cpu.s_reg[current_sreg].lim,s_reg_str[current_sreg]);
			sreg_dirty[current_sreg] = 0;
		}
		return addr+cpu.s_reg[current_sreg].base;
	}
	else{
		return addr;
	}
}
