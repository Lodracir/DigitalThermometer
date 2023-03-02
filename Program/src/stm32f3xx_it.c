/****************************************************************
 *                                                              *
 *                     Required Includes                        *
 *                                                              *
 ****************************************************************/
#include "stm32f3xx_hal.h"

/****************************************************************
 *                                                              *
 *                     Extern Variables                         *
 *                                                              *
 ****************************************************************/
extern TIM_HandleTypeDef htim2;

/****************************************************************
 *                                                              *
 *                     Interrupt Functions                      *
 *                                                              *
 ****************************************************************/

void SysTick_Handler(void)
{
   HAL_IncTick();
}

/****************************************************************
 *                                                              *
 *                     Interrupt Functions                      *
 *                                                              *
 ****************************************************************/

void TIM2_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&htim2);
}