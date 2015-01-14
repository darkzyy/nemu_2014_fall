#include "common.h"

extern int current_sreg;
extern lnaddr_t segment_translate(swaddr_t addr,size_t len,int32_t current_sreg);
extern hwaddr_t page_translate(lnaddr_t addr);

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

uint32_t lnaddr_read(lnaddr_t addr, size_t len) {
	assert(len == 1 || len == 2 || len == 4);
		hwaddr_t hwaddr = page_translate(addr);
		return hwaddr_read(hwaddr, len);
}

void lnaddr_write(lnaddr_t addr, size_t len, uint32_t data) {
	assert(len == 1 || len == 2 || len == 4);
		hwaddr_t hwaddr = page_translate(addr);
		hwaddr_write(hwaddr, len, data);
}

uint32_t swaddr_read(swaddr_t addr, size_t len) {
	assert(len == 1 || len == 2 || len == 4);
	lnaddr_t lnaddr = segment_translate(addr, len, current_sreg);
	return lnaddr_read(lnaddr, len);
}

void swaddr_write(swaddr_t addr, size_t len, uint32_t data) {
	assert(len == 1 || len == 2 || len == 4);
	lnaddr_t lnaddr = segment_translate(addr, len, current_sreg);
	lnaddr_write(lnaddr, len, data);
}

/*static uint32_t hwaddr_read_instr(hwaddr_t addr, size_t len) {
  assert(len == 1 || len == 2 || len == 4);
  return dram_read(addr, len);
  }*/

uint32_t instr_fetch(swaddr_t addr, size_t len) {
	assert(len == 1 || len == 2 || len == 4);
	current_sreg=1;
	return swaddr_read(addr, len);
}
