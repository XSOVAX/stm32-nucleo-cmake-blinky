#include "stm32f103xb.h"

void delay( volatile uint32_t count ) {
	while ( count-- ) { __NOP(); };
}

int main( void ) {
  RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
  GPIOA->CRL &= ~(GPIO_CRL_MODE5 | GPIO_CRL_CNF5);
  GPIOA->CRL |= GPIO_CRL_MODE5_1 | GPIO_CRL_MODE5_0;

  while( 1 ) {

      GPIOA->ODR ^= GPIO_ODR_ODR5;
      delay( 900000 );

  } 
}
