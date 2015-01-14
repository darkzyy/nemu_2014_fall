#ifndef __UI_BREAKPOINT_H__
#define __UI_BREAKPOINT_H__

#include "common.h"

#define INT3_CODE 0xcc

typedef struct breakpoint {
	int type;
	int NO;
	struct breakpoint *next;
	swaddr_t addr;
	int pre_inc;
	int pre_val;
	char *exp;
	/* TODO: Add more members if necessary */


} BP;

void init_bp_pool();
void add_bp(swaddr_t addr,int inc);
void add_newb(swaddr_t addr);
bool hit_newb();
void add_wp(char *p);
void free_bp(int NO);
void reno();
int find_pre_inc(swaddr_t eip);
void printb();
bool wp_change();
void reload();
swaddr_t find_bp(int a);
#endif
