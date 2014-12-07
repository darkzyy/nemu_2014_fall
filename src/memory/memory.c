#include "common.h"

uint32_t dram_read(hwaddr_t addr, size_t len);
void dram_write(hwaddr_t addr, size_t len, uint32_t data);
uint32_t cache1_read(hwaddr_t addr, size_t len);
void cache1_write(hwaddr_t addr, size_t len, uint32_t data);
uint32_t cache2_read(hwaddr_t addr, size_t len);
void cache2_write(hwaddr_t addr, size_t len, uint32_t data);

/* Memory accessing interfaces */

uint32_t hwaddr_read(hwaddr_t addr, size_t len) {
	assert(len == 1 || len == 2 || len == 4);
	return cache1_read(addr, len);
}

void hwaddr_write(hwaddr_t addr, size_t len, uint32_t data) {
	assert(len == 1 || len == 2 || len == 4);
	cache1_write(addr, len, data);
}

uint32_t swaddr_read(swaddr_t addr, size_t len) {
	assert(len == 1 || len == 2 || len == 4);
	return hwaddr_read(addr, len);
}

void swaddr_write(swaddr_t addr, size_t len, uint32_t data) {
	assert(len == 1 || len == 2 || len == 4);
	hwaddr_write(addr, len, data);
}

/*static uint32_t hwaddr_read_instr(hwaddr_t addr, size_t len) {
	assert(len == 1 || len == 2 || len == 4);
	return dram_read(addr, len);
}*/

uint32_t instr_fetch(swaddr_t addr, size_t len) {
	assert(len == 1 || len == 2 || len == 4);
	//printf("instr addr:%x\n",addr);
	//fflush(stdout);
	//printf("instr:%x\n",swaddr_read(addr,len));
	return swaddr_read(addr, len);
}
