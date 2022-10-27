#ifndef PROGRAM_APPMAIN_H
#define PROGRAM_APPMAIN_H

/****************************************************************
 *                   Required Headers                           *
 ****************************************************************/
#include "stm32f3xx_hal.h"
#include "MCU_Drivers/DRV_MCU.h"
#include "Modules/SerialComm.h"

/****************************************************************
 *                   Prototype Functions                        *
 ****************************************************************/
void AppInit(void);
void AppMain(void);

#endif //PROGRAM_APPMAIN_H
