#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"

make_helper(concat(cwdq_,SUFFIX)) {
	DATA_TYPE_S mask=1,tmp=-1;
	mask<<=8*DATA_BYTE-1;
	if((REG(0)&mask)==0)
		REG(2)=0;
	else
		REG(2)=tmp;
	print_asm("cwdq" str(SUFFIX));
	return 1;
}

#include "exec/template-end.h"
