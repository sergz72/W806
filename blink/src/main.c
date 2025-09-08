//
// Simple W806 Hello-blinky program
//
// Scott Beasley - 2022
//

// Copy these files to your wm-sdk-w806/app/src/ folder to compile.
// Run make from the wm-sdk-w806 root directory to build
// then make flash to load the W806 with the code.
// This example assume your wm-sdk-w806 folder is in your home directory:
// dumbuser@dumbox:~/wm-sdk-w806/make; make flash
//
#include <stdio.h>
#include "wm_hal.h"

static void setup(void);

int main (void)
{
    // Do our setup.
    setup ( );
    
    // This is equivalent to loop ()...
    while (true) {
       // Blink the 3 leds one at a time.
       // Middle first...
       HAL_GPIO_TogglePin (GPIOB, GPIO_PIN_1);
       HAL_Delay (1000);
       HAL_GPIO_TogglePin (GPIOB, GPIO_PIN_1);   
       HAL_Delay (1000);     

       // Top second...              
       HAL_GPIO_TogglePin (GPIOB, GPIO_PIN_2);
       HAL_Delay (1000);
       HAL_GPIO_TogglePin (GPIOB, GPIO_PIN_2);
       HAL_Delay (1000);

       // Bottom last...       
       HAL_GPIO_TogglePin (GPIOB, GPIO_PIN_0);
       HAL_Delay (1000);
       HAL_GPIO_TogglePin (GPIOB, GPIO_PIN_0);
       HAL_Delay (1000);       
    }
    
    return 0;
}

static void setup (void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    
    // Set and Configure the system clock
    SystemClock_Config (CPU_CLK_240M);

    // This function is used to init the HAL Library.
    // It must be called before any other HAL_ functions
    HAL_Init(); 

    __HAL_RCC_GPIO_CLK_ENABLE ( );

    GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init (GPIOB, &GPIO_InitStruct);
}
