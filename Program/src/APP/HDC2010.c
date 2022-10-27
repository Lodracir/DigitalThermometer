/** HDC2010 Driver Include **/
#include "APP/HDC2010.h"
#include "MCU_Drivers/DRV_I2C1.h"

/** Conversion Factor Variables **/
const float temp_value = 165.00000f / 65536.00000f;
const float hum_value = 100.00000f / 65536.00000f;

/**
 * Static Prototype Functions
 **/
static void HDC2010_Write(uint8_t reg, uint8_t data);
static uint8_t HDC2010_Read( uint8_t reg );

/**
 * Functions
 **/
static void HDC2010_ReadInfo( HDC2010_DeviceInfo_t *dev );
static void HDC2010_PollMeasurement( void );
static uint16_t HDC2010_getTemperature( float *value );
static uint16_t HDC2010_getHumidity( float *value );

/****************************************************************
 *                                                              *
 *                          Functions                           *
 *                                                              *
 ****************************************************************/

/**
 * @Name;
 * @brief:
 * @values:
 * @return:
 **/
void HDC2010_Init(HDC2010_t *hsensor)
{

    /** Allocate Functions **/
    hsensor->readInfo           = HDC2010_ReadInfo;
    hsensor->pollMeasurement    = HDC2010_PollMeasurement;
    hsensor->getTemperature     = HDC2010_getTemperature;
    hsensor->getHumidity        = HDC2010_getHumidity;

}

/**
 * @Name;
 * @brief:
 * @values:
 * @return:
 **/
void HDC2010_DeInit(HDC2010_t *hsensor)
{

    /** Desallocate Functions **/
    hsensor->readInfo           = NULL;
    hsensor->pollMeasurement    = NULL;
    hsensor->getTemperature     = NULL;
    hsensor->getHumidity        = NULL;

}

/**
 * @Name;
 * @brief:
 * @values:
 * @return:
 **/
void HDC2010_ReadInfo( HDC2010_DeviceInfo_t *dev )
{

    /** Local Variables **/
    uint8_t ManufacturerID[2] = { 0x00 ,0x00 }, DeviceID[2] = { 0x00 ,0x00 };

    /** Read High and Low Manufacturer ID **/
    DRV_I2C1_Mem_ReadByte(HDC2010_ADDR, HDC2010_MNFRID_HIGH, &ManufacturerID[0]);
    DRV_I2C1_Mem_ReadByte(HDC2010_ADDR, HDC2010_MNFRID_HIGH, &ManufacturerID[1]);

    /** Read High and Low Device ID **/
    DRV_I2C1_Mem_ReadByte(HDC2010_ADDR, HDC2010_DEVID_HIGH, &DeviceID[0]);
    DRV_I2C1_Mem_ReadByte(HDC2010_ADDR, HDC2010_DEVID_LOW, &DeviceID[1]);

    /** Merge 8-bit buffers to a single 16-bit variable and store them **/
    dev->Manufacturer = (ManufacturerID[0] << 8) + ManufacturerID[1];
    dev->Device = (DeviceID[0] << 8) + DeviceID[1];

}

/**
 * @Name;
 * @brief:
 * @values:
 * @return:
 **/
void HDC2010_PollMeasurement( void )
{

    /** Trigger conversion **/
    HDC2010_Write(HDC2010_MEASURE_CONF, HDC2010_MEASURE_START);

}

/**
 * @Name;
 * @brief:
 * @values:
 * @return:
 **/
static uint16_t HDC2010_getTemperature( float *value )
{

    /** Local Variables **/
    uint8_t TempBuff[2] = { 0x00, 0x00 };
    uint16_t TempBits = 0;

    /** Read Sensor buffer to get Humidity Values **/
    TempBuff[0] = HDC2010_Read(HDC2010_TEMPREAD_HIGH);
    TempBuff[1] = HDC2010_Read(HDC2010_TEMPREAD_LOW);

    /** Merge Temperature bits value **/
    TempBits = (TempBuff[0] << 8) + (TempBuff[1]);

    /** Calculate Temperature value **/
    (*value) = ( ( (float)TempBits ) * (temp_value) ) - 40.0f;

    /** Return Temperature value bits **/
    return TempBits;

}

/**
 * @Name;
 * @brief:
 * @values:
 * @return:
 **/
static uint16_t HDC2010_getHumidity( float *value )
{

    /** Local Variables **/
    uint8_t HumBuff[2] = { 0x00, 0x00 };
    uint16_t HumBits = 0;

    /** Read Sensor buffer to get Humidity Values **/
    HumBuff[0] = HDC2010_Read(HDC2010_HUMREAD_HIGH);
    HumBuff[1] = HDC2010_Read(HDC2010_HUMREAD_LOW);

    /** Merge Humidity bits value **/
    HumBits = (HumBuff[0] << 8) + (HumBuff[1]);

    /** Calculate Humidity Value **/
    (*value) = (float)HumBits * hum_value;

    /** Return Humidity value bits **/
    return HumBits;

}

/****************************************************************
 *                                                              *
 *                     Static Functions                         *
 *                                                              *
 ****************************************************************/

/**
 * @Name;
 * @brief:
 * @values:
 * @return:
 **/
void HDC2010_Write(uint8_t reg, uint8_t value)
{

    /** Local Variables **/
    uint8_t data[2] = { 0x00, 0x00 };

    /** Assign Variables **/
    data[0] = reg;
    data[1] = value;

    /** Transmit data through I2C **/
    DRV_I2C1_Transmit( HDC2010_ADDR, data, sizeof(data) );

}

/**
 * @Name;
 * @brief:
 * @values:
 * @return:
 **/
uint8_t HDC2010_Read( uint8_t reg )
{

    /** Local Variable **/
    uint8_t DataValue = 0x00;

    /** Read Memory Value **/
    DRV_I2C1_Mem_ReadByte( HDC2010_ADDR, reg, &DataValue );

    return DataValue;
}

