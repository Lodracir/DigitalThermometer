/*****************************************
 *
 * Required Headers
 *
 *****************************************/
#include "MCU_Drivers/DRV_UART.h"

/*****************************************
 *
 * UART ISR Table
 *
 *****************************************/

typedef enum
{
    UART1_ISR = 0,
    UART2_ISR,
    UART3_ISR
}UartIRQnInstance_t;

static IRQn_Type UARTISRTable[3] = { USART1_IRQn , USART2_IRQn , USART3_IRQn };

/*****************************************
 *
 * Static Local variables
 *
 *****************************************/
static GPIO_InitTypeDef GPIOInitStructure;
static UartStatus_t UartStatus;
static UartIRQnInstance_t UartISRInstance;

/*****************************************
 *
 * Static local prototype functions
 *
 *****************************************/
void DrvUartSelectISRInstance( Uart_t *Uart );

/**
 * Callback prototype functions
 **/
UartStatus_t DrvUart_Transmit( uint8_t *pData, uint32_t DataSize );
UartStatus_t DrvUart_Receive( uint8_t *pData, uint32_t DataSize );

/*****************************************
 *
 * Public Functions
 *
 *****************************************/

/**
 *
 *
 *
 **/
UartStatus_t DRV_UART_Init( Uart_t *Uart, UartConfig_t *UartConfig )
{

    /** Global Variables **/
    UartStatus = UART_OK;

    /** Config selected UART Instance **/
    Uart->UartInstance.Instance         = UartConfig->SerialPort;
    Uart->UartInstance.Init.BaudRate    = UartConfig->Baudrate;
    Uart->UartInstance.Init.WordLength  = UartConfig->WordLength;
    Uart->UartInstance.Init.StopBits    = UartConfig->StopBits;
    Uart->UartInstance.Init.Parity      = UartConfig->Parity;
    Uart->UartInstance.Init.Mode        = UartConfig->TransmitMode;
    Uart->UartInstance.Init.HwFlowCtl   = UartConfig->HwFlowCtl;
    Uart->TimeOut                       = UartConfig->TimeOut;

    /** Default configuration **/
    Uart->UartInstance.Init.OverSampling     = UART_OVERSAMPLING_16;
    Uart->UartInstance.Init.OneBitSampling   = UART_ONE_BIT_SAMPLE_DISABLE;
    Uart->UartInstance.AdvancedInit.AdvFeatureInit   = UART_ADVFEATURE_NO_INIT;

    /** Init Selected UART instance **/
    if ( HAL_UART_Init( & Uart->UartInstance ) != HAL_OK )
    {
        UartStatus = UART_ERROR;
    }

    /* If Interrupt is requested */
    if( UartConfig->Mode == UART_INTERRUPT_MODE )
    {
        HAL_NVIC_SetPriority( UARTISRTable[UartISRInstance], 0, 0 );
        HAL_NVIC_EnableIRQ( UARTISRTable[UartISRInstance] );
    }

    /* */
    return UartStatus;

}

/**
 *
 *
 *
 **/
void DRV_UART_DeInit( Uart_t *Uart )
{

    /** DeInit UARTx Instance **/
    HAL_UART_DeInit( &Uart->UartInstance );

}

/**
 *
 *
 *
 **/
UartStatus_t DRV_UART_Transmit( Uart_t *Uart, uint8_t *pData, uint32_t DataSize )
{
    UartStatus = UART_OK;

    if( HAL_UART_Transmit( & Uart->UartInstance, pData, DataSize, Uart->TimeOut ) != HAL_OK )
    {
        UartStatus = UART_ERROR;
    }

    return UartStatus;
}

/**
 *
 *
 *
 **/
UartStatus_t DRV_UART_Receive( Uart_t *Uart, uint8_t *pData, uint32_t DataSize )
{
    UartStatus = UART_OK;

    if( HAL_UART_Receive( &Uart->UartInstance, pData, DataSize, Uart->TimeOut ) != HAL_OK )
    {
        UartStatus = UART_ERROR;
    }

    return UartStatus;
}

/**
 *
 *
 *
 **/
UartStatus_t DRV_UART_TransmitISR( Uart_t *Uart, uint8_t *pData, uint32_t DataSize )
{
    UartStatus = UART_OK;

    if( HAL_UART_Transmit_IT( &Uart->UartInstance, pData, DataSize ) != HAL_OK )
    {
        UartStatus = UART_ERROR;
    }

    return UartStatus;

}

/**
 *
 *
 *
 **/
UartStatus_t DRV_UART_ReceiveISR( Uart_t *Uart, uint8_t *pData, uint32_t DataSize )
{
    UartStatus = UART_OK;

    if( HAL_UART_Receive_IT( &Uart->UartInstance, pData, DataSize ) != HAL_OK )
    {
        UartStatus = UART_ERROR;
    }

    return UartStatus;

}

/**
 *
 *
 *
 **/
UartStatus_t DRV_UART_Print( Uart_t *Uart, char *pString )
{
    /** Local variables **/
    UartStatus = UART_OK;
    char NullChar = '\0';

    while( (*pString) != NullChar )
    {
        HAL_UART_Transmit(&Uart->UartInstance, (uint8_t*)pString, _1byte, Uart->TimeOut);

        pString++;
    }

    /** Transmit null char **/
    HAL_UART_Transmit(&Uart->UartInstance, (uint8_t *)&NullChar, _1byte, Uart->TimeOut);

    return UartStatus;

}

/**
 *
 *
 *
 **/
UartStatus_t DRV_UART_PrintLn( Uart_t *Uart, char *pString )
{
    /** Local variables **/
    UartStatus = UART_OK;
    char LnChar = '\n';

    while( (*pString) != '\0' )
    {
        HAL_UART_Transmit(&Uart->UartInstance, (uint8_t *)pString, _1byte, Uart->TimeOut);

        pString++;
    }

    /** Transmit Line Jump and Null char **/
    HAL_UART_Transmit(&Uart->UartInstance, (uint8_t *)&LnChar, _1byte, Uart->TimeOut);

    return UartStatus;

}

/*****************************************
 *
 * Static local prototype functions
 *
 *****************************************/

/**
 *
 *
 *
 **/
void DRV_UART1_MspInit( void )
{

    /** Enable UART1 and GPIOA Clock **/
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_USART1_CLK_ENABLE();

    /** Configure TX and RX Pins **/
    GPIOInitStructure.Pin       = GPIO_PIN_9 | GPIO_PIN_10 ;
    GPIOInitStructure.Mode      = GPIO_MODE_AF_PP;
    GPIOInitStructure.Pull      = GPIO_NOPULL;
    GPIOInitStructure.Speed     = GPIO_SPEED_FREQ_HIGH;
    GPIOInitStructure.Alternate = GPIO_AF7_USART1;
    HAL_GPIO_Init( GPIOA, &GPIOInitStructure );

}

/**
 *
 *
 *
 **/
void DRV_UART2_MspInit( void )
{

    /** Enable UART2 and GPIOA Clock **/
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_USART2_CLK_ENABLE();

    /** Configure TX Pin **/
    GPIOInitStructure.Pin       = GPIO_PIN_2;
    GPIOInitStructure.Mode      = GPIO_MODE_AF_PP;
    GPIOInitStructure.Pull      = GPIO_NOPULL;
    GPIOInitStructure.Speed     = GPIO_SPEED_FREQ_HIGH;
    GPIOInitStructure.Alternate = GPIO_AF7_USART2;
    HAL_GPIO_Init( GPIOA, &GPIOInitStructure );

    /** Configure RX Pin **/
    GPIOInitStructure.Pin       = GPIO_PIN_15;
    GPIOInitStructure.Mode      = GPIO_MODE_AF_PP;
    GPIOInitStructure.Pull      = GPIO_NOPULL;
    GPIOInitStructure.Speed     = GPIO_SPEED_FREQ_HIGH;
    GPIOInitStructure.Alternate = GPIO_AF7_USART2;
    HAL_GPIO_Init( GPIOA, &GPIOInitStructure );

}

/**
 *
 *
 *
 **/
void DRV_UART1_MspDeInit( void )
{

    /** Disable UART1 Clock  **/
    __HAL_RCC_USART1_CLK_DISABLE();

    /** DeInit GPIO Pins **/
    HAL_GPIO_DeInit( GPIOA, GPIO_PIN_9 | GPIO_PIN_10 );

}

/**
 *
 *
 *
 **/
void DRV_UART2_MspDeInit( void )
{

    /** Disable UART2 Clock **/
    __HAL_RCC_USART2_CLK_DISABLE();

    /** DeInit GPIO Pins **/
    HAL_GPIO_DeInit( GPIOA, GPIO_PIN_2 | GPIO_PIN_15 );

}

/*****************************************
 *
 * Static local functions
 *
 *****************************************/
void DrvUartSelectISRInstance( Uart_t *Uart )
{

    /** **/
    if( Uart->UartInstance.Instance == USART1 )
    {
        UartISRInstance = UART1_ISR;
    }
    else if( Uart->UartInstance.Instance == USART2 )
    {
        UartISRInstance = UART2_ISR;
    }
    else if( Uart->UartInstance.Instance == USART3 )
    {
        UartISRInstance = UART3_ISR;
    }

}

/**
 * Callback prototype functions
 **/
UartStatus_t DrvUart_Transmit( uint8_t *pData, uint32_t DataSize )
{


    return UartStatus;

}


UartStatus_t DrvUart_Receive( uint8_t *pData, uint32_t DataSize )
{



    return UartStatus;

}