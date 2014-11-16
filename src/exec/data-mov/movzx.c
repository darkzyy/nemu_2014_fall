#include "exec/helper.h"

#define DATA_BYTE 1
#include "movzx-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "movzx-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "movzx-template.h"
#undef DATA_BYTE

extern char suffix;

make_helper(movzw_v) {
	return movzw_l(eip);
}
make_helper(movzb_v) {
	return (suffix=='l'? movzb_l(eip) : movzb_w(eip));
}
