#ifndef PROGRAM_DRV_UART_H
#define PROGRAM_DRV_UART_H

/****************************************************************
 *                   Required Headers                           *
 ****************************************************************/
#include "stm32f3xx_hal.h"

/** ANSI C Headers **/
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

/****************************************************************
 *                           Defines                            *
 ****************************************************************/
#define UART_TX_BUFFER_SIZE 1024
#define UART_RX_BUFFER_SIZE 1024

/****************************************************************
 *                   Typedef Enumerations                       *
 ****************************************************************/

typedef enum
{
    UART_OK = 0,
    UART_ERROR
}UartStatus_t;

typedef enum
{
    UART_ISR_ENABLE = 0,
    UART_ISR_DISABLE
}Uart_ISR_enum_t;

/****************************************************************
 *                   Typedef Structures                         *
 ****************************************************************/

typedef struct
{
    Uart_ISR_enum_t Enable;
    uint8_t         Priority;
    uint8_t         Subpriority;
}Uart_ISR_t;

typedef struct
{
    USART_TypeDef   *SerialPort;
    uint32_t        Baudrate;
    uint32_t        Mode;
    uint32_t        WordLength;
    uint32_t        StopBits;
    uint32_t        Parity;
    Uart_ISR_t      ISR;
    uint32_t        HwFlowCtl;
    uint32_t        Oversampling;
    uint32_t        TimeOut;
}UartConfig_t;

typedef struct
{
    UART_HandleTypeDef  Handle;
    uint8_t             *TX_Buffer;
    uint8_t             *RX_Buffer;
    uint32_t            TimeOut;
}Uart_t;

/****************************************************************
 *                   Prototype Functions                        *
 ****************************************************************/
UartStatus_t DRV_UART_Init( Uart_t *Uart, UartConfig_t *UartConfig );
UartStatus_t DRV_UART_DeInit( Uart_t *Uart );

/** Polling UART Functions **/
UartStatus_t DRV_UART_Transmit( Uart_t *Uart, uint8_t *pData, uint32_t DataSize );
UartStatus_t DRV_UART_Receive( Uart_t *Uart, uint8_t *pData, uint32_t DataSize );

/** ISR UART Functions **/
UartStatus_t DRV_UART_TransmitISR( Uart_t *Uart, uint8_t *pData, uint32_t DataSize );
UartStatus_t DRV_UART_ReceiveISR( Uart_t *Uart, uint8_t *pData, uint32_t DataSize );

/** UART Print functions **/
UartStatus_t DRV_UART_Print( Uart_t *Uart, char *pString );
UartStatus_t DRV_UART_PrintLn( Uart_t *Uart, char *pString );

/** UART ISR Functions **/
void DRV_UART_InterruptHandler( USART_TypeDef *UARTx );

#endif //PROGRAM_DRV_UART_H
