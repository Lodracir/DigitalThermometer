#ifndef _DRV_I2C_H_
#define _DRV_I2C_H_

/* Include STM32 Hal Driver */
#include "stm32f3xx_hal.h"

/* ANSI C Headers */
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef enum
{
    I2C_OK = 0,
    I2C_ERROR
}I2CStatus_t;

/**
 * I2C Configure Structure
 */
typedef struct
{

    I2C_TypeDef     *Instance;
    uint32_t        Timing;
    uint32_t        OwnAddress1;
    uint32_t        AddressingMode;
    uint32_t        DualAddressMode;
    uint32_t        OwnAddress2;
    uint32_t        OwnAddress2Masks;
    uint32_t        GeneralCallMode;
    uint32_t        NoStretchMode;
    uint32_t        Timeout;

}I2C_Config_t;

typedef struct
{

    I2C_HandleTypeDef   I2C_Handle;
    uint32_t            Timeout;

}I2C_t;

/**
 * 
 * Prototype Functions
 * 
 **/

/** Init and DeInit Functions **/
I2CStatus_t DRV_I2C_Init( I2C_t *hi2c, I2C_Config_t *hi2c_cfg );
void DRV_I2C_DeInit( I2C_t *hi2c );

I2CStatus_t DRV_I2C_Mem_Write( I2C_t *hi2c, uint16_t DevAddr, uint16_t MemAddr );

#endif // _DRV_I2C_H