#ifndef __UI_BREAKPOINT_H__
#define __UI_BREAKPOINT_H__

#include "common.h"

#define INT3_CODE 0xcc

typedef struct breakpoint {
	int NO;
	struct breakpoint *next;
	swaddr_t addr;
	int pre_inc;
	/* TODO: Add more members if necessary */


} BP;

void add_bp(swaddr_t addr,int inc);
void free_bp(int NO);
void reno();
int find_pre_inc(swaddr_t eip);
void printb();
swaddr_t find_bp(int a);
#endif
