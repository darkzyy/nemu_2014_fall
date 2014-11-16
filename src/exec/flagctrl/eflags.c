#include "cpu/modrm.h"
#include "cpu/reg.h"

uint32_t mask_lsb=0x1,mask_af=0xf;


void flag_of(int32_t op1,int32_t op2,char a,int data_byte) {
	int32_t  mask_msb=0x1;
	mask_msb<<=(8*data_byte-1);
	if(a=='-'){
		int32_t temp=op1-op2;
		if(((mask_msb&op1)!=(mask_msb&op2))&&((mask_msb&op1)!=(mask_msb&temp)))
			cpu.EFLAGS.OF=1;
		else
			cpu.EFLAGS.OF=0;
	}
	else if(a=='+'){
		int32_t temp=op1+op2;
		if(((mask_msb&op1)==(mask_msb&op2))&&((mask_msb&op1)!=(mask_msb&temp)))
			cpu.EFLAGS.OF=1;
		else
			cpu.EFLAGS.OF=0;
	}
	else {
		printf("运算符错误\n");
		assert(0);
	}
}
void flag_cf(uint32_t op1,uint32_t op2,char a,int data_byte){
	uint32_t mask_cf=1;
	if(data_byte!=4){
		mask_cf<<=8*data_byte;
		mask_cf-=1;
	}
	else mask_cf=0xffffffff;
	if(a=='-'){
		if((mask_cf&op1)<(mask_cf&op2))
			cpu.EFLAGS.CF=1;
		else 
			cpu.EFLAGS.CF=0;
	}
	else if(a=='+'){
		uint32_t temp=op1+op2;
		if((mask_cf&temp)<(mask_cf&op1))
			cpu.EFLAGS.CF=1;
		else
			cpu.EFLAGS.CF=0;
	}
	else {
		printf("运算符错误\n");
		assert(0);
	}
}
void flag_zf(int32_t temp,int data_byte){
	uint32_t mask_zf=1;
	if(data_byte!=4){
		mask_zf<<=8*data_byte;
		mask_zf-=1;
	}
	else mask_zf=0xffffffff;
	cpu.EFLAGS.ZF=!(temp&mask_zf);
}
void flag_af(int32_t op1,int32_t op2,char a) {
	if(a=='-'){
		if((mask_af&op1)<(mask_af&op2))
			cpu.EFLAGS.AF=1;
		else
			cpu.EFLAGS.AF=0;
	}
	else if(a=='+'){
		uint32_t temp=(uint32_t) op1+(uint32_t) op2;
		if((mask_af&temp)<(mask_af&op1))
			cpu.EFLAGS.AF=1;
		else
			cpu.EFLAGS.AF=0;
	}
	else {
		printf("运算符错误\n");
		assert(0);
	}
}

void flag_pf(int32_t temp) {
	int32_t tmp2=1,i;
	//printf("temp=%d\n",temp);
	for(i = 0;i < 8;i++){
		tmp2 ^= (temp & mask_lsb) ;
		temp>>=1;
	} 
	cpu.EFLAGS.PF=tmp2;
	//printf("PF:%d		tmp2:%d\n",cpu.EFLAGS.PF,tmp2);
}

void flag_sf(int32_t temp,int data_byte) {
	cpu.EFLAGS.SF=(temp>>((8*data_byte)-1))&mask_lsb;
}
