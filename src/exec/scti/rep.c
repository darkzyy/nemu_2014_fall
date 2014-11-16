#include "exec/helper.h"

#define DATA_BYTE 1
#include "rep-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "rep-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "rep-template.h"
#undef DATA_BYTE

extern char suffix;

make_helper(rep_v) {
	return (suffix=='l' ? rep_l(eip) : rep_w(eip));
}
