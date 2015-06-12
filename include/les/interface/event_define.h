#ifndef __LES__MACHUNLEI__H__
#define __LES__MACHUNLEI__H__

#   ifdef __cplusplus
extern "C"{
#   endif

#include "LESConfig.h"
#include "type_define.h"

#ifdef LES_EVENT_BASE
#   define LES_EVENT_BEGIN             (LES_EVENT_BASE)
#else
#   define LES_EVENT_BEGIN             (0x4C4553)
#endif

#define LES_EVENT_IDENT(value)  \
    (LES_EVENT_BEGIN + (value))


/*************************************************
 * 定义每种事件起始偏移量
 */
#define LES_EVENT_SEM_OFFSET            (0)
#define LES_EVENT_MSGQ_OFFSET           (100)
#define LES_EVENT_TASK_OFFSET           (200)
#define LES_EVENT_CONTEXT_OFFSET        (300)
#define LES_EVENT_INTERRUPT_OFFSET      (400)
#define LES_EVENT_RESCHEDULE_OFFSET     (500)

#define LES_EVENT_SEMIDENT(value)   \
    LES_EVENT_IDENT(value + LES_EVENT_SEM_OFFSET)

#define LES_EVENT_MSGQIDENT(value)   \
    LES_EVENT_IDENT(value + LES_EVENT_MSGQ_OFFSET)

#define LES_EVENT_TASKIDENT(value)   \
    LES_EVENT_IDENT(value + LES_EVENT_TASK_OFFSET)

#define LES_EVENT_CONTEXTIDENT(value)   \
    LES_EVENT_IDENT(value + LES_EVENT_CONTEXT_OFFSET)

#define LES_EVENT_INTERRUPTIDENT(value)   \
    LES_EVENT_IDENT(value + LES_EVENT_INTERRUPT_OFFSET)

#define LES_EVENT_RESCHEDULEIDENT(value)   \
    LES_EVENT_IDENT(value + LES_EVENT_RESCHEDULE_OFFSET)

/*************************************************
 * 信号量相关事件定义
 */
#define LES_EVENT_SEMCREATE             LES_EVENT_SEMIDENT(0)

#define LES_EVENT_SEMTAKE               LES_EVENT_SEMIDENT(1)

#define LES_EVENT_SEMGIVE               LES_EVENT_SEMIDENT(2)


/*************************************************
 * 消息队列相关事件定义
 */
#define LES_EVENT_MSGQCREATE            LES_EVENT_MSGQIDENT(0)

#define LES_EVENT_MSGQSEND              LES_EVENT_MSGQIDENT(1)

#define LES_EVENT_MSGQRECV              LES_EVENT_MSGQIDENT(2)


/*************************************************
 * 任务相关事件定义
 */
#define LES_EVENT_TASKCREATE            LES_EVENT_TASKIDENT(0)

#define LES_EVENT_TASKSTART             LES_EVENT_TASKIDENT(1)

#define LES_EVENT_TASKDELAY             LES_EVENT_TASKIDENT(2)


/*************************************************
 * 上下文切换相关事件定义
 */
#define LES_EVENT_CONTEXTSWITCH         LES_EVENT_CONTEXTIDENT(0)

#define LES_EVENT_FAKECONTEXTSWITCH     LES_EVENT_CONTEXTIDENT(1)


/*************************************************
 * 中断相关事件定义
 */
#define LES_EVENT_INTERRUPTENTER        LES_EVENT_INTERRUPTIDENT(0)

#define LES_EVENT_INTERRUPTEXIT         LES_EVENT_INTERRUPTIDENT(1)

#define LES_EVENT_INTERRUPTEXIT_CONTEXT LES_EVENT_INTERRUPTIDENT(2)


/*************************************************
 * 同步事件调度点事件
 */
#define LES_EVENT_SYNCRESCHEDULE        LES_EVENT_RESCHEDULEIDENT(0)

#define LES_EVENT_INTERRUPTRESCHEDULE   LES_EVENT_RESCHEDULEIDENT(1)

/* 需要删除的事件 */
#define LES_EVENT_INTERFLAG             LES_EVENT_INTERRUPTIDENT(2)

#   ifdef __cplusplus
}
#   endif

#endif
