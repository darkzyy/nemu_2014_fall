#include "exec/helper.h"

#define DATA_BYTE 1
#include "idiv-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "idiv-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "idiv-template.h"
#undef DATA_BYTE

extern char suffix;

make_helper(idiv_rm2r_v) {
	return (suffix == 'l' ? idiv_rm2r_l(eip) : idiv_rm2r_w(eip));
}
