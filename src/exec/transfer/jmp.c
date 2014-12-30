#include "exec/helper.h"

#define DATA_BYTE 1
#include "jmp-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "jmp-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "jmp-template.h"
#undef DATA_BYTE

extern char suffix;

make_helper(jmp_rel_v) {
	return (suffix == 'l' ? jmp_rel_l(eip) : jmp_rel_w(eip));
}
make_helper(jmp_rm_v) {
	return (suffix == 'l' ? jmp_rm_l(eip) : jmp_rm_w(eip));
}
make_helper(ljmp_v) {
	return (suffix == 'l' ? ljmp_l(eip) : ljmp_w(eip));
}
