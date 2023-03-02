/** Include Main Header **/
#include "main.h"

/** Global Variables **/


/** Prototype Functions **/

int main()
{
    /** Init HAL Driver **/
    HAL_Init();

    /** Init MCU Peripherals */
    MCU_DRV_Init();

    /** Set PB3 Low **/
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_SET);

    while(1)
    {
        

    }

    return 0;
}
