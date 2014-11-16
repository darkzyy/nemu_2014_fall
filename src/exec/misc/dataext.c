#include "exec/helper.h"

#define DATA_BYTE 2
#include "dataext-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "dataext-template.h"
#undef DATA_BYTE

extern char suffix;

make_helper(cwdq_v) {
	return (suffix=='l' ? cwdq_l(eip) : cwdq_w(eip));
}
