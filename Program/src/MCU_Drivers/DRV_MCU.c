/****************************************************************
 *                      Required Headers                        *
 ****************************************************************/
#include "MCU_Drivers/DRV_MCU.h"

/****************************************************************
 *                      Extern Variables                        *
 ****************************************************************/
Uart_t huart2;

/****************************************************************
 *                      Static Variables                        *
 ****************************************************************/
UartConfig_t huart2_cfg;

/****************************************************************
 *                  Static Prototype Functions                  *
 ****************************************************************/
static void DRV_UART2_Init(void);

/****************************************************************
 *                                                              *
 *                          Functions                           *
 *                                                              *
 ****************************************************************/

/*
 *
 *
 */
void MCU_DRV_Init(void)
{
    /** MCU Driver Inits **/
    DRV_GPIO_Init();
    DRV_UART2_Init();
    DRV_I2C1_Init();
    DRV_TIM2_Init();
}


static void DRV_UART2_Init(void)
{
    huart2_cfg.SerialPort   = USART2;
    huart2_cfg.Baudrate     = 115200;
    huart2_cfg.Mode         = UART_MODE_TX_RX;
    huart2_cfg.Parity       = UART_PARITY_NONE;
    huart2_cfg.StopBits     = UART_STOPBITS_1;
    huart2_cfg.WordLength   = UART_WORDLENGTH_8B;
    huart2_cfg.HwFlowCtl    = UART_HWCONTROL_NONE;
    huart2_cfg.Oversampling = UART_OVERSAMPLING_8;
    huart2_cfg.ISR.Enable   = UART_ISR_DISABLE;
    huart2_cfg.TimeOut      = 1000;

    DRV_UART_Init( &huart2, &huart2_cfg );

}