#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "./uthash.h"

#define block_width 6
#define block_len (1<<block_width)

typedef struct {
    uint8_t block[block_len];
} struct_key_t;

typedef struct {
    struct_key_t key;
    unsigned long long count;
    UT_hash_handle hh;
} record_t;

record_t *rec_head = NULL;

void add_bl(void *mem){
    record_t *r, *ret;
    r = (record_t *)malloc(sizeof(record_t));
    memset((void *)r, 0, sizeof(record_t));
    memcpy((void *)r, mem, sizeof(struct_key_t));
    HASH_FIND(hh, rec_head, &r->key, sizeof(struct_key_t), ret);
    if(!ret){
        HASH_ADD(hh, rec_head, key, sizeof(struct_key_t), r);
        r->count = 1;
    }
    else{
        ret->count += 1;
        free(r);
    }
}

void print_mem(){
    record_t* rc;
    for(rc = rec_head; rc != NULL; rc = rc->hh.next){
        int i;
        uint32_t *arr = (uint32_t *) &(rc->key);
        if(rc->count > 50){
            for(i = 0; i < block_len/4; i+=4){
                printf("0x%x ",arr[i]);
            }
            printf("\n");
        }
    }
}

#undef block_width 
#undef block_len
