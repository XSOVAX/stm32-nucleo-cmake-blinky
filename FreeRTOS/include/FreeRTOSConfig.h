#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

#include <stdint.h>

extern uint32_t SystemCoreClock;

#define configKERNEL_INTERRUPT_PRIORITY 255
#define configMAX_SYSCALL_INTERRUPT_PRIORITY 10

#define configCPU_CLOCK_HZ SystemCoreClock
#define configTICK_RATE_HZ (TickType_t)(1000)

#define configTOTAL_HEAP_SIZE (size_t)(18 * 1024) // 16 KB

#define configUSE_MALLOC_FAILED_HOOK 0
#define configMINIMAL_STACK_SIZE (unsigned short)128
#define configCHECK_FOR_STACK_OVERFLOW 0

#define configUSE_IDLE_HOOK 0
#define configUSE_TICK_HOOK 0
#define configSUPPORT_DYNAMIC_ALLOCATION 1
#define configSUPPORT_STATIC_ALLOCATION 0
#define config_LOWEST_INTERRUPT_PRIORITY 12
#define config_MAX_SYSCALL_INTERRUPT_PRIORITY 10

#define configMAX_PRIORITIES 5
#define configMAX_TASK_NAME_LEN 16
#define configUSE_16_BIT_TICKS 0
#define configIDLE_SHOULD_YIELD 1
#define configUSE_MUTEXES 0
#define configUSE_RECURSIVE_MUTEXES 0
#define configUSE_COUNTING_SEMAPHORES 0
#define configUSE_QUEUE 1
#define configUSE_TIMERS 0
#define configTIMER_TASK_PRIORITY 2
#define configTIMER_QUEUE_LENGTH 10
#define configTIMER_TASK_STACK_DEPTH 100
#define configEXPECTED_IDLE_TIME_BEFORE_SLEEP 5
#define configUSE_TICKLESS_IDLE 0
#define configUSE_TASK_NOTIFICATIONS 1

#define configUSE_PREEMPTION 0
#define configUSE_TIME_SLICING 0

// vTaskGetRunTimeStats

#define configUSE_TRACE_FACILITY 1
#define configUSE_STATS_FORMATTING_FUNCTIONS 1
#define configRECORD_STACK_HIGH_ADDRESS 1 // RTOS View сколько стека осталось
#define configGENERATE_RUN_TIME_STATS                                                              \
    1 // Rtos View показывать процент времени CPU, которое каждая задача использовала
#define configQUEUE_REGISTRY_SIZE 10

// Используем SysTick как источник для runtime stats

extern volatile uint32_t ulHighFrequencyTimerTicks;

#define portCONFIGURE_TIMER_FOR_RUN_TIME_STATS() (ulHighFrequencyTimerTicks = 0)
#define portGET_RUN_TIME_COUNTER_VALUE() ulHighFrequencyTimerTicks

#define INCLUDE_vTaskDelay 1
#define INCLUDE_xTaskDelayUntil 1
// #define INCLUDE_vTaskPrioritySet        		1
// #define INCLUDE_uxTaskPriorityGet       		1
// #define INCLUDE_vTaskCleanUpResources   		0
// #define INCLUDE_vTaskSuspend             		1
// #define INCLUDE_xTaskGetSchedulerState   		0
#endif