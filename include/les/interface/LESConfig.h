#ifndef __LES__CONFIG__BY__MACHUNLEI__H__
#define __LES__CONFIG__BY__MACHUNLEI__H__

#define LES_TASKARGUMENTNUMS    10 /*配置任务参数个数*/
#define LES_TASKREGISTERNUMS    32 /*配置保存任务上下文中寄存器的个数，R1~Rx*/

/*
 * 以下选项配置内核中任务TCB中插桩代码
 */
#undef  LES__DEFINERECORDFLAG /*表明启用内核中定义的LES_RecordFlag结构体定义，具体参见data_define.h文件*/
#define LES__COUNTERNUMS 3 /*配置内核中计数器的个数*/

#define SYS_TCB     Thread_Control /* 配置内核中控制块结构体名字 */

#define LES_MAXNAMELEN  128 /* 配置内核所支持的最长的任务名 */

#define LES_EVENT_BASE  0x4C4553 /* 配置自定义事件的开始数值, 默认是 "LES" */

#define LES_COUNTER_SEM_IDENT 	0
#define LES_COUNTER_MSGQ_IDENT 	1
#endif
