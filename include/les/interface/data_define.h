#ifndef __LES__DATA_DEFINE__BY__CHUNLEI__H__
#define __LES__DATA_DEFINE__BY__CHUNLEI__H__

#   ifdef __cplusplus
extern "C"{
#   endif

#include "type_define.h"

#ifndef LES_COUNTER_SEM_IDENT
#	define LES_COUNTER_SEM_IDENT 0
#endif

#ifndef LES_COUNTER_MSGQ_IDENT
#	define LES_COUNTER_MSGQ_IDENT 1
#endif

typedef enum{
    LES_COUNTER_SEM 	= LES_COUNTER_SEM_IDENT,
    LES_COUNTER_MSGQ 	= LES_COUNTER_MSGQ_IDENT,
    LES_COUNTER_MAX,
}LES_CounterEnum;

#if 0

#ifndef LES__COUNTERNUMS
#   define LES__COUNTERNUMS LES_COUNTER_MAX
#endif


LES_Counter counters[LES__COUNTERNUMS];
#endif



/*阶段设置*/
#define LES_RECORD_PHASE    0x1
#define LES_REPLAY_PHASE    0x2

/*开启日志设置*/
#define LES_LOG_ON      0x1
#define LES_LOG_OFF     0x2

extern  LES_Atomic LES_RecordReplay;
extern  LES_Atomic LES_LogOpen;
/*引用了外部的函数，该函数实现具体的日志记录*/
extern void LES_EventLogHandle(LES_EventId, const void*, LES_Size);
extern void LES_Context2Registers(void* const, LES_Size, const void*);
extern size_t LES_CRC32(void* stackAddr, LES_Size len);
extern void LES_InterruptExitReschedule();

#   ifdef __cplusplus
}
#   endif
#endif
