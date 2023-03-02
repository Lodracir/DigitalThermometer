/****************************************************************
 *                                                              *
 *                     Required Includes                        *
 *                                                              *
 ****************************************************************/

//Modules
#include "Modules/SerialComm.h"

/****************************************************************
 *                                                              *
 *                  Static Typedef struct                       *
 *                                                              *
 ****************************************************************/

typedef struct 
{
    //Flags
    bool    Init;

    //UART Configuration Structure
    Uart_t  Uart;

}Serial_t;

typedef struct 
{
    uint8_t TX[SERIAL_UART_TX_BUFFER_SIZE];
    uint8_t RX[SERIAL_UART_RX_BUFFER_SIZE];

}SerialBuffer_t;


/****************************************************************
 *                                                              *
 *                     Local Variables                          *
 *                                                              *
 ****************************************************************/

//Serial Buffers
static SerialBuffer_t SerialBuffer = {
    .TX = {0},
    .RX = {0}
};

//Char
static uint8_t LnChar = '\n';
static uint8_t CrChar = '\r';

//Serial Structure
static Serial_t Serial = {
    //Flags
    .Init = false,

};

/****************************************************************
*                                                               *
*                     Public Functions                          *
*                                                               *
****************************************************************/

Serial_err_t SerialComm_Init(SerialConfig_t *Config)
{
    //Local variables
    UartConfig_t UartConfig;

    if(Serial.Init == true)
    {
        return SERIAL_ERROR_ALREADY_INIT;
    }
    else
    {
        //Configure UART
        UartConfig.SerialPort = Config->Instance;
        UartConfig.Baudrate   = Config->Baudrate;

        //Configure default values
        UartConfig.Mode         = UART_MODE_TX_RX;
        UartConfig.StopBits     = UART_STOPBITS_1;
        UartConfig.Parity       = UART_PARITY_NONE;
        UartConfig.HwFlowCtl    = UART_HWCONTROL_NONE;
        UartConfig.Oversampling = UART_OVERSAMPLING_16;
        UartConfig.ISR.Enable   = UART_ISR_DISABLE;
        UartConfig.TimeOut      = 1000;

        //Configure Buffer TODO: UNDER DEVELOPMENT
       

        //Configure UART
        if( DRV_UART_Init(&Serial.Uart, &UartConfig) != UART_OK )
        {
            return SERIAL_ERROR_UART;
        }
    }

    Serial.Init = true;
    return SERIAL_ERROR_NO;
}

Serial_err_t SerialComm_DeInit(void)
{
    if(Serial.Init == false)
    {
        return SERIAL_ERROR_ALREADY_INIT;
    }
    else
    {
        //Disable UART
        if( DRV_UART_DeInit(&Serial.Uart) != UART_OK )
        {
            return SERIAL_ERROR_UART;
        }
    }

    Serial.Init = false;
    return SERIAL_ERROR_NO;
}

Serial_err_t SerialComm_Print( const char *pString )
{
    if( Serial.Init == false )
    {
        return SERIAL_ERROR_NO_INIT;
    }
    else
    {
        while( (*pString) != '\0' )
        {
            DRV_UART_Transmit( &Serial.Uart, (uint8_t *)pString, 1 );
            pString++;
        }

        DRV_UART_Transmit( &Serial.Uart, &CrChar, 1 );
        DRV_UART_Transmit( &Serial.Uart, &LnChar, 1 );
    }

    return SERIAL_ERROR_NO;
}

Serial_err_t SerialComm_Transmit(uint8_t *pData, uint16_t Size)
{
    if( Serial.Init == false )
    {
        return SERIAL_ERROR_NO_INIT;
    }
    else
    {
        DRV_UART_Transmit( &Serial.Uart, pData, Size );
    }

    return SERIAL_ERROR_NO;
}

Serial_err_t SerialComm_Receive(uint8_t *pData, uint16_t Size)
{
    if( Serial.Init == false )
    {
        return SERIAL_ERROR_NO_INIT;
    }
    else
    {
        DRV_UART_Receive( &Serial.Uart, pData, Size );
    }

    return SERIAL_ERROR_NO;
}