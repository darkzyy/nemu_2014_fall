#include "exec/helper.h"

#define DATA_BYTE 1
#include "call-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "call-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "call-template.h"
#undef DATA_BYTE

extern char suffix;

make_helper(call_rel_v) {
		return (suffix == 'l' ? call_rel_l(eip) : call_rel_w(eip));
}
make_helper(call_rm_v) {
		return (suffix == 'l' ? call_rm_l(eip) : call_rm_w(eip));
}
make_helper(ret_n_v) {
	return (suffix =='l' ? ret_n_l(eip) : ret_n_w(eip));
}
make_helper(ret_ni_v) {
	return (suffix =='l' ? ret_ni_l(eip) : ret_ni_w(eip));
}
