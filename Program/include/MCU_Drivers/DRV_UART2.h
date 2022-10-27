#ifndef PROGRAM_DRV_UART2_H
#define PROGRAM_DRV_UART2_H

/* Include STM32 Hal Driver */
#include "stm32f3xx_hal.h"

/* ANSI C Headers */
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

/*  */
typedef struct
{
    void    (*Transmit)(uint8_t *pData, uint8_t size);
    void    (*Receive)(uint8_t *pData, uint8_t size);
}DRV_Serial_t;

/*  */
extern DRV_Serial_t Serial;

/* Prototype Functions */
void DRV_UART2_Init(void);
void DRV_UART2_DeInit(void);

#endif //PROGRAM_DRV_UART2_H
