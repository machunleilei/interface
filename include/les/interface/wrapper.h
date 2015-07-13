#ifndef __LES__WRAPPER__H__
#define	__LES__WRAPPER__H__

/* 凡是包含了该头文件，对信号量获取和释放将被映射到LES_xx_xx_xx操作上 */

#include <types.h>
#include <tasks.h>
#include <status.h>

extern ACoreOs_status_code LES_ACoreOs_semaphore_obtain(
	ACoreOs_id id,
	UINT32 option_set,
	ACoreOs_interval timeout
);

extern ACoreOs_status_code LES_ACoreOs_semaphore_release(
	ACoreOs_id id
);

/* 该函数用于信号量释放时的标杆 */
extern void LES_ACoreOs_semaphore_release_end(void);

#define ACoreOs_semaphore_obtain(arg0, arg1, arg2)	\
	LES_ACoreOs_semaphore_obtain(arg0, arg1, arg2)

#define ACoreOs_semaphore_release(arg0)	\
	LES_ACoreOs_semaphore_release(arg0);	\
	LES_ACoreOs_semaphore_release_end()

#endif