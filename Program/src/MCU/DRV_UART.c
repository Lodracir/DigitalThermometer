/****************************************************************
 *                   Required Headers                           *
 ****************************************************************/
#include "MCU/DRV_UART.h"

/****************************************************************
 *               Local Typedef Enumerations                     *
 ****************************************************************/

/****************************************************************
 *                      Local Variables                         *
 ****************************************************************/
static IRQn_Type UARTISRTable[3] = { USART1_IRQn , USART2_IRQn , USART3_IRQn };

static uint8_t UART_TXBuffer[UART_TX_BUFFER_SIZE];
static uint8_t UART_RXBuffer[UART_RX_BUFFER_SIZE];

/****************************************************************
 *                Prototype Static Functions                    *
 ****************************************************************/
 void UART_InitClock( USART_TypeDef *Instance );
 void UART_DeInitClock( USART_TypeDef *Instance );
 void UART_EnableIRQ( USART_TypeDef *Instance, uint8_t Priority, uint8_t Subpriority );

/****************************************************************
 *                       Public Functions                       *
 ****************************************************************/

/**
 *
 * @param Uart
 * @param UartConfig
 * @return
 **/
UartStatus_t DRV_UART_Init( Uart_t *Uart, UartConfig_t *UartConfig )
{
    /** Config selected UART Instance **/
    Uart->Handle.Instance           = UartConfig->SerialPort;
    Uart->Handle.Init.BaudRate      = UartConfig->Baudrate;
    Uart->Handle.Init.WordLength    = UartConfig->WordLength;
    Uart->Handle.Init.StopBits      = UartConfig->StopBits;
    Uart->Handle.Init.Parity        = UartConfig->Parity;
    Uart->Handle.Init.Mode          = UartConfig->Mode;
    Uart->Handle.Init.HwFlowCtl     = UartConfig->HwFlowCtl;
    Uart->TimeOut                   = UartConfig->TimeOut;

    /** Default configuration **/
    Uart->Handle.Init.OverSampling     = UART_OVERSAMPLING_16;
    Uart->Handle.Init.OneBitSampling   = UART_ONE_BIT_SAMPLE_DISABLE;
    Uart->Handle.AdvancedInit.AdvFeatureInit   = UART_ADVFEATURE_NO_INIT;

    /** Enable UART Clock **/
    UART_InitClock( Uart->Handle.Instance );

    /** Init Selected UART instance **/
    if ( HAL_UART_Init( &Uart->Handle ) != HAL_OK )
    {
        return UART_ERROR;
    }

    /** If Interrupt is requested **/
    if( UartConfig->ISR.Enable == UART_ISR_ENABLE )
    {
        UART_EnableIRQ( UartConfig->SerialPort, UartConfig->ISR.Priority, UartConfig->ISR.Subpriority );
    }

    /** Clean UART TX RX Buffers **/
    memset(UART_TXBuffer, 0x00, UART_TX_BUFFER_SIZE);
    memset(UART_RXBuffer, 0x00, UART_RX_BUFFER_SIZE);

    /** Assign UART Structure pointers to buffers **/
    Uart->TX_Buffer = UART_TXBuffer;
    Uart->RX_Buffer = UART_RXBuffer;

    return UART_OK;
}

/**
 * @name
 * @input Uart
 * @param UartConfig
 * @return
 **/
UartStatus_t DRV_UART_DeInit( Uart_t *Uart )
{
    /** Disable UART Clock **/
    UART_DeInitClock( Uart->Handle.Instance );

    /** DeInit UARTx Instance **/
    HAL_UART_DeInit( &Uart->Handle );

    /** Clean UART TX RX Buffers **/
    memset(UART_TXBuffer, 0x00, UART_TX_BUFFER_SIZE);
    memset(UART_RXBuffer, 0x00, UART_RX_BUFFER_SIZE);

    /** Deallocate UART Structure pointers to buffers **/
    Uart->TX_Buffer = NULL;
    Uart->RX_Buffer = NULL;

    return UART_OK;
}

/**
 *
 * @param Uart
 * @param UartConfig
 * @return
 **/
UartStatus_t DRV_UART_Transmit( Uart_t *Uart, uint8_t *pData, uint32_t DataSize )
{
    if( HAL_UART_Transmit( & Uart->Handle, pData, DataSize, Uart->TimeOut ) != HAL_OK )
    {
        return UART_ERROR;
    }

    return UART_OK;
}

/**
 *
 * @param Uart
 * @param UartConfig
 * @return
 **/
UartStatus_t DRV_UART_Receive( Uart_t *Uart, uint8_t *pData, uint32_t DataSize )
{
    if( HAL_UART_Receive( &Uart->Handle, pData, DataSize, Uart->TimeOut ) != HAL_OK )
    {
        return UART_ERROR;
    }

    return UART_OK;
}

/**
 *
 * @param Uart
 * @param UartConfig
 * @return
 **/
UartStatus_t DRV_UART_TransmitISR( Uart_t *Uart, uint8_t *pData, uint32_t DataSize )
{
    if( HAL_UART_Transmit_IT( &Uart->Handle, pData, DataSize ) != HAL_OK )
    {
        return UART_ERROR;
    }

    return UART_OK;
}

/**
 *
 * @param Uart
 * @param UartConfig
 * @return
 **/
UartStatus_t DRV_UART_ReceiveISR( Uart_t *Uart, uint8_t *pData, uint32_t DataSize )
{
    if( HAL_UART_Receive_IT( &Uart->Handle, pData, DataSize ) != HAL_OK )
    {
        return UART_ERROR;
    }

    return UART_OK;
}

/**
 *
 * @param Uart
 * @param UartConfig
 * @return
 **/
UartStatus_t DRV_UART_Print( Uart_t *Uart, char *pString )
{
    /** Local variables **/
    char NullChar = '\0';

    while( (*pString) != NullChar )
    {
        HAL_UART_Transmit(&Uart->Handle, (uint8_t*)pString, 1, Uart->TimeOut);

        pString++;
    }

    /** Transmit null char **/
    HAL_UART_Transmit(&Uart->Handle, (uint8_t *)&NullChar, 1, Uart->TimeOut);

    return UART_OK;
}

/**
 *
 * @param Uart
 * @param UartConfig
 * @return
 **/
UartStatus_t DRV_UART_PrintLn( Uart_t *Uart, char *pString )
{
    /** Local variables **/
    char LnChar = '\n';

    while( (*pString) != '\0' )
    {
        HAL_UART_Transmit(&Uart->Handle, (uint8_t *)pString, 1, Uart->TimeOut);

        pString++;
    }

    /** Transmit Line Jump and Null char **/
    HAL_UART_Transmit(&Uart->Handle, (uint8_t *)&LnChar, 1, Uart->TimeOut);

    return UART_OK;
}

/****************************************************************
 *                      Private Functions                       *
 ****************************************************************/

/**
 *
 * @param Uart
 * @param UartConfig
 * @return
 **/
void UART_InitClock( USART_TypeDef *Instance )
{
    if( Instance == USART1 )
    {
        __HAL_RCC_USART1_CLK_ENABLE();
    }
    else if( Instance == USART2 )
    {
        __HAL_RCC_USART2_CLK_ENABLE();
    }
    else if( Instance == USART3 )
    {
        __HAL_RCC_USART3_CLK_ENABLE();
    }
    else
    {
        return;
    }
}

/**
 *
 * @param Uart
 * @param UartConfig
 * @return
 **/
void UART_DeInitClock( USART_TypeDef *Instance )
{
    if( Instance == USART1 )
    {
        __HAL_RCC_USART1_CLK_DISABLE();
    }
    else if( Instance == USART2 )
    {
        __HAL_RCC_USART2_CLK_DISABLE();
    }
    else if( Instance == USART3 )
    {
        __HAL_RCC_USART3_CLK_DISABLE();
    }
    else
    {
        return;
    }
}

/**
 *
 * @param Uart
 * @param UartConfig
 * @return
 **/
void UART_EnableIRQ( USART_TypeDef *Instance, uint8_t Priority, uint8_t Subpriority )
{
    /** Local Variables **/
    uint8_t UARTSelectedIRQ = 0;

    /** Select the USART **/
    if( Instance == USART1 ) { UARTSelectedIRQ = 0; }
    if( Instance == USART2 ) { UARTSelectedIRQ = 0; }
    if( Instance == USART3 ) { UARTSelectedIRQ = 0; }

    /** Enable IRQ **/
    HAL_NVIC_SetPriority( UARTISRTable[UARTSelectedIRQ], Priority, Subpriority );
    HAL_NVIC_EnableIRQ( UARTISRTable[UARTSelectedIRQ] );

}