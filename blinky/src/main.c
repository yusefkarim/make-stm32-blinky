#include "init.h"

int main(void)
{
    System_Clock_80MHz_Init();
    LED2_Init();
    User_Button1_Init();
    TIM8_CH1_Init();

    while (1);
}
