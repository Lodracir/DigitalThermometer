/* MCU Driver Header */
#include "MCU_Drivers/DRV_MCU.h"


/****************************************************************
 *                                                              *
 *                          Functions                           *
 *                                                              *
 ****************************************************************/

/*
 *
 *
 */
void MCU_DRV_Init(void)
{
    // MCU Driver Inits
    DRV_GPIO_Init();
    DRV_UART2_Init();
    DRV_I2C1_Init();
    DRV_TIM2_Init();
}
