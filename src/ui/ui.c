#include "ui/ui.h"
#include "ui/breakpoint.h"

#include "nemu.h"

#include <signal.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

extern uint32_t expr(char *e,bool *success);
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
	if(nemu_state!=BPS2)
		nemu_state = RUNNING;
	cpu_exec(-1);
	if(nemu_state != END&&nemu_state !=BPS2) { nemu_state = STOP; }
}

static void cmd_r() {
	if(nemu_state != END) { 
		char c;
		while(1) {
			printf("The program is already running. Restart the program? (y or n)");
			fflush(stdout);
			scanf(" %c", &c);
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
		nemu_state = RUNNING;
	}
	cpu_exec(a);
	if(nemu_state != END&&nemu_state !=BPS2) { nemu_state = STOP; }
}
static void cmd_b(char *p){
		p=strtok(NULL,"");
		if(p==NULL){printf("Unknown command 'b NULL'\n"); }
		else if(p[0]!='*'){printf("Unknown command\n"); }
		else{
			bool suc=1;
			swaddr_t a=expr(p+1,&suc);
			//sscanf(p,"%x",&a);
			if(suc){
				add_bp(a,swaddr_read(a,1));
				swaddr_write(a,1,0xcc);
			}
		}
		
}
static void cmd_d(char *p){
	p=strtok(NULL," ");
	if(p==NULL){printf("Unknown command 'd NULL'\n");}
	else if(strcmp(p,"all")==0){
		init_bp_pool();
	}
	else{
		int a;
		sscanf(p,"%d",&a);
		swaddr_write(find_bp(a),1,find_pre_inc(find_bp(a)));
		free_bp(a-1);
	}
}

static void cmd_p(char *p){
	p=strtok(NULL,"");
	bool suc=0;
	printf("%d\n",expr(p,&suc));
}
static void cmd_w(char *p){
	p=strtok(NULL,"");
	bool suc=1;
	expr(p,&suc);
	//printf("suc=%d\n",suc);
	if(suc==1){
		//printf("adding\n");
		//fflush(stdout);
		add_wp(p);
	}

}

static void cmd_info_b(){
	printb();
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
	printf("EFLAGS		   0x%x		    	%d\n",cpu.EFLAGS.val,cpu.EFLAGS.val);

}

extern void cmd_bt();

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
		else if(strcmp(p,"info") == 0) {
			p = strtok(NULL," ");
			if(p ==NULL){ 
				printf("Unknown command 'info %s'\n",p);
			}
			else {
				if(strcmp(p,"r")==0){
					cmd_info_reg();
				}
				else if(strcmp(p,"b")==0){
					cmd_info_b();
				}
				else printf("Unknown command 'info %s'\n",p);
			}
	   	}
		else if(strcmp(p,"x")==0){
			p = strtok(NULL," ");
		    unsigned int a=0;
  			if(p ==NULL){ printf("Unknown command 'x %s'\n",p); }
		    else{
				sscanf(p,"%u",&a);
				p= strtok(NULL,"");
				if(p ==NULL){ printf("Unknown command\n"); }
				else{
					bool suc=1;
			  		 uint32_t b=expr(p,&suc);
					 if(suc){
					 	//sscanf(p,"%x",&b);
						 int i=0;
						 while(i<a)
						 {
							printf("%02x ", swaddr_read(b + i, 1));
						    i++;
						 	if(i%5 == 0)
								 printf("\n");
			   			 }
					 }
				}
			}
		}
		else if(strcmp(p,"b")==0)	{cmd_b(p);}
		else if(strcmp(p,"d")==0)   {cmd_d(p);}
		else if(strcmp(p,"p")==0)	{cmd_p(p);}
		else if(strcmp(p,"w")==0)	{cmd_w(p);}
		else if(strcmp(p,"bt")==0)	{cmd_bt();}



			 


			
		/* TODO: Add more commands */

		else { printf("Unknown command '%s'\n", p); }
	}
}
