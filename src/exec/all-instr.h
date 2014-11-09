#include "prefix/prefix.h"

#include "dopc/dopc.h"

#include "data-mov/mov.h"
#include "data-mov/movzx.h"
#include "data-mov/push.h"
#include "data-mov/pop.h"

#include "misc/misc.h"
#include "misc/lea.h"


#include "logic/test.h"
#include "logic/or.h"
#include "logic/and.h"
#include "logic/xor.h"
#include "logic/shift.h"

#include "transfer/jcc.h"
#include "transfer/jmp.h"
#include "transfer/call.h"

#include "arith/cmp.h"
#include "arith/add.h"
#include "arith/adc.h"
#include "arith/sub.h"
#include "arith/sbb.h"
#include "arith/mul.h"
#include "arith/imul.h"
#include "arith/div.h"
#include "arith/idiv.h"
#include "arith/neg.h"
#include "arith/not.h"
#include "arith/dec.h"
#include "arith/inc.h"
