#include "exec/helper.h"

#define DATA_BYTE 2
#include "lea-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "lea-template.h"
#undef DATA_BYTE

extern char suffix;

make_helper(lea_rm2r_v) {
	return (suffix == 'l' ? lea_rm2r_l(eip) : lea_rm2r_w(eip));
}
