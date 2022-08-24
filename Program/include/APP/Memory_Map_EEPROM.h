#ifndef PROGRAM_MEMORY_MAP_EEPROM_H
#define PROGRAM_MEMORY_MAP_EEPROM_H

/** ANSI C Headers **/
#include <stdio.h>
#include <stdint.h>

/** EEPROM MAPING **/

// Sensor Information
#define DevMnfr_MemAddr 0x10
#define DevID_MemAddr   0x12    // (DevMnfr_MemAddr + 2)

/**
 * Values Mapping
 **/

// Temperature Value
#define TEMP_AVERAGE_ADDR
#define TEMP_MAX_ADDR
#define TEMP_MIN_ADDR

// Temperature Value
#define HUM_AVERAGE_ADDR
#define HUM_MAX_ADDR
#define HUM_MIN_ADDR

#endif //PROGRAM_MEMORY_MAP_EEPROM_H
