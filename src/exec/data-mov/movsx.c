#include "exec/helper.h"

#define DATA_BYTE 1
#include "movsx-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "movsx-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "movsx-template.h"
#undef DATA_BYTE

extern char suffix;

make_helper(movsw_v) {
	return movsw_l(eip);
}
make_helper(movsb_v) {
	return (suffix=='l'? movsb_l(eip) : movsb_w(eip));
}
