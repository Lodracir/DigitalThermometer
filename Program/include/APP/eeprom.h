#ifndef PROGRAM_EEPROM_H
#define PROGRAM_EEPROM_H

/** Include STM32 Hal Driver **/
#include "stm32f3xx_hal.h"

/** ANSI C Headers **/
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

/**
 * Enum structures
 **/
 typedef enum
 {
     MEM_BLOCK_0,
     MEM_BLOCK_1
 }MEM_BLOCKADDR_t;

typedef enum
{

    D_UINT8 = 0,
    D_UINT16,
    D_UINT32,
    D_UINT64,
    D_FLOAT,
    D_DOUBLE

}Data_Type_t;

/**
 * EEPROM Functions Structure
 **/
typedef struct
{

    void    (*WriteData)( MEM_BLOCKADDR_t AddrBlock, uint8_t addr, void* pData, Data_Type_t DataType );
    void    (*ReadData)( MEM_BLOCKADDR_t AddrBlock, uint8_t addr, void* pData, Data_Type_t DataType );

}EEPROM_t;

/** 
 * Prototype Functions 
 **/
void EEPROM_Init(EEPROM_t *heeprom);
void EEPROM_DeInit(EEPROM_t *heeprom);

#endif //PROGRAM_EEPROM_H
