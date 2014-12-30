#ifndef __CPU_REG_H__
#define __CPU_REG_H__

#include "common.h"

/* TODO: Re-organize the 'CPU_state' structure to match
 * the GPR encoding scheme in i386 instruction format.
 * For example, if we access reg_w(R_BX) we will get the 'bx' register;
 * if we access reg_b(R_CH), we will get the 'ch' register.
 * Hint: Use 'union'.
 * For more details about the GPR encoding scheme, see i386 manual.
 */

typedef struct seg_reg {
	uint16_t selector;
	uint32_t lim;
	uint32_t base;
	uint8_t CPL;
}seg_reg_tmp;

typedef union {
	struct {
	union {
		uint32_t _32;
		uint16_t _16;
		uint8_t _8[2];
	} gpr[8];
	struct seg_reg s_reg[4];
	uint32_t cr[4];
	};

	/* Do NOT change the order of the GPRs' definitions. 
	 * They match the register encoding scheme used in i386 instruction format.
	 * See i386 manual for more details.
	 */

	struct{
		int32_t eax, ecx, edx, ebx, esp, ebp, esi, edi;
		struct seg_reg ES,CS,SS,DS;
		union{
			struct {
				uint32_t PE :1;
				uint32_t useless:30;
				uint32_t PG :1;
			};
			uint32_t val;
		}CR0;
		uint32_t CR1,CR2,CR3;
		swaddr_t eip;
		union {
			struct {
				uint32_t CF 	:1;
				uint32_t dc1 	:1;
				uint32_t PF 	:1;
				uint32_t dc2 	:1;
				uint32_t AF  	:1;
				uint32_t dc3	:1;
				uint32_t ZF 	:1;
				uint32_t SF  	:1;
				uint32_t TF 	:1;
				uint32_t IF 	:1;
				uint32_t DF 	:1;
				uint32_t OF 	:1;
				uint32_t IO_PL 	:2;
				uint32_t NT 	:1;
				uint32_t dc4 	:1;
				uint32_t RF 	:1;
				uint32_t VM 	:1;
				uint32_t useless 	:14;
			};
			uint32_t val;
		} EFLAGS;
		struct {
			uint32_t base;
			uint16_t lim;
		}GDTR;
		//uint16_t CS,DS,ES,SS;//SEGMENT
	};
} CPU_state;

extern CPU_state cpu;

int current_sreg;

enum { R_EAX, R_ECX, R_EDX, R_EBX, R_ESP, R_EBP, R_ESI, R_EDI };
enum { R_AX, R_CX, R_DX, R_BX, R_SP, R_BP, R_SI, R_DI };
enum { R_AL, R_CL, R_DL, R_BL, R_AH, R_CH, R_DH, R_BH };
enum { R_CS, R_DS, R_ES, R_SS };

#define reg_l(index) (cpu.gpr[index]._32)
#define reg_w(index) (cpu.gpr[index]._16)
#define reg_b(index) (cpu.gpr[index & 0x3]._8[index >> 2])
#define s_reg(index) (cpu.s_reg[index].selector)
#define c_reg(index) (cpu.cr[index])

extern const char* regsl[];
extern const char* regsw[];
extern const char* regsb[];
extern const char* s_reg_str[];
extern const char* c_reg_str[];

#endif
