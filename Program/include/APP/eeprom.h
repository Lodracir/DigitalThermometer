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
 * Write Data to EEPROM
 **/
typedef struct
{

    /** Unsigned Data **/
    void    (*U8BIT)(SPI_HandleTypeDef *hspi, uint8_t addr, uint8_t data);
    void    (*U16BIT)(SPI_HandleTypeDef *hspi, uint8_t addr, uint16_t data);
    void    (*U32BIT)(SPI_HandleTypeDef *hspi, uint8_t addr, uint32_t data);
    void    (*U64BIT)(SPI_HandleTypeDef *hspi, uint8_t addr, uint64_t data);

    /** Signed Data **/
    void    (*S8BIT)(SPI_HandleTypeDef *hspi, uint8_t addr, int8_t data);
    void    (*S16BIT)(SPI_HandleTypeDef *hspi, uint8_t addr, int16_t data);
    void    (*S32BIT)(SPI_HandleTypeDef *hspi, uint8_t addr, int32_t data);
    void    (*S64BIT)(SPI_HandleTypeDef *hspi, uint8_t addr, int64_t data);

    /** Float and Double Data **/
    void    (*FloatData)(SPI_HandleTypeDef *hspi, uint8_t addr, float data);
    void    (*DoubleData)(SPI_HandleTypeDef *hspi, uint8_t addr, double data);

}EEPROM_Write_t;

/**
 * Read Data to EEPROM
 **/
typedef struct
{

    /** Unsigned Data **/
    void    (*U8BIT)(SPI_HandleTypeDef *hspi, uint8_t addr, uint8_t *data);
    void    (*U16BIT)(SPI_HandleTypeDef *hspi, uint8_t addr,uint16_t *data);
    void    (*U32BIT)(SPI_HandleTypeDef *hspi, uint8_t addr,uint32_t *data);
    void    (*U64BIT)(SPI_HandleTypeDef *hspi, uint8_t addr,uint64_t *data);

    /** Signed Data **/
    void    (*S8BIT)(SPI_HandleTypeDef *hspi, uint8_t addr, int8_t *data);
    void    (*S16BIT)(SPI_HandleTypeDef *hspi, uint8_t addr, int16_t *data);
    void    (*S32BIT)(SPI_HandleTypeDef *hspi, uint8_t addr, int32_t *data);
    void    (*S64BIT)(SPI_HandleTypeDef *hspi, uint8_t addr, int64_t *data);

    /** Float and Double Data **/
    void    (*FloatData)(SPI_HandleTypeDef *hspi, uint8_t addr, float *data);
    void    (*DoubleData)(SPI_HandleTypeDef *hspi, uint8_t addr, double *data);

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
