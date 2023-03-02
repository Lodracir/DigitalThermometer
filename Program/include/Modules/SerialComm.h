//
// Created by resca on 27/10/2022.
//

#ifndef PROGRAM_SERIALCOMM_H
#define PROGRAM_SERIALCOMM_H

/****************************************************************
 *                   Required Headers                           *
 ****************************************************************/

//ANSI C
#include <stdio.h>
#include <stdbool.h>

//MCU 
#include "MCU/DRV_UART.h"

/****************************************************************
 *                          Defines                             *
 ****************************************************************/

#define SERIAL_UART_TX_BUFFER_SIZE  512  
#define SERIAL_UART_RX_BUFFER_SIZE  512

#define SERIAL_COMM_BAUDRATE 115200

/****************************************************************
 *                   Typedef enumeration                        *
 ****************************************************************/

typedef enum
{
    SERIAL_ERROR_NO = 0,
    SERIAL_ERROR_NO_INIT,
    SERIAL_ERROR_ALREADY_INIT,
    SERIAL_ERROR_UART,

    SERIAL_ERROR_TOTAL
}Serial_err_t;

/****************************************************************
 *                   Typedef structures                         *
 ****************************************************************/

typedef struct 
{
    USART_TypeDef   *Instance;
    uint32_t        Baudrate;

}SerialConfig_t;

/****************************************************************
 *                   Prototype Functions                        *
 ****************************************************************/

//New Functions
Serial_err_t SerialComm_Init(SerialConfig_t *Config);
Serial_err_t SerialComm_DeInit(void);

Serial_err_t SerialComm_Print( const char *pString );

Serial_err_t SerialComm_Transmit(uint8_t *pData, uint16_t Size);
Serial_err_t SerialComm_Receive(uint8_t *pData, uint16_t Size);

#endif //PROGRAM_SERIALCOMM_H
