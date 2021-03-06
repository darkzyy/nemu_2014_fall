#include "exec/helper.h"

#define DATA_BYTE 1
#include "jcc-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "jcc-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "jcc-template.h"
#undef DATA_BYTE

extern char suffix;

make_helper(ja_v) {
	return (suffix == 'l' ? ja_l(eip) : ja_w(eip));
}
make_helper(jae_v) {
	return (suffix == 'l' ? jae_l(eip) : jae_w(eip));
}
make_helper(jb_v) {
	return (suffix == 'l' ? jb_l(eip) : jb_w(eip));
}
make_helper(jbe_v) {
	return (suffix == 'l' ? jbe_l(eip) : jbe_w(eip));
}
make_helper(jcxz_v) {
	return (suffix == 'l' ? jcxz_l(eip) : jcxz_w(eip));
}
make_helper(jecxz_v) {
	return (suffix == 'l' ? jecxz_l(eip) : jecxz_w(eip));
}
make_helper(je_v) {
	return (suffix == 'l' ? je_l(eip) : je_w(eip));
}
make_helper(jg_v) {
	return (suffix == 'l' ? jg_l(eip) : jg_w(eip));
}
make_helper(jge_v) {
	return (suffix == 'l' ? jge_l(eip) : jge_w(eip));
}
make_helper(jl_v) {
	return (suffix == 'l' ? jl_l(eip) : jl_w(eip));
}
make_helper(jle_v) {
	return (suffix == 'l' ? jle_l(eip) : jle_w(eip));
}
make_helper(jne_v) {
	return (suffix == 'l' ? jne_l(eip) : jne_w(eip));
}
make_helper(jno_v) {
	return (suffix == 'l' ? jno_l(eip) : jno_w(eip));
}
make_helper(jns_v) {
	return (suffix == 'l' ? jns_l(eip) : jns_w(eip));
}
make_helper(jo_v) {
	return (suffix == 'l' ? jo_l(eip) : jo_w(eip));
}
make_helper(jpo_v) {
	return (suffix == 'l' ? jpo_l(eip) : jpo_w(eip));
}
make_helper(jpe_v) {
	return (suffix == 'l' ? jpe_l(eip) : jpe_w(eip));
}
make_helper(js_v) {
	return (suffix == 'l' ? js_l(eip) : js_w(eip));
}
