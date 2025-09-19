#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

#include <stdint.h>

extern uint32_t SystemCoreClock;

// ���������� ����������
#define configKERNEL_INTERRUPT_PRIORITY         255  // ������ ��������� (STM32)
#define configMAX_SYSCALL_INTERRUPT_PRIORITY    16   // ������������ ��������� ��� ���������� �������

#define configCPU_CLOCK_HZ                    	SystemCoreClock
#define configTICK_RATE_HZ                    	( TickType_t ) 	( 1000 ) 

// ������ ��� STM32F103C8 (20 KB SRAM)
#define configTOTAL_HEAP_SIZE          			( size_t ) 			( 18 * 1024 )  // 16 KB

#define configUSE_MALLOC_FAILED_HOOK				1	// �������� ������� �� ����
#define configMINIMAL_STACK_SIZE              	( unsigned short ) 128 
#define configCHECK_FOR_STACK_OVERFLOW				1	// 0 - ��� �������� �� ������������
																	// 1 - ������ �������� � ��������� �������� �� ������������������
																	// 2 - ������ �������� � ��� ������������� � �������� �� ������������������
	
#define configUSE_IDLE_HOOK                     1
#define configUSE_TICK_HOOK                     1
#define configSUPPORT_STATIC_ALLOCATION       	0
#define configSUPPORT_DYNAMIC_ALLOCATION      	1	// ������������ ��������� ������

#define config_LOWEST_INTERRUPT_PRIORITY			15 // ������ ��������� ����������
#define config_MAX_SYSCALL_INTERRUPT_PRIORITY	10 // ������������, ������� ����� ������������ ��������� � RTOS 
																	// �� �������� ��������� ���������� FromISR ������� ������ ������������ ����������

#define configMAX_PRIORITIES                  	5
#define configMAX_TASK_NAME_LEN               	16
#define configUSE_16_BIT_TICKS                	0
#define configIDLE_SHOULD_YIELD               	1
#define configUSE_MUTEXES                     	0	// 1 ��� ������������� ��������� ���������
#define configUSE_RECURSIVE_MUTEXES           	0
#define configUSE_COUNTING_SEMAPHORES         	0	// 1 ��� ������������� ����������� ������� ���������
#define configUSE_QUEUE                      	1	// 1 ��� ������������� ����������� ��������
#define configUSE_TIMERS                      	1	// 1 ��� ������������� ����������� ��������
#define configTIMER_TASK_PRIORITY             	2
#define configTIMER_QUEUE_LENGTH              	10
#define configTIMER_TASK_STACK_DEPTH          	100
#define configEXPECTED_IDLE_TIME_BEFORE_SLEEP	5	// ��������� ��� Tickless idle  ������� � ���������� ����� ������� ��� �� ���� � ���
																	// (�� ���� ����������� ����� ����� ������� � ���� ���������� ��� ����� �� ����� � ���)
#define configUSE_TICKLESS_IDLE						0	// 0 Tickless idle �� ������������
																	//	1 ������������ ��������� ����������  ������� portSUPPRESS_TICKS_AND_SLEEP()
																	// 2 ������������ ���������������� ���������� portSUPPRESS_TICKS_AND_SLEEP()
#define configUSE_TASK_NOTIFICATIONS				1 	// ���������������� ����������� � �������
/*
������������ "����������� ������������"
�� ��������������� ��������� ���������� �����
�� ��������� ������ � ����� ������� ����������� ��������� ������������� ������ � ��������� "������" � ������ ����� ����� ������ ������.
� ������ ������� ��� ����� ����� ������� �� ��������� ������
*/
//#define configUSE_PREEMPTION               		1
//#define configUSE_TIME_SLICING              		1
/*
������������ "����������� ������������"
���� ����������� ���������� ������ ���� ������ � ���������� �����������, ��� ���������� ������������ ���� ��������� ������ � ������� �����������
��� ����������� �������, ������ ������������� ����, �������� ��������� ������� ������� ��� ����� ����������� ����������
����� ����������� �������
*/
//#define configUSE_PREEMPTION               		1
//#define configUSE_TIME_SLICING              		0

/*
������������ "������������� ���������������"
���� ����������� ����������� ������������
������������� ���������� ������ ��� ����� �������� ������ � ��������� "�������������" ��� ��� � ������� ������ �������� taskYIELD()
������������ ��� �� ������������� ������������� ������ � ���� �� ������� ��� ��������� ������������ ����������� ��������
*/
#define configUSE_PREEMPTION               		0
#define configUSE_TIME_SLICING              		0 // ��� 1



// ��� vTaskGetRunTimeStats ��� �� �������� ���������� �� �������
//#define configGENERATE_RUN_TIME_STATS				1	
//#define configUSE_STATS_FORMATTING_FUNCTIONS 		1
//#define portCONFIGURE_TIMER_FOR_RUN_TIME_STATS 	1	// ������������ ����������� ���������







#define INCLUDE_vTaskDelay 							1	// �������� vTaskDelay
//#define INCLUDE_vTaskPrioritySet        		1	// ��� ���������� ������������
//#define INCLUDE_uxTaskPriorityGet       		1	// ��� �� ���������� ���������
//#define INCLUDE_vTaskCleanUpResources   		0
//#define INCLUDE_vTaskSuspend             		1
//#define INCLUDE_xTaskGetSchedulerState   		0
#endif