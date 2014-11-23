/*#include <elf.h>
#include <string.h>

int match_sym(char*sym) {
	Elf32_Ehdr *elf = (void *)0;
	Elf32_Shdr *sh = (void *)elf->e_shoff;
   	int i=0;
	while(i<elf->e_shnum){
		if(sh[i].sh_type==SHT_STRTAB){
			Elf32_Sym *st = (void *)sh[i].sh_offset;
		
		if(strcmp(sym,(const char *)st->st_name)==0)
			return st->st_value;
		}
		i++;
	}
	return 0;
}

*/
