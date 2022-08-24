#ifndef PROGRAM_MAIN_H
#define PROGRAM_MAIN_H

/* Include Librarie */
#include "stm32f3xx_hal.h"

/* ANSI C Headers */
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/* Defines and Macros */
#define BSP_LD3_Pin     GPIO_PIN_3
#define BSP_LD3_Port    GPIOB

/* Macros Functions (LD3) */
#define BSP_LD3_Toggle()            ( HAL_GPIO_TogglePin(BSP_LD3_Port, BSP_LD3_Pin) )
#define BSP_LD3_WritePin(pinState)  ( HAL_GPIO_WritePin(BSP_LD3_Port, BSP_LD3_Pin, pinState) )

/* Include MCU Drivers */
#include "MCU_Drivers/DRV_MCU.h"

/* App Drivers Include */
#include "APP/value.h"
#include "APP/Memory_Map_EEPROM.h"
#include "APP/HDC2010.h"


#endif //PROGRAM_MAIN_H
