/** TIM2 Driver Include **/
#include "MCU_Drivers/DRV_TIM2.h"
#include "APP/APP_STATE_MACHINE.h"
#include <stdbool.h>

/** TIM2 Handle Typedef **/
TIM_HandleTypeDef htim2;

/** Local variables **/
static uint8_t count = 0;
volatile bool MeasureFLAG = false;
volatile extern APP_UML_t APPStateMachine;

/****************************************************************
 *                                                              *
 *                          Functions                           *
 *                                                              *
 ****************************************************************/

void DRV_TIM2_Init(void)
{

    /** TIM2 Clock Init **/
    __HAL_RCC_TIM2_CLK_ENABLE();

    /** Configure TIM2 **/
    htim2.Instance                  = TIM2;
    htim2.Init.ClockDivision        = TIM_CLOCKDIVISION_DIV1;
    htim2.Init.Prescaler            = 800 - 1;
    htim2.Init.Period               = 10000 - 1;
    htim2.Init.CounterMode          = TIM_COUNTERMODE_UP;
    htim2.Init.AutoReloadPreload    = TIM_AUTORELOAD_PRELOAD_DISABLE;

    /** Init TIM2 **/
    HAL_TIM_Base_Init(&htim2);

    /** Configure TIM2 Interrupt **/
    HAL_NVIC_SetPriority( TIM2_IRQn, 0, 0 );
    HAL_NVIC_EnableIRQ(TIM2_IRQn);

}

/****************************************************************
 *                                                              *
 *                          Functions                           *
 *                                                              *
 ****************************************************************/

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{

    //GPIOB->ODR ^= (1U << 3);
    count++;

    if( (count == 60) )
    {
        APPStateMachine = START_MEASUREMENT;
        count = 0;
    }


}