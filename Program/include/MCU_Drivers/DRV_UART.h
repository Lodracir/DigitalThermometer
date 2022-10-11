//
// Created by resca on 10/10/2022.
//

#ifndef PROGRAM_DRV_UART_H
#define PROGRAM_DRV_UART_H

/*****************************************************************
 *
 *  Required Libraries
 *
 *****************************************************************/

/** Include STM32 Hal Driver **/
#include "stm32f3xx_hal.h"

/** ANSI C Headers **/
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

/*****************************************************************
 *
 *  Defines
 *
 *****************************************************************/

/** **/
#define _1byte  1
#define _2byte  2
#define _3byte  3

/** **/
#define _100mS  100
#define _200mS  200
#define _500mS  500

/*****************************************************************
 *
 *  Typedef enumerations
 *
 *****************************************************************/

/** UART Return code **/
typedef enum
{
    UART_OK = 0,
    UART_ERROR

}UartStatus_t;

/** UART Polling/Interrupt mode **/
typedef enum
{
    UART_POLLING_MODE = 0,
    UART_INTERRUPT_MODE,
    UART_DMA_MODE

}UartMode_t;

/*****************************************************************
 *
 *  Typedef structures
 *
 *****************************************************************/

/** UART Configuration structure **/
typedef struct
{
    USART_TypeDef   *SerialPort;
    uint32_t        Baudrate;
    uint32_t        TransmitMode;
    uint32_t        WordLength;
    uint32_t        StopBits;
    uint32_t        Parity;
    UartMode_t      Mode;
    uint32_t        HwFlowCtl;
    uint32_t        TimeOut;

}UartConfig_t;

/** UART Structure **/
typedef struct
{

    /** Structure variables **/
    UART_HandleTypeDef  UartInstance;
    uint32_t            TimeOut;

    /** Proposed Callback Functions **/
    UartStatus_t (*Transmit)( uint8_t *pData, uint32_t DataSize );
    UartStatus_t (*Receive)( uint8_t *pData, uint32_t DataSize);

}Uart_t;

/*****************************************************************
 *
 *  Prototype Functions
 *
 *****************************************************************/

/** Init and DeInit functions **/
UartStatus_t DRV_UART_Init( Uart_t *Uart, UartConfig_t *UartConfig );
void DRV_UART_DeInit( Uart_t *Uart );

/** MSP Init Functions **/
void DRV_UART1_MspInit( void );
void DRV_UART2_MspInit( void );

/** MSP DeInit Functions **/
void DRV_UART1_MspDeInit( void );
void DRV_UART2_MspDeInit( void );

/** Polling UART Functions **/
UartStatus_t DRV_UART_Transmit( Uart_t *Uart, uint8_t *pData, uint32_t DataSize );
UartStatus_t DRV_UART_Receive( Uart_t *Uart, uint8_t *pData, uint32_t DataSize );

/** ISR UART Functions **/
UartStatus_t DRV_UART_TransmitISR( Uart_t *Uart, uint8_t *pData, uint32_t DataSize );
UartStatus_t DRV_UART_ReceiveISR( Uart_t *Uart, uint8_t *pData, uint32_t DataSize );

/** UART Print functions **/
UartStatus_t DRV_UART_Print( Uart_t *Uart, char *pString );
UartStatus_t DRV_UART_PrintLn( Uart_t *Uart, char *pString );

#endif //PROGRAM_DRV_UART_H
