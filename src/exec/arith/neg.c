#include "exec/helper.h"

#define DATA_BYTE 1
#include "neg-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "neg-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "neg-template.h"
#undef DATA_BYTE

extern char suffix;

make_helper(neg_v) {
	return (suffix == 'l' ? neg_l(eip) : neg_w(eip));
}
