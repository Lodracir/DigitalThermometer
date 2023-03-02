/* I2C1 Driver Include */
#include "MCU/DRV_I2C1.h"

/* I2C1 Handle structure */
I2C_HandleTypeDef hi2c1;

/**
 * Definitions
 **/
#define _1Byte  1
#define _100mS  100

/****************************************************************
 *                                                              *
 *                          Functions                           *
 *                                                              *
 ****************************************************************/

void DRV_I2C1_Init(void)
{

    // Configure I2C1
    hi2c1.Instance              = I2C1;
    hi2c1.Init.Timing           = 0x2000090E;
    hi2c1.Init.OwnAddress1      = 0;
    hi2c1.Init.AddressingMode   = I2C_ADDRESSINGMODE_7BIT;
    hi2c1.Init.DualAddressMode  = I2C_DUALADDRESS_DISABLE;
    hi2c1.Init.OwnAddress2      = 0;
    hi2c1.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
    hi2c1.Init.GeneralCallMode  = I2C_GENERALCALL_DISABLE;
    hi2c1.Init.NoStretchMode    = I2C_NOSTRETCH_DISABLE;
    HAL_I2C_Init(&hi2c1);

    // Configure Analogue filter
    HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE);

    // Configure Digital filter
    HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0);

}

void DRV_I2C1_Mem_WriteByte(uint16_t DevAddr, uint16_t MemAddr, uint8_t *pData)
{

    HAL_I2C_Mem_Write(&hi2c1, DevAddr, MemAddr, _1Byte, pData, _1Byte, _100mS);

}

void DRV_I2C1_Mem_ReadByte(uint16_t DevAddr, uint16_t MemAddr, uint8_t *pData)
{

    HAL_I2C_Mem_Read(&hi2c1, DevAddr, MemAddr, _1Byte, pData, _1Byte, _100mS);

}

void DRV_I2C1_Transmit(uint16_t DevAdd, uint8_t *pData, uint16_t DataSize)
{

    HAL_I2C_Master_Transmit(&hi2c1, DevAdd, pData, DataSize, _100mS);

}

void DRV_I2C1_Receive(uint16_t DevAdd, uint8_t *pData, uint16_t DataSize)
{

    HAL_I2C_Master_Receive(&hi2c1, DevAdd, pData, DataSize, _100mS);

}