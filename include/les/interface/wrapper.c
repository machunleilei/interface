/* can not include the direction #include <les/interface/wrapper.h> */

#include <types.h>
#include <tasks.h>
#include <status.h>

/* 对信号量操作的封装 */
ACoreOs_status_code LES_ACoreOs_semaphore_obtain(
	ACoreOs_id id,
	UINT32 option_set,
	ACoreOs_interval timeout){
	return ACoreOs_semaphore_obtain(id, option_set, timeout);
}

ACoreOs_status_code LES_ACoreOs_semaphore_release(
	ACoreOs_id id){
	return ACoreOs_semaphore_release(id);
}

void LES_ACoreOs_semaphore_release_end(void){
	int __temp = 10;
	(void)__temp;
}
