#ifndef __LES__TYPE__DEFINE__BY__MACHUNLEI__H__
#define __LES__TYPE__DEFINE__BY__MACHUNLEI__H__
#include <sys/types.h>
#include "LESConfig.h"

typedef size_t  LES_SemaphoreId;
typedef size_t  LES_MessageQueueId;
typedef size_t  LES_TaskId;
typedef size_t  LES_EventId;
typedef size_t  LES_TaskPriority;
typedef int     LES_Size;
typedef size_t  LES_Address;
typedef size_t  LES_Argument;

typedef size_t  LES_Register;
typedef size_t  LES_CheckSum;
typedef size_t  LES_Counter;

typedef size_t  LES_String[LES_MAXNAMELEN / sizeof(LES_Size)];

/* FIXME change it to real type */
typedef size_t  LES_Atomic;
#endif
