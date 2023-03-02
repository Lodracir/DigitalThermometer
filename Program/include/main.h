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

/* Include MCU Drivers */
#include "MCU_Drivers/DRV_MCU.h"

/* App Drivers Include */
#include "APP/value.h"
#include "APP/statistics.h"
#include "APP/APP_STATE_MACHINE.h"
#include "APP/Memory_Map_EEPROM.h"
#include "APP/HDC2010.h"
#include "APP/eeprom.h"

#include "AppMain.h"

/** Modules Include **/
#include "Modules/SerialComm.h"



#endif //PROGRAM_MAIN_H
