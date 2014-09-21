#include "ui/ui.h"

#include "nemu.h"

#include <signal.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

int nemu_state = END;

void cpu_exec(uint32_t);
void restart();

/* We use the readline library to provide more flexibility to read from stdin. */
char* rl_gets() {
	static char *line_read = NULL;

	if (line_read) {
		free(line_read);
		line_read = NULL;
	}

	line_read = readline("(nemu) ");

	if (line_read && *line_read) {
		add_history(line_read);
	}

	return line_read;
}

/* This function will be called when you press <C-c>. And it will return to 
 * where you press <C-c>. If you are interesting in how it works, please
 * search for "Unix signal" in the Internet.
 */
static void control_C(int signum) {
	if(nemu_state == RUNNING) {
		nemu_state = INT;
	}
}

void init_signal() {
	/* Register a signal handler. */
	struct sigaction s;
	memset(&s, 0, sizeof(s));
	s.sa_handler = control_C;
	int ret = sigaction(SIGINT, &s, NULL);
	assert(ret == 0);
}

static void cmd_c() {
	if(nemu_state == END) {
		puts("The Program does not start. Use 'r' command to start the program.");
		return;
	}

	nemu_state = RUNNING;
	cpu_exec(-1);
	if(nemu_state != END) { nemu_state = STOP; }
}

static void cmd_r() {
	if(nemu_state != END) { 
		char c;
		while(1) {
			printf("The program is already running. Restart the program? (y or n)");
			scanf("%c", &c);
			switch(c) {
				case 'y': goto restart_;
				case 'n': return;
				default: puts("Please answer y or n.");
			}
		}
	}

restart_:
	restart();
	nemu_state = STOP;
	cmd_c();
}

static void cmd_si(unsigned int a){
	if(nemu_state == END){
		restart();
		nemu_state =STOP;
		nemu_state = RUNNING;
		}
	cpu_exec(a);
}

static void cmd_info_reg(){
	if(nemu_state == END) {
        puts("The Program does not start. Use 'r' command to start the program.");
        return;
	}
	printf("eax            0x%x            %d\n",cpu.eax,cpu.eax);
	printf("ecx            0x%x            %d\n",cpu.ecx,cpu.ecx);
	printf("edx            0x%x            %d\n",cpu.edx,cpu.edx);
	printf("ebx            0x%x            %d\n",cpu.ebx,cpu.ebx);
	printf("esp            0x%x            %d\n",cpu.esp,cpu.esp);
	printf("ebp            0x%x            %d\n",cpu.ebp,cpu.ebp);
	printf("esi            0x%x            %d\n",cpu.esi,cpu.esi);
	printf("edi            0x%x            %d\n",cpu.edi,cpu.edi);
	printf("eip            0x%x            %d\n",cpu.eip,cpu.eip);

}


void main_loop() {
	char *cmd;
	while(1) {
		cmd = rl_gets();
		char *p = strtok(cmd, " ");

		if(p == NULL) { continue; }

		if(strcmp(p, "c") == 0) { cmd_c(); }
		else if(strcmp(p, "r") == 0) { cmd_r(); }
		else if(strcmp(p, "q") == 0) { return; }
		else if(strcmp(p,"si") == 0) {
			p =strtok(NULL," ");
			if(p!=NULL){
		   		unsigned int a=0;
				sscanf(p,"%u",&a);
				cmd_si(a);
			}
			else cmd_si(1);
	   	}
		else if(strcmp(p,"infor") == 0) { cmd_info_reg(); }

		/* TODO: Add more commands */

		else { printf("Unknown command '%s'\n", p); }
	}
}
