#include "ui/ui.h"
#include "ui/breakpoint.h"
#include "nemu.h"

#include <setjmp.h>

#define LOADER_START 0x100000

int exec(swaddr_t);
int exec2(swaddr_t);
void load_prog();
void init_dram();
extern void init_cache1();
extern void init_cache2();
extern void init_tlb();

char assembly[40];
jmp_buf jbuf;	/* Make it easy to perform exception handling */

extern uint8_t loader [];
extern uint32_t loader_len;

extern int quiet;

void restart() {
	/* Perform some initialization to restart a program */
	load_prog();
	memcpy(hwa_to_va(LOADER_START), loader, loader_len);

	cpu.eip = LOADER_START;
	cpu.ebp = 0;
	cpu.esp = 0x800000;
	cpu.EFLAGS.val = 0x2;
	cpu.CS.base = 0;
	cpu.CS.lim = 0xffffffff;
	cpu.CR0.PG = 0;
	cpu.CR0.PE = 0;

	init_cache1();
	init_cache2();
	init_tlb();
	init_dram();
	reload();//重新载入断点
}

static void print_bin_instr(swaddr_t eip, int len) {
	int i;
	printf("%8x:   ", eip);
	for(i = 0; i < len; i ++) {
		printf("%02x ", swaddr_read(eip + i, 1));
	}
	printf("%*.s", 50 - (12 + 3 * len), "");
}

void cpu_exec(volatile uint32_t n) {
	//volatile uint32_t n_temp = n;

	setjmp(jbuf);
	for(; n > 0; n --) {
		swaddr_t eip_temp = cpu.eip;
		int instr_len = exec(cpu.eip);
		cpu.eip += instr_len;
		//if(n_temp != -1 || (enable_debug && !quiet)) {
		//if((enable_debug && !quiet && n_temp<11)) {
		if((enable_debug && !quiet)) {
			print_bin_instr(eip_temp, instr_len);
			puts(assembly);
		}

		if(nemu_state == INT) {
			printf("\n\nUser interrupt\n");
			return;
		} 
		else if(nemu_state == END) { return; }
		else if(nemu_state == BPS1){
			cpu.eip--;
			nemu_state=BPS2;
			return;
		}
		else if(nemu_state == BPS2){
			swaddr_write(eip_temp,1,0xcc);	
			nemu_state=RUNNING;
		}
		else if(wp_change()) {return;}
		if(hit_newb())
		  return;
	}
}
