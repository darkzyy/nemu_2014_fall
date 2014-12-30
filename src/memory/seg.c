#include "common.h"
#include "memory.h"
#include "cpu/reg.h"
#include "debug.h"

lnaddr_t segment_translate(swaddr_t addr, size_t len, int32_t current_sreg){
	if(cpu.CR0.PE){
		uint16_t mask_RPL=0x3;
		uint32_t mask_DPL=0x60;
		uint32_t mask_BASE0=0x0000ffff;
		uint32_t mask_BASE1=0x00ff0000;
		uint32_t mask_BASE2=0xff000000;
		//uint32_t mask_LIM0 =0x0000ffff;
		//uint32_t mask_LIM1 =0x00070000;
		uint16_t selector_tmp = cpu.s_reg[current_sreg].selector;
		if((selector_tmp>>3)>cpu.GDTR.lim)
		  assert(0);
		uint32_t gdt_tmp[4];
		int i;
		for(i=0;i<4;i++)
		  gdt_tmp[i] = lnaddr_read( cpu.GDTR.base+((selector_tmp >>3)<<3)+2*i , 2);
		uint32_t base_tmp = (gdt_tmp[1]&mask_BASE0)|
			((gdt_tmp[2]<<16)&mask_BASE1)|
			((gdt_tmp[3]<<16)&mask_BASE2);
		//Log("base:0x%x	current_sreg:%s",base_tmp,s_reg_str[current_sreg]);
		//uint32_t lim_tmp = (gdt_tmp[0]&mask_LIM0)|
		//	((gdt_tmp[3]<<16)&mask_LIM1);
		assert((gdt_tmp[2]&mask_DPL) >= (selector_tmp&mask_RPL));
		assert((gdt_tmp[2]&mask_DPL) >= cpu.s_reg[current_sreg].CPL);
		//printf("0x%x	0x%x	0x%x	cur_seg:%d\n",addr,len,lim_tmp,current_sreg);
		test(cpu.s_reg[current_sreg].lim >= addr+len,"out of limit: \naddr:0x%x\nlen: %x\nlimit:0x%x\ncurrent_sreg:%s",addr,len, cpu.s_reg[current_sreg].lim,s_reg_str[current_sreg]);
		return addr+base_tmp;
	}
	else{
		return addr;
	}
}
