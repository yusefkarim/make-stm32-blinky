#ifndef BLINKY_H
#define BLINKY_H

/*
 * Accepts GPIO_Typedef struct defined for GPIO ports in stm32l476xx.h and
 * and a pin number. Initializes that pin as an output with the characteristics
 * defined in the source file.
 *
 * FUNCTION USAGE:
 * ## Step 1: Initialize the clock for the port you want
 *    Ex. To enable the clock for port B, set the bit in AHB2ENR register
 *    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;
 * ## Step 2: Use this function to initialize the GPIO pin with defined settings
 *    Ex. Initializing pin PB2 as output
 *    GPIO_Pin_Output_Init(GPIOB, 2);
 * ## Step 3: Set or clear the specific pin you have initialized to turn on and off
 *    Ex. Turning pin PB2 on
 *    GPIO->ODR |= 1UL<<2
*/
void GPIO_Pin_Output_Init(GPIO_TypeDef *GPIO, unsigned short pin);

/*
 * Accepts GPIO_Typedef struct defined for GPIO ports in stm32l476xx.h and
 * and a pin number. Initializes that pin as an input with the characteristics
 * defined in the source file.
 *
 * FUNCTION USAGE:
 * ## Step 1: Initialize the clock for the port you want
 *    Ex. To enable the clock for port B, set the bit in AHB2ENR register
 *    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;
 * ## Step 2: Use this function to initialize the GPIO pin with defined settings
 *    Ex. Initializing pin PB8 as input
 *    GPIO_Pin_Input_Init(GPIOB, 8);
 * ## Step 3: Read the initialized pin by masking it with a logical AND
 *    Ex. Reading the value of pin PB8 (bit eight)
 *    GPIO->IDR & 0x100
*/
void GPIO_Pin_Input_Init(GPIO_TypeDef *GPIO, unsigned short pin);

/*
 * Initializes SysTick with interrupt enabled. Uses the processor clock (default 4MHz).
 * Overwrite the SysTick_Handler function defined in startup_stm32l476xx.s to do
 * tasks when the SysTick counts down to 0.
 *
 * Args:
 *      ticks: The number of clock ticks you want to wait before the SysTick interrupt
 *             occurs. Ex. Passing 4000000 for ticks will make the interrupt trigger
 *             every 1 second if the processor clock is set to 4MHz.
 */
void SysTick_Init(uint32_t ticks);

#endif
