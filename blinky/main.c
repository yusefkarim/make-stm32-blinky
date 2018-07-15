// Author: Yusef Karim
#include "stm32l476xx.h"
#include "blinky.h"

void SysTick_Handler(void) {
    // Toggle PC8 every SysTick interrupt
    GPIOC->ODR ^= 0x100;
}

int main(void)
{
    // Enable the clock to GPIO port C
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;
    GPIO_Pin_Output_Init(GPIOC, 8);
    // Clear state (off)
    GPIOC->ODR &= ~(1UL<<8);

    SysTick_Init(4000000);
}

