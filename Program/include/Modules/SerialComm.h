//
// Created by resca on 27/10/2022.
//

#ifndef PROGRAM_SERIALCOMM_H
#define PROGRAM_SERIALCOMM_H

/****************************************************************
 *                   Required Headers                           *
 ****************************************************************/
#include "MCU_Drivers/DRV_UART.h"

/****************************************************************
 *                   Typedef structures                         *
 ****************************************************************/

typedef struct
{
    void    (*Print)( const char *pString );
    void    (*PrintLn)( const char *pString );
    void    (*Transmit)( uint8_t *pData, uint16_t Size );
    void    (*Receive)( uint8_t *pData, uint16_t Size );
}Serial_t;

/****************************************************************
 *                   Prototype Functions                        *
 ****************************************************************/
void SerialComm_Init(void);
void SerialComm_DeInit(void);

/****************************************************************
 *                   Typedef structures                         *
 ****************************************************************/
extern Serial_t Serial;

#endif //PROGRAM_SERIALCOMM_H
