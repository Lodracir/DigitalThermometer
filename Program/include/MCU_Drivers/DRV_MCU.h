#ifndef PROGRAM_DRV_MCU_H
#define PROGRAM_DRV_MCU_H

/* Include STM32 HAL Driver */
#include "stm32f3xx_hal.h"

/* ANSI C Headers */
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

/* Include MCU Drivers */
#include "MCU_Drivers/DRV_GPIO.h"
#include "MCU_Drivers/DRV_UART2.h"
#include "MCU_Drivers/DRV_I2C1.h"
#include "MCU_Drivers/DRV_TIM2.h"

/* Prototype Functions */
void MCU_DRV_Init(void);

#endif //PROGRAM_DRV_MCU_H
