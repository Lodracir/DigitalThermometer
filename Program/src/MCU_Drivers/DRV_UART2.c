/* DRV UART2 Header */
#include "MCU_Drivers/DRV_UART2.h"

/* UART2 Typedef Structure */
UART_HandleTypeDef huart2;

/*  Static Prototype Functions */
static void DRV_UART2_Transmit(uint8_t *pData, uint8_t size);
static void DRV_UART2_Receive(uint8_t *pData, uint8_t size);

/****************************************************************
 *                                                              *
 *                          Functions                           *
 *                                                              *
 ****************************************************************/

/*
 *
 *
 *
 */
void DRV_UART2_Init(void)
{

    // Allocate functions
    Serial.Transmit = DRV_UART2_Transmit;
    Serial.Receive  = DRV_UART2_Receive;

    // Configure UART2
    huart2.Instance            = USART2;
    huart2.Init.BaudRate       = 115200;
    huart2.Init.Mode           = UART_MODE_TX_RX;
    huart2.Init.Parity         = UART_PARITY_NONE;
    huart2.Init.StopBits       = UART_STOPBITS_1;
    huart2.Init.WordLength     = UART_WORDLENGTH_8B;
    huart2.Init.HwFlowCtl      = UART_HWCONTROL_NONE;
    huart2.Init.OverSampling   = UART_OVERSAMPLING_16;
    huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
    HAL_UART_Init(&huart2);

}

void DRV_UART2_DeInit(void)
{

    // DeAllocate Functions
    Serial.Transmit     = NULL;
    Serial.Receive      = NULL;

    // UART2 DeInit
    HAL_UART_DeInit(&huart2);

}

/****************************************************************
 *                                                              *
 *                     Static Functions                         *
 *                                                              *
 ****************************************************************/

/*
 *
 *
 *
 */
static void DRV_UART2_Transmit(uint8_t *pData, uint8_t size)
{

    HAL_UART_Transmit(&huart2, pData, size, HAL_MAX_DELAY);

}

/*
 *
 *
 *
 */
static void DRV_UART2_Receive(uint8_t *pData, uint8_t size)
{

    HAL_UART_Receive(&huart2, pData, size, HAL_MAX_DELAY);

}