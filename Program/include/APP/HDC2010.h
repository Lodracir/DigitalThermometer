#ifndef PROGRAM_HDC2010_H
#define PROGRAM_HDC2010_H

/** Include STM32 Hal Driver **/
#include "stm32f3xx_hal.h"

/** ANSI C Headers **/
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

/** HDC2010 Defines **/
#define HDC2010_ADDR			(0x41 << 1) //0100 0001 -> 0x41
#define HDC2010_ADDR_PIN		GPIO_PIN_12
#define HDC2010_ADDR_PORT		GPIOA
#define HDC2010_RDYINT_PIN		GPIO_PIN_11
#define HDC2010_RDYINT_PORT		GPIOA

/** HDC2010 Memory Values **/
#define HDC2010_DEVID_LOW		0xFE
#define HDC2010_DEVID_HIGH		0xFF
#define HDC2010_MNFRID_LOW		0xFD
#define HDC2010_MNFRID_HIGH		0xFC
#define HDC2010_TEMPREAD_LOW	0x00
#define HDC2010_TEMPREAD_HIGH	0x01
#define HDC2010_HUMREAD_LOW		0x02
#define HDC2010_HUMREAD_HIGH	0x03
#define HDC2010_MEASURE_CONF	0x0F
#define HDC2010_RSTRDYINT_CONF	0x0E

/** HDC2010 Command Values **/
#define HDC2010_MEASURE_START	0x01
#define HDC2010_TRIGGONDEMAND	0x00

/**
 * HDC2010 Device Information Structure
 **/
typedef struct
{

    uint16_t Device;
    uint16_t Manufacturer;

}HDC2010_DeviceInfo_t;

/**
 * HDC2010 Measurement Information
 **/
typedef struct
{
    float       value;
    uint16_t    bits;
}HDC2010_MeasuredValue_t;

/**
 * HDC2010 Sensor Values
 **/
typedef struct
{
    HDC2010_MeasuredValue_t Temp;
    HDC2010_MeasuredValue_t Hum;
}HDC2010_Values_t;

/**
 * HDC2010 Function Structure
 **/
typedef struct
{
    void    (*readInfo)(I2C_HandleTypeDef *hi2c, HDC2010_DeviceInfo_t *dev);
    void    (*pollMeasurement)(I2C_HandleTypeDef *hi2c, HDC2010_Values_t *var);

}HDC2010_t;

/** HDC2010 Prototype Functions **/
void HDC2010_Init(HDC2010_t *hsensor);
void HDC2010_DeInit(HDC2010_t *hsensor);


#endif //PROGRAM_HDC2010_H
