#include "common.h"

#include <unistd.h>

void load_table();
void main_loop();
void set_main_args(int, char * []);
void init_bp_pool();
void init_regex();
void init_signal();
void reg_test();

int enable_debug = false;
int quiet = false;

long long hit1=0,miss1=0,sub1=0;
long long hit2=0,miss2=0,sub2=0;
long long hit3=0,miss3=0,sub3=0;

static void process_args(int argc, char *argv[]) {
	int opt;
	while( (opt = getopt(argc, argv, "dq")) != -1) {
		switch(opt) {
			case 'd':
				enable_debug = true;
				break;
			case 'q':
				quiet = true;
				break;
			default:
				test(0, "bad option = %s\n", optarg);
				break;
		}
	}

	test(argc > optind, "Program is not given\n");

	set_main_args(argc - optind, argv + optind);
}

int main(int argc, char *argv[]) {
	process_args(argc, argv);

	/* Perform some global initialization */
	init_regex();
	init_signal();
	load_table();
	init_bp_pool();


	/* Test whether the 'CPU_state' structure is organized correctly. */
	reg_test();

	main_loop();
	printf("L1:hit:%lld,miss:%lld,sub:%lld\n",hit1,miss1,sub1);
	printf("L2:hit:%lld,miss:%lld,sub:%lld\n",hit2,miss2,sub2);
	printf("TLB:hit:%lld,miss:%lld,sub:%lld\n",hit3,miss3,sub3);

	return 0;
}
