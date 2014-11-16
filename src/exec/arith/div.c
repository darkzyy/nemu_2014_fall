#include "exec/helper.h"

#define DATA_BYTE 1
#include "div-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "div-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "div-template.h"
#undef DATA_BYTE

extern char suffix;

make_helper(div_rm2r_v) {
	return (suffix == 'l' ? div_rm2r_l(eip) : div_rm2r_w(eip));
}
