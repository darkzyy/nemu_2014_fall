#include "exec/helper.h"

#define DATA_BYTE 1
#include "shift-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "shift-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "shift-template.h"
#undef DATA_BYTE

extern char suffix;

make_helper(shl_1_v) {
	return (suffix == 'l' ? shl_1_l(eip) : shl_1_w(eip));
}
make_helper(shl_c_v) {
	return (suffix == 'l' ? shl_c_l(eip) : shl_c_w(eip));
}
make_helper(shl_i_v) {
	return (suffix == 'l' ? shl_i_l(eip) : shl_i_w(eip));
}
make_helper(shr_1_v) {
	return (suffix == 'l' ? shr_1_l(eip) : shr_1_w(eip));
}
make_helper(shr_c_v) {
	return (suffix == 'l' ? shr_c_l(eip) : shr_c_w(eip));
}
make_helper(shr_i_v) {
	return (suffix == 'l' ? shr_i_l(eip) : shr_i_w(eip));
}
make_helper(sar_1_v) {
	return (suffix == 'l' ? sar_1_l(eip) : sar_1_w(eip));
}
make_helper(sar_c_v) {
	return (suffix == 'l' ? sar_c_l(eip) : sar_c_w(eip));
}
make_helper(sar_i_v) {
	return (suffix == 'l' ? sar_i_l(eip) : sar_i_w(eip));
}
