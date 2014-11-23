#include <elf.h>
#include "trap.h"

void loader() {
	Elf32_Ehdr *elf = (void *)0;
	Elf32_Phdr *ph = (void *)elf->e_phoff;
	int i = 0;
	int count = 0;
	for(; i < elf->e_phnum; i ++) {
		if (ph[i].p_type == PT_LOAD) {
			int j;
			void* dst;
			const void* src;
			dst = (void*)ph[i].p_vaddr;
			src = (void*)elf + ph[i].p_offset;
			for (j = 0; j < ph[i].p_filesz; j++) {
				*(char*)dst = *(char*)src;
				dst = (char*)dst + 1;
				src = (char*)src + 1;
			}
			for (j=0; j < ph[i].p_memsz - ph[i].p_filesz; j++) {
				*(char*)dst = 0;
				dst = (char*)dst + 1;
			}
			count++;
		}
	}

	((void(*)(void)) elf->e_entry)();

	HIT_GOOD_TRAP;
}


