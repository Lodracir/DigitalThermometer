#ifndef PROGRAM_APPMAIN_H
#define PROGRAM_APPMAIN_H

/****************************************************************
 *                                                              *
 *                     Required Includes                        *
 *                                                              *
 ****************************************************************/

//STM32 HAL
#include "stm32f3xx_hal.h"

//MCU
#include "MCU/DRV_MCU.h"

//Modules
#include "Modules/SerialComm.h"

/****************************************************************
 *                                                              *
 *                          Defines                             *
 *                                                              *
 ****************************************************************/

#define DIGITAL_TERMOMETER_VERSION  "0.1.0a"

/****************************************************************
 *                   Prototype Functions                        *
 ****************************************************************/
void AppInit(void);
void AppMain(void);

#endif //PROGRAM_APPMAIN_H
