#ifndef __LES__INTERFACE__DEFINE__BY__MACHUNELEI__H__
#define __LES__INTERFACE__DEFINE__BY__MACHUNELEI__H__
/*
 * 该模块实现了定义的接口
 */

#include "function_define.h"
#include "event_define.h"
#include "data_define.h"
#include <sys/types.h>

#if 0
    static size_t LES_CRC32(void* stackAddr, LES_Size len){
        LES_Size __value = 0;
        LES_Size __i = 0;
        LES_Size last3Bytes = 0;
        while(__i ++ < len / 4){
            __value ^= *(((size_t*)stackAddr) + (__i << 2));
        }
        __i = len % 4;
        if(__i >= 3)
            last3Bytes = (*(((char*)stackAddr) + len - 3));
        if(__i >= 2)
            last3Bytes = (last3Bytes << 8) | (*(((char*)stackAddr) + len - 2));
        if(__i >= 1)
            last3Bytes = (last3Bytes << 8) | (*(((char*)stackAddr) + len - 1));
        return __value ^ last3Bytes;
    }
#endif

/*
#define LES_GetCurrentPC()  \
    ({\
         LES_Address __pcCount;   \
         __asm__ __volatile__("bl 1f\r\n"\
             "1:\r\n"\
             "mr %%lr, %0\r\n"\
             :"=r"(__pcCount));\
         __pcCount;\
     })
*/

#define LES_GetCurrentPC()  \
    ({\
         LES_Address __pcCount = 0;   \
         __asm__ __volatile__("bl 1f\r\n"\
             "1:\r\n"\
             "mflr, %0\r\n"\
             :"=r"(__pcCount));\
         __pcCount;\
     })

#define __LES__SYSCALLEXTBEGIN              \
    __LES__DO                               \
        LES_Address __pcCount = LES_GetCurrentPC();\
        __LES__IF(__LES__RR)

#define __LES__SYSCALLEXTEND              \
    __LES__EVENTLOGEND
#define __LES__SYSCALLEXTMIDDLE

#define __LES__CONTEXTSWITCHBEGIN           \
    __LES__DO                               \
        __LES__IF(__LES__RR)

#define __LES__FAKECONTEXTSWITCHBEGIN       \
    __LES__DO                               \
        __LES__IF(__LES__RR)


#define __LES__CONTEXTSWITCHEND             \
    __LES__EVENTLOGEND

#define __LES__FAKECONTEXTSWITCHEND         \
    __LES__EVENTLOGEND

#define __LES__CONTEXTSWITCHMIDDLE
#define __LES__FAKECONTEXTSWITCHMIDDLE


/*************************************************
 * 任务切换事件记录
 */
#define LES_ContextSwitchLog(taskId, taskContextAddr, crc32, taskTcb)    \
    __LES__CONTEXTSWITCHBEGIN               \
        LES_CounterResetAll(taskTcb); \
        LES_EventParamInt_3X(LES_EVENT_CONTEXTSWITCH, taskId, crc32, taskContextAddr);  \
    __LES__CONTEXTSWITCHMIDDLE              \
    __LES__CONTEXTSWITCHEND

#define LES_FakeContextSwitchLog(taskId, taskTcb)  \
    __LES__FAKECONTEXTSWITCHBEGIN               \
        LES_CounterResetAll(taskTcb); \
        LES_EventParamInt_1(LES_EVENT_FAKECONTEXTSWITCH, taskId);    \
    __LES__FAKECONTEXTSWITCHMIDDLE              \
    __LES__FAKECONTEXTSWITCHEND


/*************************************************
 * 信号量操作相关事件记录
 */
#define LES_SemaphoreCreateLog(count, taskId, taskTcb, name)  \
    __LES__SYSCALLEXTBEGIN                              \
        LES_Counter __count = LES_CounterGet(taskTcb, LES_COUNTER_SEM);     \
        LES_CounterInc(taskTcb, LES_COUNTER_SEM);   \
        LES_EventParamIntString_41(LES_EVENT_SEMCREATE,\
                (LES_SemaphoreId)count,        \
                (LES_TaskId)taskId,             \
                __pcCount,                      \
                __count,	\
                name);                       \
    __LES__SYSCALLEXTMIDDLE                     \
    __LES__SYSCALLEXTEND

#define LES_SemaphoreTakeLog(semId, taskId, taskTcb)    \
    __LES__SYSCALLEXTBEGIN                  \
        LES_Counter __count = LES_CounterGet(taskTcb, LES_COUNTER_SEM);       \
        LES_CounterInc(taskTcb, LES_COUNTER_SEM);   \
        LES_EventParamInt_4(LES_EVENT_SEMTAKE,  \
                (LES_SemaphoreId)semId,         \
                (LES_TaskId)taskId,             \
                __pcCount,                      \
                __count);                       \
    __LES__SYSCALLEXTMIDDLE                     \
    __LES__SYSCALLEXTEND


#define LES_SemaphoreGiveLog(semId, taskId, taskTcb)    \
    __LES__SYSCALLEXTBEGIN                  \
        LES_Counter __count = LES_CounterGet(taskTcb, LES_COUNTER_SEM);       \
        LES_CounterInc(taskTcb, LES_COUNTER_SEM);   \
        LES_EventParamInt_4(LES_EVENT_SEMGIVE,  \
                (LES_SemaphoreId)semId,         \
                (LES_TaskId)taskId,             \
                __pcCount,                      \
                __count);                       \
    __LES__SYSCALLEXTMIDDLE                     \
    __LES__SYSCALLEXTEND


/*************************************************
 * 消息队列操作相关事件记录
 */
#define LES_MessageQueueCreateLog(count, taskId, taskTcb, msgName)   \
    __LES__SYSCALLEXTBEGIN                  \
        LES_Counter __count = LES_CounterGet(taskTcb, LES_COUNTER_MSGQ);       \
        LES_CounterInc(taskTcb, LES_COUNTER_MSGQ);   \
        LES_EventParamIntString_41(LES_EVENT_MSGQCREATE,  \
                (LES_MessageQueueId)count,         \
                (LES_TaskId)taskId,             \
                __pcCount,                      \
                __count, msgName);                       \
    __LES__SYSCALLEXTMIDDLE                     \
    __LES__SYSCALLEXTEND

#define LES_MessageQueueRecvLog(msgId, buffer, bufferLen, taskId, taskTcb)   \
    __LES__SYSCALLEXTBEGIN                  \
        LES_Counter __count = LES_CounterGet(taskTcb, LES_COUNTER_MSGQ);       \
        LES_CounterInc(taskTcb, LES_COUNTER_MSGQ);   \
        LES_EventParamInt_4(LES_EVENT_MSGQRECV,  \
                (LES_MessageQueueId)msgId,         \
                (LES_TaskId)taskId,             \
                __pcCount,                      \
                __count);                       \
    __LES__SYSCALLEXTMIDDLE                     \
    __LES__SYSCALLEXTEND

#define LES_MessageQueueSendLog(msgId, buffer, bufferLen, taskId, taskTcb)  \
    __LES__SYSCALLEXTBEGIN                  \
        LES_Counter __count = LES_CounterGet(taskTcb, LES_COUNTER_MSGQ);       \
        LES_CounterInc(taskTcb, LES_COUNTER_MSGQ);   \
        LES_EventParamInt_4(LES_EVENT_MSGQSEND,  \
                (LES_MessageQueueId)msgId,         \
                (LES_TaskId)taskId,             \
                __pcCount,                      \
                __count);                       \
    __LES__SYSCALLEXTMIDDLE                     \
    __LES__SYSCALLEXTEND

/*************************************************
 * 任务操作相关事件记录
 */
#define LES_TaskCreateLog(taskId, name, priority, option, stackSize)    \
    __LES__DO   \
        __LES__IF(__LES__RR)  \
            LES_EventParamIntString_41(LES_EVENT_TASKCREATE,\
                    taskId,\
                    priority,\
                    option,\
                    stackSize,\
                    name);  \
    __LES__SYSCALLEXTEND

#define LES_TaskStartLog(taskId, entryPoint, args)                      \
    __LES__DO   \
        __LES__IF(__LES__RR)    \
            LES_EventParamInt_3(LES_EVENT_TASKSTART,\
                    taskId, \
                    (LES_Address)entryPoint,\
                    (LES_Address)args); \
    __LES__SYSCALLEXTEND


#define LES_TaskDelayLog(taskId, howLong)   \
    __LES__DO   \
        __LES__IF(__LES__RR)    \
            LES_EventParamInt_2(LES_EVENT_TASKDELAY,\
                    taskId, \
                    (LES_Counter)howLong);  \
    __LES__SYSCALLEXTEND


/*************************************************
 * 使能调度相关事件记录
 */
#define LES_SyncRescheduleLog(taskId, nestLevel, needReschedule)    \
    __LES__DO   \
        LES_Address __pcCount = LES_GetCurrentPC();\
        __LES__IF(__LES__RR)    \
            LES_EventParamInt_4(LES_EVENT_SYNCRESCHEDULE,\
                    taskId, \
                    (LES_Counter)nestLevel, \
                    __pcCount,	\
                    needReschedule);        \
    __LES__SYSCALLEXTEND


/*************************************************
 * 中断相关事件记录
 */
#define LES_InterruptEnterLog(intVector, nestLevel)        \
    __LES__DO   \
        __LES__IF(__LES__RR)    \
            LES_EventParamInt_2(LES_EVENT_INTERRUPTENTER,\
            		(LES_Counter)intVector,		\
                    (LES_Counter)nestLevel);     \
    __LES__SYSCALLEXTEND

#define LES_InterruptExitLog(intVector, nestLevel)         \
    __LES__DO   \
        __LES__IF(__LES__RR)    \
            LES_EventParamInt_2(LES_EVENT_INTERRUPTEXIT, \
            		(LES_Counter)intVector,		\
                    (LES_Counter)nestLevel);    \
    __LES__SYSCALLEXTEND



/*控制记录接口*/
void LES_LogOn();
void LES_LogOff();

#endif
