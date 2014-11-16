#include "exec/helper.h"

#define DATA_BYTE 1
#include "movs-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "movs-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "movs-template.h"
#undef DATA_BYTE

extern char suffix;

make_helper(movs_m_v) {
	return (suffix=='l' ? movs_m_l(eip) : movs_m_w(eip));
}
