
#include "wm_hal.h"

// See below for explanation. 
#define readl(addr) ({unsigned int __v = (*(volatile unsigned int *) (addr)); __v;})

/* SystemClock_Config() requires this handler, do not forget to include */
__attribute__((isr)) void CORET_IRQHandler(void)
{
    // Scope the SysTick system timer peripheral. 
    // See: https://developer.arm.com/documentation/dui0497/a/cortex-m0-peripherals/about-the-cortex-m0-peripherals
    readl (0xE000E010);

    HAL_IncTick ( ); // This function is called to increment a global variable "uwTick" used as application time base. 
}

