#include "stm32l476xx.h"
#include "blinky.h"
/* SEE HEADER FILE FOR DETAILED OVERVIEW OF DEFINED FUNCTIONS */

void GPIO_Pin_Output_Init(GPIO_TypeDef *GPIO, unsigned short pin) {
    // Set mode of pin as digital output
    // 00 = digital input       01 = digital output
    // 10 = alternate function  11 = analog (default)
    GPIO->MODER &= ~(3UL<<(2*pin));         // Clear mode bits
    GPIO->MODER |= 1UL<<(2*pin);            // Set mode = 01 (digital output)

    // Set output type of pin as push-pull
    // 0 = push-pull (default)
    // 1 = open-drain
    GPIO->OTYPER &= ~(1<<pin);

    // Set output speed of pin as low
    // 00 = low speed      01 = medium speed
    // 10 = fast speed     11 = high speed
    GPIO->OSPEEDR &= ~(3UL<<(2*pin));      // Clear speed bits

    // Set pin as no pull-up, no pull-down
    // 00 = no pull-up, no pull-down      01 = pull-up
    // 10 = pull-down                     11 = reserved
    GPIO->PUPDR &= ~(3UL<<(2*pin));        // no pull-up, no pull-down
}


void GPIO_Pin_Input_Init(GPIO_TypeDef *GPIO, unsigned short pin) {
    // Set mode of pin as digital input
    // 00 = digital input       01 = digital output
    // 10 = alternate function  11 = analog (default)
    GPIO->MODER &= ~(3UL<<(2*pin));         // Clear mode bits (also sets as input)

    // Set pin as no pull-up, no pull-down
    // 00 = no pull-up, no pull-down      01 = pull-up
    // 10 = pull-down                     11 = reserved
    GPIO->PUPDR &= ~(3UL<<(2*pin));        // no pull-up, no pull-down
}

void SysTick_Init(uint32_t ticks) {
    // Disable SysTick IRQ and SysTick counter
    SysTick->CTRL = 0;
    // Set reload register
    SysTick->LOAD = ticks - 1;

    // Set interrupt priority of SysTick as least urgent (highest priority number)
    // This function is defined in core_cm4.h
    NVIC_SetPriority(SysTick_IRQn, (1<<__NVIC_PRIO_BITS) - 1);

    // Reset the SysTick counter value (by writing to it)
    SysTick->VAL = 0;

    // Select processor clock
    // 1 = processor clock, 0 = external clock
    SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk;

    // Enables SysTick exception request
    // 1 = counting down to zero asserts the SysTick exception request
    // 0 = counting down to zero does not assert the SysTick exception request
    SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;

    // Enable SysTick timer
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
}


