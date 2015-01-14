#include "common.h"
#include "memory.h"
#include <string.h>

#include <elf.h>

#ifdef HAS_DEVICE
#define ELF_OFFSET_IN_DISK 0
#endif

#define STACK_SIZE (1 << 20)

void ide_read(uint8_t *, uint32_t, uint32_t);
void create_video_mapping();
uint32_t get_ucr3();
extern uint32_t mm_malloc(uint32_t va,int len);

uint32_t loader() {
	Elf32_Ehdr *elf;
	Elf32_Phdr *ph = NULL;

#ifdef HAS_DEVICE
	uint8_t buf[4096];
	ide_read(buf, ELF_OFFSET_IN_DISK, 4096);
	elf = (void*)buf;
#else
	/* The ELF file is located at memory address 0 */
	elf = (void *)0x0;
#endif
	ph=(void*)elf->e_phoff;

	/* Load each program segment */
	//nemu_assert(0);

	int i=0,num=elf->e_phnum;
	for(; i<num;i++) {
		/* Scan the program header table, load each segment into memory */
		if(ph[i].p_type == PT_LOAD) {
			const char * src=(void*)elf+ph[i].p_offset;
			char * temp=(void*)mm_malloc(ph[i].p_vaddr,ph[i].p_memsz);
			int j;
			/* TODO: read the content of the segment from the ELF file 
			 * to the memory region [VirtAddr, VirtAddr + FileSiz)
			 */
			memcpy(temp,src,ph[i].p_filesz);
			j=ph[i].p_filesz;
			/* TODO: zero the memory region 
			 * [VirtAddr + FileSiz, VirtAddr + MemSiz)
			 */
			for(;j<ph[i].p_memsz;j++){
				temp[j]=0;
			}
			/* Record the prgram break for future use. */
			extern uint32_t brk;
			uint32_t new_brk = ph->p_vaddr + ph->p_memsz - 1;
			if(brk < new_brk) { brk = new_brk; }
		}
	}

	volatile uint32_t entry = elf->e_entry;

#ifdef IA32_PAGE
	mm_malloc(KOFFSET - STACK_SIZE, STACK_SIZE);

#ifdef HAS_DEVICE
	create_video_mapping();
#endif

	write_cr3(get_ucr3());
#endif

	return entry;
}
