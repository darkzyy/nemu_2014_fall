#include "common.h"
#include "memory.h"
#include "cpu/reg.h"

extern uint32_t hwaddr_read(hwaddr_t addr,size_t len);

//uint32_t mask_dir	=	0xffc00000;
uint32_t mask_table	=	0x003ff000;
uint32_t mask_offset=	0x00000fff;
#define dir(addr) ((addr>>22)*4)
#define tab(addr) (((addr&mask_table)>>12)*4)
#define off(addr) (addr&mask_offset)

hwaddr_t page_translate(lnaddr_t addr){
	if(cpu.CR0.PG) {
		//Log("eip:%x",cpu.eip);
		uint32_t mask_present		=	0x1;
		uint32_t pdir_base_addr		=	cpu.CR3&(~mask_offset);
		uint32_t ptable_base_addr	=	hwaddr_read(pdir_base_addr+dir(addr),4);
		 test(ptable_base_addr&mask_present,"pdir_base:0x%x  ptab_base: 0x%x addr: 0x%x  eip: 0x%x",              pdir_base_addr,ptable_base_addr,addr,cpu.eip);
		ptable_base_addr &= ~mask_offset;
		//	Log("pdir_base:0x%x	ptable_base:0x%x	eip:%x",pdir_base_addr,ptable_base_addr,cpu.eip);
		uint32_t pframe_base_addr	=	hwaddr_read(ptable_base_addr+tab(addr),4);
			test(pframe_base_addr & mask_present,"pframe_base: %x",pframe_base_addr);
		pframe_base_addr &= ~mask_offset;
		//	Log("pframe_base_addr: %x",pframe_base_addr);
		return pframe_base_addr + off(addr);
	}
	else{
		return addr;
	}
}
