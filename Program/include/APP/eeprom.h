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

/**
 * Write Data to EEPROM
 **/
typedef struct
{

    /** Unsigned Data **/
    void    (*D8BIT)(I2C_HandleTypeDef *hi2c, MEM_BLOCKADDR_t AddrBlock, uint8_t addr, uint8_t data);
    void    (*D16BIT)(I2C_HandleTypeDef *hi2c, MEM_BLOCKADDR_t AddrBlock, uint8_t addr, uint16_t data);
    void    (*D32BIT)(I2C_HandleTypeDef *hi2c, MEM_BLOCKADDR_t AddrBlock, uint8_t addr, uint32_t data);
    void    (*D64BIT)(I2C_HandleTypeDef *hi2c, MEM_BLOCKADDR_t AddrBlock, uint8_t addr, uint64_t data);

    /** Float and Double Data **/
    void    (*FloatData)(I2C_HandleTypeDef *hi2c, MEM_BLOCKADDR_t AddrBlock, uint8_t addr, float data);
    void    (*DoubleData)(I2C_HandleTypeDef *hi2c, MEM_BLOCKADDR_t AddrBlock, uint8_t addr, double data);

}EEPROM_Write_t;

/**
 * Read Data to EEPROM
 **/
typedef struct
{

    /** Unsigned Data **/
    void    (*D8BIT)(I2C_HandleTypeDef *hi2c, MEM_BLOCKADDR_t AddrBlock, uint8_t addr, uint8_t *data);
    void    (*D16BIT)(I2C_HandleTypeDef *hi2c, MEM_BLOCKADDR_t AddrBlock, uint8_t addr,uint16_t *data);
    void    (*D32BIT)(I2C_HandleTypeDef *hi2c, MEM_BLOCKADDR_t AddrBlock, uint8_t addr,uint32_t *data);
    void    (*D64BIT)(I2C_HandleTypeDef *hi2c, MEM_BLOCKADDR_t AddrBlock, uint8_t addr,uint64_t *data);

    /** Float and Double Data **/
    void    (*FloatData)(I2C_HandleTypeDef *hi2c, MEM_BLOCKADDR_t AddrBlock, uint8_t addr, float *data);
    void    (*DoubleData)(I2C_HandleTypeDef *hi2c, MEM_BLOCKADDR_t AddrBlock, uint8_t addr, double *data);

}EEPROM_Read_t;

/**
 * EEPROM Functions Structure
 **/
typedef struct
{

    EEPROM_Write_t  write;
    EEPROM_Read_t   read;

}EEPROM_t;

/** Prototype Functions **/
void EEPROM_Init(EEPROM_t *heeprom);
void EEPROM_DeInit(EEPROM_t *heeprom);

#endif //PROGRAM_EEPROM_H
