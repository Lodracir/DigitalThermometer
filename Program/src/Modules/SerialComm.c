/****************************************************************
 *                   Required Headers                           *
 ****************************************************************/
#include "Modules/SerialComm.h"

/****************************************************************
 *                   Global Variables                           *
 ****************************************************************/
Uart_t huart2;
Serial_t Serial;

/****************************************************************
 *                   Static Variables                           *
 ****************************************************************/
static uint8_t LnChar = '\n';
static uint8_t CrChar = '\r';

/****************************************************************
 *               Static Prototype Functions                     *
 ****************************************************************/
 static void Serial_Print( const char *pString );
 static void Serial_PrintLn( const char *pString );
 static void Serial_Transmit( uint8_t *pData, uint16_t Size );
 static void Serial_Receive( uint8_t *pData, uint16_t Size );

/****************************************************************
*                     Public Functions                          *
****************************************************************/

/**
 *
 * @param Uart
 * @param UartConfig
 * @return
 **/
void SerialComm_Init(void)
{
    Serial.Print    = Serial_Print;
    Serial.PrintLn  = Serial_PrintLn;
    Serial.Transmit = Serial_Transmit;
    Serial.Receive  = Serial_Receive;
}

/**
 *
 * @param Uart
 * @param UartConfig
 * @return
 **/
void SerialComm_DeInit(void)
{
    Serial.Print    = NULL;
    Serial.PrintLn  = NULL;
    Serial.Transmit = NULL;
    Serial.Receive  = NULL;
}

/****************************************************************
 *                      Static Functions                        *
 ****************************************************************/

static void Serial_Print( const char *pString )
{
    while( (*pString) != '\0' )
    {
        DRV_UART_Transmit( &huart2, (uint8_t *)pString, 1 );
        pString++;
    }
}

static void Serial_PrintLn( const char *pString )
{
    Serial_Print( pString );
    DRV_UART_Transmit( &huart2, &CrChar, 1 );
    DRV_UART_Transmit( &huart2, &LnChar, 1 );
}

static void Serial_Transmit( uint8_t *pData, uint16_t Size )
{
    DRV_UART_Transmit( &huart2, pData, Size );
}

static void Serial_Receive( uint8_t *pData, uint16_t Size )
{
    DRV_UART_Receive( &huart2, pData, Size );
}