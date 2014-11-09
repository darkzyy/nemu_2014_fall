#ifndef __EXEC_FLAGS_H__
#define __EXEC_FLAGS_H__


void flag_of(int32_t op1,int32_t op2,char a,int data_type);
void flag_cf(uint32_t op1,uint32_t op2,char a,int data_type);
void flag_zf(int32_t temp,int data_byte);
void flag_af(int32_t op1,int32_t op2,char a);
void flag_pf(int32_t temp);
void flag_sf(int32_t temp,int data_byte);

#endif
