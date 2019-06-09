#include "stm32l476xx.h"
#include "init.h"

void System_Clock_80MHz_Init(void) {
    // To correctly read data from FLASH memory, the number of wait states
    // (LATENCY) must be correctly programmed according to the frequency
    // of the CPU clock (HCLK) and the supply voltage of the device.
    FLASH->ACR &= ~ FLASH_ACR_LATENCY;
    FLASH->ACR |= FLASH_ACR_LATENCY_2WS;

    // Enable the Internal High Speed oscillator (HSI)
    RCC->CR |= RCC_CR_HSION;
    while ((RCC->CR & RCC_CR_HSIRDY) == 0);
    // Adjusts the HSI calibration value, added to HSICAL[7:0] in ICSCR
    RCC->ICSCR &= ~RCC_ICSCR_HSITRIM;
    RCC->ICSCR |= RCC_ICSCR_HSITRIM_4;

    // Enable the Phase Lock Loop (PLL)
    RCC->CR &= ~RCC_CR_PLLON;
    while ((RCC->CR & RCC_CR_PLLRDY) == RCC_CR_PLLRDY);

    // Select HSI as clock source for PLL
    // 00 = No clock, 01 = MSI, 10 = HSI, 11 = HSE
    RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLSRC;
    RCC->PLLCFGR |= RCC_PLLCFGR_PLLSRC_HSI;

    // Configure PLL as 80 MHz
    // f = PLL clock input * (PLLN / PLLM) = 16 MHz * (20 / 2) = 160 MHz
    // f /= PLLR = 160 MHz / 2 = 80 MHz
    RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLN;
    RCC->PLLCFGR |= RCC_PLLCFGR_PLLN_4 | RCC_PLLCFGR_PLLN_2;
    RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLM;
    RCC->PLLCFGR |= RCC_PLLCFGR_PLLM_0;
    // 00: PLLR = 2, 01: PLLR = 4, 10: PLLR = 6, 11: PLLR = 8
    RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLR;

    // Enable Main PLL PLLCLK Output
    RCC->PLLCFGR |= RCC_PLLCFGR_PLLREN;
    // Enable the PLL clock and wait until it is ready
    RCC->CR |= RCC_CR_PLLON;
    while ((RCC->CR & RCC_CR_PLLRDY) == 0);

    // Select PLL as system clock
    RCC->CFGR &= ~RCC_CFGR_SW;
    // 00: MSI, 01: HSI, 10: HSE, 11: PLL
    RCC->CFGR |= RCC_CFGR_SW_PLL;

    // Wait until System Clock has been selected
    while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL);
}

void LED2_Init(void) {
    // Enable the clock to GPIO port A
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;
    // Set mode of pin as alternate function (mode 10)
    GPIOA->MODER &= ~GPIO_MODER_MODE5;
    GPIOA->MODER |= GPIO_MODER_MODE5_1;
    // Set alternate function 3 (011) for PA5 (TIM8_CH1N)
    GPIOA->AFR[0] &= ~GPIO_AFRL_AFSEL5;
    GPIOA->AFR[0] |= GPIO_AFRL_AFSEL5_1 | GPIO_AFRL_AFSEL5_0;
    // Set output speed of pin as low by clearing speed bits
    GPIOA->OSPEEDR &= ~GPIO_OSPEEDR_OSPEED5;
    // Set pin as no pull-up, no pull-down
    GPIOA->PUPDR &= ~GPIO_PUPDR_PUPD5;
}

void User_Button1_Init(void) {
    // Enable the clock to GPIO port C
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;
    // Set pin as digital input by clearing mode bits (also sets as input)
    GPIOC->MODER &= ~GPIO_MODER_MODE13;
    // Set pin as no pull-up, no pull-down
    GPIOC->PUPDR &= ~GPIO_PUPDR_PUPD13;
    
    /**** EXTI 13 Configuration ****/
    // Enable SYSCFG clock
    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
    // Select PC.13 as the trigger source for EXTI 13
    SYSCFG->EXTICR[3] &= ~SYSCFG_EXTICR4_EXTI13;
    SYSCFG->EXTICR[3] |= SYSCFG_EXTICR4_EXTI13_PC;
    // Enable falling edge trigger for EXTI 13
    EXTI->FTSR1 |= EXTI_FTSR1_FT13;
    // Disable rising edge trigger for EXTI 13
    EXTI->RTSR1 &= ~EXTI_RTSR1_RT13;
    // Enable interrupt for EXTI 13, Interrupt Mask Register, enable line 13
    EXTI->IMR1 |= EXTI_IMR1_IM13;
    // Set EXTI 13 to priority 1 (same line as lines 10-15)
    NVIC_SetPriority(EXTI15_10_IRQn, 1);
    // Enable EXTI 13 interrupt
    NVIC_EnableIRQ(EXTI15_10_IRQn);
}

void TIM8_CH1_Init(void) {
    // Enable TIM8 clock
    RCC->APB2ENR |= RCC_APB2ENR_TIM8EN;
    // Set count direction as up-counting: 0 = up-counting, 1 = down-counting
    TIM8->CR1 &= ~TIM_CR1_DIR;
    // Clock prescalar (16 bit value, max 65,535)
    TIM8->PSC = 40000 - 1;
    // Auto-realod value, for up counting goes from 0->ARR
    TIM8->ARR = 1000 - 1;
    // Capture/compare register can be any value 0 < CCR < ARR
    TIM8->CCR1 = 500;
    // Main output enable (MOE): 0 = Disable, 1 = Enable
    TIM8->BDTR |= TIM_BDTR_MOE;
    // Clear output compare mode bits of channel 1
    TIM8->CCMR1 &= ~TIM_CCMR1_OC1M;
    // Select toggle mode (0011)
    TIM8->CCMR1 |= TIM_CCMR1_OC1M_0 | TIM_CCMR1_OC1M_1;
    // Select output polarity: 0 = active high, 1 = active low
    TIM8->CCER &= ~TIM_CCER_CC1NP;
    // Enable output for channel 1 complementary output
    TIM8->CCER |= TIM_CCER_CC1NE;
    // Initially have TIM8 disabled
    TIM8->CR1 &= ~TIM_CR1_CEN;
}

void EXTI15_10_IRQHandler(void) {
    // Check for the EXTI 13 interrupt flag
    if ((EXTI->PR1 & EXTI_PR1_PIF13) == EXTI_PR1_PIF13) {
        // Toggle TIM8
        TIM8->CR1 ^= TIM_CR1_CEN;
        // Clear interrupt pending request by writing 1
        EXTI->PR1 |= EXTI_PR1_PIF13;
    }
}
