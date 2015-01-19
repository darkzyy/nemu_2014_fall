#include "common.h"
#include "lib/misc.h"
#include <time.h>
#include <stdlib.h>

#define block_width 6
#define group_width 7
#define tag_width (27-block_width-group_width)
#define hw_mem_size (1<<27)

#define block_len (1<<block_width)
#define nr_group (1<<group_width)
#define block_mask (block_len-1)
#define ways (1<<(16-block_width-group_width))

typedef union {
	struct {
		uint32_t block	:block_width;
		uint32_t group	:group_width;
		uint32_t tag	:tag_width;
	};
	uint32_t addr;
} cache1_addr;

typedef struct {
	union {
		struct {
			uint16_t tag:14;
			uint16_t v:1;
		};
		uint16_t tmp;
	}flag;
	uint8_t a[block_len];
} block;

block cache1[nr_group][ways];

extern uint32_t dram_read(hwaddr_t addr,size_t len);
extern void dram_write(hwaddr_t addr,size_t len,uint32_t data);

extern uint32_t cache2_read(hwaddr_t addr,size_t len);
extern void cache2_write(hwaddr_t addr,size_t len,uint32_t data);

extern long long hit1,miss1,sub1;

void init_cache1(){
	int i,j;
	for(i=0;i<nr_group;i++){
		for(j=0;j<ways;j++){
			cache1[i][j].flag.v=0;
		}
	}
}

void cache1_read_2(hwaddr_t addr,void *tmp){
	test(addr<hw_mem_size,"addr=%x\n",addr);
	cache1_addr temp;
	temp.addr=addr & ~block_mask;
	int i,j;
	for(i=0;i<ways;i++){
		if(cache1[temp.group][i].flag.v && (cache1[temp.group][i].flag.tag==(addr>>(block_width+group_width)))){
			hit1++;
			memcpy(tmp,cache1[temp.group][i].a,block_len);
			break;
		}
	}
	if(i==ways){
		for(i=0;i<ways;i++){
			if(!cache1[temp.group][i].flag.v){
				int j;
				for(j=0;j<block_len;j++){
					cache1[temp.group][i].a[j]=cache2_read(temp.addr+j,1);
				}
				cache1[temp.group][i].flag.v=1;
				cache1[temp.group][i].flag.tag=(addr>>(block_width+group_width));
				memcpy(tmp,cache1[temp.group][i].a,block_len);
				miss1++;
				break;
			}
		}
		if(i==ways){
			srand((unsigned) time(NULL));
			i=rand()%ways;
			for(j=0;j<block_len;j++){
				cache1[temp.group][i].a[j]=cache2_read(temp.addr+j,1);
			}
			cache1[temp.group][i].flag.v=1;
			cache1[temp.group][i].flag.tag=(addr>>(block_width+group_width));
			memcpy(tmp,cache1[temp.group][i].a,block_len);
			sub1++;
		}
	}
}

void cache1_write_2(hwaddr_t addr,void *tmp,uint8_t *mask){
	test(addr<hw_mem_size,"addr=%x\n",addr);
	cache1_addr temp;
	temp.addr=addr & ~block_mask;
	int i;
	for(i=0;i<ways;i++){
		if(cache1[temp.group][i].flag.v && (cache1[temp.group][i].flag.tag==(addr>>(block_width+group_width)))){
			memcpy_with_mask(cache1[temp.group][i].a,tmp,block_len,mask);
			break;
		}
	}
}

uint32_t cache1_read(hwaddr_t addr,size_t len) {
	assert(len==1||len==2||len==4);
	uint32_t offset = addr & block_mask;//块内偏移量
	uint8_t tmp[block_len*2];
	cache1_read_2(addr,tmp);
	if( (addr^(addr +len - 1)) & ~(block_mask) ){
		cache1_read_2(addr+block_len,tmp+block_len);
	}
	return *(uint32_t *)(tmp+offset) & (~0u >> ((4 - len)<<3));
}

void cache1_write(hwaddr_t addr,size_t len,uint32_t data){
	assert(len==1||len==2||len==4);
	cache2_write(addr,len,data);
	uint32_t offset = addr & block_mask;
	uint8_t tmp[2 * block_len];
	uint8_t mask[2 * block_len];
	memset(mask, 0, 2*block_len);

	*(uint32_t *)(tmp+offset) = data;
	memset(mask+offset,1,len);

	cache1_write_2(addr,tmp,mask);

	if( (addr^(addr +len-1)) & ~(block_mask) ){
		cache1_write_2(addr+block_len,tmp+block_len,mask+block_len);
	}
}
