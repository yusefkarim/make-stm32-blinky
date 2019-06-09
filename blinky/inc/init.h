/* Setup the System Clock as 80 MHz through the PLL and HSI. */
void System_Clock_80MHz_Init(void);

/* Setup the on-baord LED, LD2 for the Nucleo board (PA5).
 * Uses alternate function 3, corresponding to TIM8_CH1N. */
void LED2_Init(void);

/* Setup the on-board button, B1 for the Nucleo board (PC13)
 * Uses EXTI 13 for falling edge trigger interrupts. */
void User_Button1_Init(void);

/* Use TIM8 in output compare mode to toggle the PA5 every 500 ms, using:
 * f_TIM8 = F_sys / (Prescalar + 1) = 80 MHz / (39999 + 1) = 2000 Hz = 2 kHz
 * PA5 Toggle Rate = ARR / f_TIM8 = 1000 / 2000 = 0.5 sec = 500 ms */
void TIM8_CH1_Init(void);

/* External Interrupt line 13 Interrupt Request Handler used for PC13.
 * Toggles TIM8_CH1N */
void EXTI15_10_IRQHandler(void);
