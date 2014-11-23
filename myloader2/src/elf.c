#include<elf.h>
#include"trap.h"

void loader() {
	Elf32_Ehdr *elf =(void *)0;
	int num=elf->e_phnum,i=0;
	Elf32_Phdr *ph=(void *)elf->e_phoff;
	while(i<num){
		if(ph[i].p_type == PT_LOAD) {	
			const char * src=(void *)elf+ph[i].p_offset;
			char * temp =(void *)ph[i].p_vaddr;
			int j;
			for(j=0;j<ph[i].p_filesz;j++){
				temp[j]=src[j];
			}
			for(;j<ph[i].p_memsz;j++){
				temp[j]=0;
			}
		}
		i++;
	}
	((void(*)(void)) elf->e_entry) ();
	HIT_GOOD_TRAP;
}

