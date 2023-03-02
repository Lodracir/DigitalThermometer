#ifndef PROGRAM_MAIN_H
#define PROGRAM_MAIN_H

/****************************************************************
 *                                                              *
 *                     Required Includes                        *
 *                                                              *
 ****************************************************************/

//MCU
#include "stm32f3xx_hal.h"

// ANSI C Headers
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Include MCU Drivers 
#include "MCU/DRV_MCU.h"

// App Drivers Include 
#include "AppMain.h"

//Common Include
#include "Common/CircularBuffer.h"

/** Modules Include **/
#include "Modules/SerialComm.h"



#endif //PROGRAM_MAIN_H
