/* HDC2010 Driver Include */
#include "APP/HDC2010.h"

/** Static Prototype Functions **/
static void HDC2010_Write(I2C_HandleTypeDef *hi2c ,uint8_t reg, uint8_t data);
static uint8_t HDC2010_Read(I2C_HandleTypeDef *hi2c, uint8_t reg);
static void HDC2010_ReadInfo(I2C_HandleTypeDef *hi2c, HDC2010_DeviceInfo_t *dev);
static void HDC2010_PollMeasurement(I2C_HandleTypeDef *hi2c, HDC2010_Values_t *var);

/** Conversion Factor Variables **/
const float temp_value = 165.00000f / 65536.00000f;
const float hum_value = 100.00000f / 65536.00000f;

/****************************************************************
 *                                                              *
 *                          Functions                           *
 *                                                              *
 ****************************************************************/


/*
 *
 *
 *
 */
void HDC2010_Init(HDC2010_t *hsensor)
{

    // Allocate Functions
    hsensor->readInfo           = HDC2010_ReadInfo;
    hsensor->pollMeasurement    = HDC2010_PollMeasurement;

}


/*
 *
 *
 *
 */
void HDC2010_DeInit(HDC2010_t *hsensor)
{

    // Desallocate Functions
    hsensor->readInfo           = NULL;
    hsensor->pollMeasurement    = NULL;

}

/****************************************************************
 *                                                              *
 *                     Static Functions                         *
 *                                                              *
 ****************************************************************/


/*
 *
 *
 *
 */
void HDC2010_Write(I2C_HandleTypeDef *hi2c ,uint8_t reg, uint8_t value)
{

    /* Local Variables */
    uint8_t data[2] = { 0x00, 0x00 };

    /* Assign Variables */
    data[0] = reg;
    data[1] = value;

    /* Transmit data through I2C */
    HAL_I2C_Master_Transmit(hi2c, HDC2010_ADDR, data, 2, HAL_MAX_DELAY);

}


/*
 *
 *
 *
 */
uint8_t HDC2010_Read(I2C_HandleTypeDef *hi2c, uint8_t reg)
{

    /* Local Variable */
    uint8_t DataValue = 0x00;

    /* Read Memory Value */
    HAL_I2C_Mem_Read(hi2c, HDC2010_ADDR, reg, 1, &DataValue, 1, HAL_MAX_DELAY);

    return DataValue;
}


/*
 *
 *
 *
 */
static void HDC2010_ReadInfo(I2C_HandleTypeDef *hi2c, HDC2010_DeviceInfo_t *dev)
{

    /* Local Variables */
    uint8_t ManufacturerID[2] = { 0x00 ,0x00 }, DeviceID[2] = { 0x00 ,0x00 };

    /* Read High and Low Manufacturer ID */
    ManufacturerID[0] = HDC2010_Read(hi2c, HDC2010_MNFRID_HIGH);
    ManufacturerID[1] = HDC2010_Read(hi2c, HDC2010_MNFRID_LOW);

    /* Read High and Low Device ID */
    DeviceID[0] = HDC2010_Read(hi2c, HDC2010_DEVID_HIGH);
    DeviceID[1] = HDC2010_Read(hi2c, HDC2010_DEVID_LOW);

    /* Merge 8-bit buffers to a single 16-bit variable and store them*/
    dev->Manufacturer = (ManufacturerID[0] << 8) + ManufacturerID[1];
    dev->Device = (DeviceID[0] << 8) + DeviceID[1];

}


/*
 *
 *
 *
 */
static void HDC2010_PollMeasurement(I2C_HandleTypeDef *hi2c, HDC2010_Values_t *var)
{

    /* Local Variables */
    uint8_t TempBuff[2] = { 0x00, 0x00 }, HumBuff[2] = { 0x00, 0x00 };

    /* Trigger conversion */
    HDC2010_Write(hi2c, HDC2010_MEASURE_CONF, HDC2010_MEASURE_START);

    /* Delay 10 mS */
    HAL_Delay(10);

    /* Read Sensor buffer to get Temperature and Humidity Values */
    TempBuff[0] = HDC2010_Read(hi2c, HDC2010_TEMPREAD_HIGH);
    TempBuff[1] = HDC2010_Read(hi2c, HDC2010_TEMPREAD_LOW);

    HumBuff[0] = HDC2010_Read(hi2c, HDC2010_HUMREAD_HIGH);
    HumBuff[1] = HDC2010_Read(hi2c, HDC2010_HUMREAD_LOW);

    /* Merge Temperature and Humidity Values */
    var->Temp.bits  = (TempBuff[0] << 8) + (TempBuff[1]);
    var->Hum.bits   = (HumBuff[0] << 8) + (HumBuff[1]);

    /* Convert bits to float values (Temp and Hum) */
    var->Temp.value =   ( ( (float)var->Temp.bits ) * (temp_value) ) - 40.0f;
    var->Hum.value  =   (float)var->Hum.bits * hum_value;

}