#include "common.h"
#include "memory.h"
#include "cpu/reg.h"
#include"lib/misc.h"
#include<time.h>
#include<stdlib.h>

extern uint32_t hwaddr_read(hwaddr_t addr,size_t len);
extern hwaddr_t tlb(lnaddr_t addr);

//uint32_t mask_dir	=	0xffc00000;
uint32_t mask_table	=	0x003ff000;
uint32_t mask_offset=	0x00000fff;
uint32_t mask_present		=	0x1;
#define dir(addr) ((addr>>22)*4)
#define tab(addr) (((addr&mask_table)>>12)*4)
#define off(addr) (addr&mask_offset)

hwaddr_t page_translate(lnaddr_t addr){
	if(cpu.CR0.PG) {
		return tlb(addr);
	}
	else{
		return addr;
	}
}


#define tag_width 20
#define offset_width 12
#define NR_TLB 64

/*typedef union{
	uint32_t addr;
	struct {
		uint32_t offset :offset_width;
		uint32_t tag    :tag_width;
	};
}laddr;
*/
typedef struct{
	union{
		struct{
			uint32_t tag    :tag_width;
			uint32_t v      :1;
		};
		uint32_t flag;
	};
	uint32_t pframe_base;
}block;

block TLB[NR_TLB];

void init_tlb(){
	int i;
	for(i=0;i<NR_TLB;i++)
	  TLB[i].v = 0;
}

hwaddr_t tlb(lnaddr_t addr){
	int i;
	uint32_t offset = addr&mask_offset;
	for(i=0;i<NR_TLB;i++){
		if( TLB[i].v==1 && (TLB[i].tag==(addr&~mask_offset)>>offset_width)){
		  return (TLB[i].pframe_base+offset);
		}
	}
	//执行到这里说明TLB miss
	uint32_t pdir_base_addr		=	cpu.CR3&(~mask_offset);
	uint32_t ptable_base_addr	=	hwaddr_read(pdir_base_addr+dir(addr),4);
	test(ptable_base_addr&mask_present,"addr:0x%x	pdir_base:0x%x  ptab_base: 0x%x	eip: 0x%x",addr,pdir_base_addr,ptable_base_addr,cpu.eip);
	ptable_base_addr &= ~mask_offset;
	uint32_t pframe_base_addr	=	hwaddr_read(ptable_base_addr+tab(addr),4);
	test(pframe_base_addr & mask_present,"pframe_base: %x",pframe_base_addr);
	pframe_base_addr &= ~mask_offset;
	for(i=0;i<NR_TLB;i++){
		if( !TLB[i].v ){
			TLB[i].tag = (addr&~mask_offset)>>offset_width;
			TLB[i].pframe_base =pframe_base_addr; 
			TLB[i].v = 1;
			return pframe_base_addr+offset;
		}
	}
	//执行到这里说明需要替换
	srand((unsigned) time(NULL));
	i=rand()%NR_TLB;
	TLB[i].tag = (addr&~mask_offset)>>offset_width;
	TLB[i].pframe_base =pframe_base_addr; 
	TLB[i].v = 1;
	return pframe_base_addr+offset;
}

