#ifndef __LES__CONFIG__BY__MACHUNLEI__H__
#define __LES__CONFIG__BY__MACHUNLEI__H__

#define LES_TASKARGUMENTNUMS    10 /*���������������*/
#define LES_TASKREGISTERNUMS    32 /*���ñ��������������мĴ����ĸ�����R1~Rx*/

/*
 * ����ѡ�������ں�������TCB�в�׮����
 */
#undef  LES__DEFINERECORDFLAG /*���������ں��ж����LES_RecordFlag�ṹ�嶨�壬����μ�data_define.h�ļ�*/
#define LES__COUNTERNUMS 3 /*�����ں��м������ĸ���*/

#define SYS_TCB     Thread_Control /* �����ں��п��ƿ�ṹ������ */

#define LES_MAXNAMELEN  128 /* �����ں���֧�ֵ���������� */

#define LES_EVENT_BASE  0x4C4553 /* �����Զ����¼��Ŀ�ʼ��ֵ, Ĭ���� "LES" */

#define LES_COUNTER_SEM_IDENT 	0
#define LES_COUNTER_MSGQ_IDENT 	1
#endif
