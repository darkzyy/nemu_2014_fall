#include "exec/helper.h"
#include "nemu.h"
#include "cpu/modrm.h"
#include "./../all-instr.h"

make_helper(dopc80) {
	ModR_M m;
	m.val=instr_fetch(eip+1,1);
	switch (m.opcode) {
		case 0: return add_i2rm_b(eip);break;
		case 1: return or_i2rm_b(eip);break;
		case 2: return adc_i2rm_b(eip);break;
		case 3: return sbb_i2rm_b(eip);break;
		case 4: return and_i2rm_b(eip);break;
		case 5: return sub_i2rm_b(eip);break;
		case 6: return xor_i2rm_b(eip);break;
		case 7: return cmp_i2rm_b(eip);break;
		default :{
					 printf("dopcode error\n");
					 assert(0);
				 }
	}
	return 0;
}

make_helper(dopc81) {
	ModR_M m;
	m.val=instr_fetch(eip+1,1);
	switch (m.opcode){
		case 0: return add_i2rm_v(eip);break;
		case 1: return or_i2rm_v(eip);break;
		case 2: return adc_i2rm_v(eip);break;
		case 3: return sbb_i2rm_v(eip);break;
		case 4: return and_i2rm_v(eip);break;
		case 5: return sub_i2rm_v(eip);break;
		case 6: return xor_i2rm_v(eip);break;
		case 7: return cmp_i2rm_v(eip);break;
		default :{
					 printf("dopcode error\n");
					 assert(0);
				 }
	}
}

make_helper(dopc83) {
	ModR_M m;
	m.val=instr_fetch(eip+1,1);
	switch (m.opcode){
		case 0: return add_i82rm_v(eip);break;
		case 1: return or_i82rm_v(eip);break;
		case 2: return adc_i82rm_v(eip);break;
		case 3: return sbb_i82rm_v(eip);break;
		case 4: return and_i82rm_v(eip);break;
		case 5: return sub_i82rm_v(eip);break;
		case 6: return xor_i82rm_v(eip);break;
		case 7: return cmp_i82rm_v(eip);break;
		default :{
					 printf("dopcode error\n");
					 assert(0);
				 }
	}
}
make_helper(dopcc0) {
	ModR_M m;
	m.val=instr_fetch(eip+1,1);
	switch (m.opcode){
		//case 0: assert(0);break;
		//case 1: assert(0);break;
		//case 2: assert(0);break;
		//case 3: assert(0);break;
		case 4: return shl_i_b(eip);break;
		case 5: return shr_i_b(eip);break;
		//case 6: assert(0);break;
		case 7: return sar_i_b(eip);break;
		default :{
					 printf("dopcode error\n");
					 assert(0);
				 }
	}
}
make_helper(dopcc1) {
	ModR_M m;
	m.val=instr_fetch(eip+1,1);
	switch (m.opcode){
		//case 0: assert(0);break;
		//case 1: assert(0);break;
		//case 2: assert(0);break;
		//case 3: assert(0);break;
		case 4: return shl_i_v(eip);break;
		case 5: return shr_i_v(eip);break;
		//case 6: assert(0);break;
		case 7: return sar_i_v(eip);break;
		default :{
					 printf("dopcode error\n");
					 assert(0);
				 }
	}
}
make_helper(dopcd0) {
	ModR_M m;
	m.val=instr_fetch(eip+1,1);
	switch (m.opcode){
		//case 0: assert(0);break;
		//case 1: assert(0);break;
		//case 2: assert(0);break;
		//case 3: assert(0);break;
		case 4: return shl_1_b(eip);break;
		case 5: return shr_1_b(eip);break;
		//case 6: assert(0);break;
		case 7: return sar_1_b(eip);break;
		default :{
					 printf("dopcode error\n");
					 assert(0);
				 }
	}
}
make_helper(dopcd1) {
	ModR_M m;
	m.val=instr_fetch(eip+1,1);
	switch (m.opcode){
		//case 0: assert(0);break;
		//case 1: assert(0);break;
		//case 2: assert(0);break;
		//case 3: assert(0);break;
		case 4: return shl_1_v(eip);break;
		case 5: return shr_1_v(eip);break;
		//case 6: assert(0);break;
		case 7: return sar_1_v(eip);break;
		default :{
					 printf("dopcode error\n");
					 assert(0);
				 }
	}
}
make_helper(dopcd2) {
	ModR_M m;
	m.val=instr_fetch(eip+1,1);
	switch (m.opcode){
		//case 0: assert(0);break;
		//case 1: assert(0);break;
		//case 2: assert(0);break;
		//case 3: assert(0);break;
		case 4: return shl_c_b(eip);break;
		case 5: return shr_c_b(eip);break;
		//case 6: assert(0);break;
		case 7: return sar_c_b(eip);break;
		default :{
					 printf("dopcode error\n");
					 assert(0);
				 }
	}
}
make_helper(dopcd3) {
	ModR_M m;
	m.val=instr_fetch(eip+1,1);
	switch (m.opcode){
		//case 0: assert(0);break;
		//case 1: assert(0);break;
		//case 2: assert(0);break;
		//case 3: assert(0);break;
		case 4: return shl_c_v(eip);break;
		case 5: return shr_c_v(eip);break;
		//case 6: assert(0);break;
		case 7: return sar_c_v(eip);break;
		default :{
					 printf("dopcode error\n");
					 assert(0);
				 }
	}
}
make_helper(dopcff) {
	ModR_M m;
	m.val=instr_fetch(eip+1,1);
	switch (m.opcode){
		case 4:assert(0);break;
		case 5:assert(0);break;
		case 6:return push_m_v(eip);break;
		default :{
					 printf("dopcode error\n");
					 assert(0);
				 }
	}
}
make_helper(dopcf6) {
	ModR_M m;
	m.val=instr_fetch(eip+1,1);
	switch (m.opcode){
		case 2:return not_b(eip);break;
		case 3:return neg_b(eip);break;
		case 4:return mul_rm2r_b(eip);break;
		case 5:return imul_rm2r_b(eip);break;
		case 6:return div_rm2r_b(eip);break;
		case 7:return idiv_rm2r_v(eip);break;
		default :{
					 printf("dopcode error\n");
					 assert(0);
				 }
	}
}
make_helper(dopcf7) {
	ModR_M m;
	m.val=instr_fetch(eip+1,1);
	switch (m.opcode){
		case 2:return neg_v(eip);break;
		case 3:return neg_v(eip);break;
		case 4:return mul_rm2r_v(eip);break;
		case 5:return imul_rm2r_b(eip);break;
		case 6:return div_rm2r_v(eip);break;
		case 7:return idiv_rm2r_v(eip);break;
		default :{
					 printf("dopcode error\n");
					 assert(0);
				 }
	}
}
