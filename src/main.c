#include "stm32f103xb.h"
#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"



void vBlinkTask(void *pvParameters);

// Хук при неудачном malloc
void vApplicationMallocFailedHook(void) {
  configASSERT(0);
}

// Хук при переполнении стека
void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName) {
  (void) xTask;
  (void) pcTaskName;
  configASSERT(0);
}

// Хук в idle-задаче
void vApplicationIdleHook(void) {
    // Можно добавить низкоприоритетные задачи
}

// Хук по тику
void vApplicationTickHook(void) {
    // Можно добавить фоновые задачи
}


int main( void ) {
  
  SystemInit();

  xTaskCreate( vBlinkTask, "blink", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, NULL );

  vTaskStartScheduler();

  while( 1 ) {  } 
}


void vBlinkTask(void *pvParameters) {

  RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
  GPIOA->CRL &= ~(GPIO_CRL_MODE5 | GPIO_CRL_CNF5);
  GPIOA->CRL |= GPIO_CRL_MODE5_1 | GPIO_CRL_MODE5_0;

  for (;;) {
    GPIOA->ODR ^= GPIO_ODR_ODR5;
    vTaskDelay(pdMS_TO_TICKS(500));
  }
}