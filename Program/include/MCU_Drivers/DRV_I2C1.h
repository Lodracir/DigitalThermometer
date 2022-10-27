#ifndef PROGRAM_DRV_I2C1_H
#define PROGRAM_DRV_I2C1_H

/* Include STM32 Hal Driver */
#include "stm32f3xx_hal.h"

/* ANSI C Headers */
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

/* Prototype Functions */
void DRV_I2C1_Init(void);

/** Memory Write/Read **/
void DRV_I2C1_Mem_WriteByte(uint16_t DevAddr, uint16_t MemAddr, uint8_t *pData);
void DRV_I2C1_Mem_ReadByte(uint16_t DevAddr, uint16_t MemAddr, uint8_t *pData);

/** Memory Transmit/Receive **/
void DRV_I2C1_Transmit(uint16_t DevAdd, uint8_t *pData, uint16_t DataSizer);
void DRV_I2C1_Receive(uint16_t DevAdd, uint8_t *pData, uint16_t DataSize);

#endif //PROGRAM_DRV_I2C1_H
