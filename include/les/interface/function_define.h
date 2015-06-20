#ifndef __LES__FUNCTION__DEFINE__BY__MACHUNLEI__H__
#define __LES__FUNCTION__DEFINE__BY__MACHUNLEI__H__

#   ifdef __cplusplus
extern "C"{
#   endif

#include "LESConfig.h"
#include "type_define.h"
#include <string.h>

#define __LES__LOGOPEN  (LES_LogOpen & LES_LOG_ON)
#define __LES__DO                   \
    do{

#define __LES__DOEND(value)         \
    }while(value)

#define __LES__IF(value)            \
    if(value){

#define __LES__IFEND                \
    }

#define __LES__EVENTLOGBEGIN        \
    __LES__DO                       \
        __LES__IF(__LES__LOGOPEN)

#define __LES__EVENTLOGEND          \
        __LES__IFEND                     \
    __LES__DOEND(0)

/*
 * 记录开启
 */
#define __LES__RR   (LES_RecordReplay & LES_RECORD_PHASE)
/*
 * 将地址转换为TCB的变量
 */
#define __LES__Address2Tcb(tcb)     \
    ((SYS_TCB*)tcb)

/*
 * TCB中的某个计数器的值
 */
#define __LES__COUNTER(tcb, which)   \
    (__LES__Address2Tcb(tcb)->counters[which])

/*
 * 获取TCB中的某个计数器的值
 */
#define LES_CounterGet(tcb, which)   \
    __LES__COUNTER(tcb, which)

/*
 * 设置TCB中的某个计数器的值
 */
#define LES_CounterSet(tcb, which, value)   \
    __LES__COUNTER(tcb, which) = value

/*
 * 复位某个计数器数值
 */
#define LES_CounterReset(tcb, which)    \
    LES_CounterSet(tcb, which, 0)

/*
 * 复位所有计数器数值
 */
#define LES_CounterResetAll(tcb)    \
    __LES__DO       \
        LES_Size __i = 0;   \
        for(; __i < LES__COUNTERNUMS; __i ++)   \
            LES_CounterSet(tcb, __i, 0);    \
    __LES__DOEND(0)

/*
 * 递增某个计数器数值
 */
#define LES_CounterInc(tcb, which)    \
    LES_CounterGet(tcb, which) += 1

/*
 * 递减某个计数器数值
 */
#define LES_CounterDec(tcb, which)    \
    LES_CounterGet(tcb, which) -= 1


/*
 * 下面是具体记录不同参数
 */
/*
 * 记录的事件不需要参数
 */
#define LES_EventParam_0(eventId)   \
    __LES__EVENTLOGBEGIN            \
        LES_EventLogHandle(eventId, NULL, 0); \
    __LES__EVENTLOGEND


/*
 * 记录的事件需要1个参数
 */
typedef struct{
    LES_Size args[1];
}__LES_EventArg1;

#define LES_EventParamInt_1(eventId, arg1)     \
    __LES__EVENTLOGBEGIN                    \
        __LES_EventArg1 event;            \
        event.args[0] = arg1;           \
        LES_EventLogHandle(eventId, &event, sizeof(event)); \
    __LES__EVENTLOGEND

/*
 * 记录的事件需要2个参数
 */
typedef struct{
    LES_Size args[2];
}__LES_EventArg2;

#define LES_EventParamInt_2(eventId, arg1, arg2)     \
    __LES__EVENTLOGBEGIN                    \
        __LES_EventArg2 event;            \
        event.args[0] = arg1;           \
        event.args[1] = arg2;           \
        LES_EventLogHandle(eventId, &event, sizeof(event)); \
    __LES__EVENTLOGEND

/*
 * 记录的事件需要3个参数
 */
typedef struct{
    LES_Size args[3];
}__LES_EventArg3;

#define LES_EventParamInt_3(eventId, arg1, arg2, arg3)     \
    __LES__EVENTLOGBEGIN                    \
        __LES_EventArg3 event;            \
        event.args[0] = arg1;           \
        event.args[1] = arg2;           \
        event.args[2] = arg3;           \
        LES_EventLogHandle(eventId, &event, sizeof(event)); \
    __LES__EVENTLOGEND

/*
 * 记录的事件需要4个参数
 */
typedef struct{
    LES_Size args[4];
}__LES_EventArg4;

#define LES_EventParamInt_4(eventId, arg1, arg2, arg3, arg4)     \
    __LES__EVENTLOGBEGIN                    \
        __LES_EventArg4 event;            \
        event.args[0] = arg1;           \
        event.args[1] = arg2;           \
        event.args[2] = arg3;           \
        event.args[3] = arg4;           \
        LES_EventLogHandle(eventId, &event, sizeof(event)); \
    __LES__EVENTLOGEND

/*
 * 主要用于记录任务创建时候信息
 */
typedef struct{
    LES_Size args[4];
    LES_String string;
}__LES_EventTaskCreate;

#define __LES__SIZEALIGN(size)          \
    ((size + sizeof(LES_Size) - 1) / sizeof(LES_Size))

#define LES_EventParamIntString_41(eventId, arg1, arg2, arg3, arg4, name)  \
    __LES__EVENTLOGBEGIN                    \
        __LES_EventTaskCreate event;          \
        LES_Size size = __LES__SIZEALIGN(strlen(name)); \
        event.string[size] = event.string[size + 1] = 0;    \
        char* __name = (((char*)(&event.string)) + sizeof(LES_Size));\
        event.string[0] = size * 4;           \
        event.args[0] = arg1;               \
        event.args[1] = arg2;           \
        event.args[2] = arg3;           \
        event.args[3] = arg4;           \
        strcpy(__name, name);           \
        LES_EventLogHandle(eventId, &event, 4 * sizeof(LES_Size) + (size + 1) * 4);  \
    __LES__EVENTLOGEND

/*
 * 记录任务启动时候信息
 */
typedef struct{
    LES_Size args[3 + LES_TASKARGUMENTNUMS];
}__LES_EventTaskStart;

#define LES_EventParamInt_XX(eventId, arg1, arg2, arg3, args)  \
    __LES__EVENTLOGBEGIN                    \
        __LES_EventTaskStart event;          \
        event.args[0] = arg1;               \
        event.args[1] = arg2;           \
        event.args[2] = arg3;           \
        strcpy(__name, name);           \
        LES_EventLogHandle(eventId, &event, 4 * sizeof(LES_Size) + size * 4);    \
    __LES__EVENTLOGEND

/*
 * 记录任务切换时候信息
 */
typedef struct{
    LES_Size args[3 + LES_TASKREGISTERNUMS];
}__LES_EventContextSwitch;

#define LES_EventParamInt_3X(eventId, arg1, arg2, context)    \
    __LES__EVENTLOGBEGIN                    \
        __LES_EventContextSwitch event;          \
        event.args[0] = arg1;               \
        event.args[1] = arg2;           \
        LES_Context2Registers(&event.args[2], 1 + LES_TASKREGISTERNUMS, (const void*)context); \
        LES_EventLogHandle(eventId, &event, (3 + LES_TASKREGISTERNUMS) * sizeof(LES_Size));    \
    __LES__EVENTLOGEND


/*
 * 记录中断退出时被打断的任务的相关信息
 */
typedef struct{
    LES_Size args[21];
}__LES_EventInterruptContext;

#define LES_EventParamInt_21(eventId, taskId, contextAddress)   \
    __LES__EVENTLOGBEGIN                    \
    	__LES_EventInterruptContext event;\
    	event.args[0] = taskId;\
    	memcpy(&event.args[1], contextAddress, sizeof(LES_Size) * 20);\
        LES_EventLogHandle(eventId, &event, sizeof(LES_Size) * 21); \
    __LES__EVENTLOGEND



#   ifdef __cplusplus
}
#   endif
#endif
