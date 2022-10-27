/** GPIO Header Driver **/
#include "MCU_Drivers/DRV_GPIO.h"

/****************************************************************
 *                                                              *
 *                          Functions                           *
 *                                                              *
 ****************************************************************/

void DRV_GPIO_Init(void)
{

    /** GPIO Init Structure **/
    GPIO_InitTypeDef hgpio;

    /** GPIO Clock Inits **/
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOF_CLK_ENABLE();

    /** Configure PB3 as Output **/
    hgpio.Pin   = GPIO_PIN_3;
    hgpio.Mode  = GPIO_MODE_OUTPUT_PP;
    hgpio.Pull  = GPIO_NOPULL;
    hgpio.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOB, &hgpio);

    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_RESET);

    /** Configure PA4 as Output **/
    hgpio.Pin   = GPIO_PIN_4;
    hgpio.Mode  = GPIO_MODE_OUTPUT_PP;
    hgpio.Pull  = GPIO_NOPULL;
    hgpio.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOA, &hgpio);

    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);

}

/****************************************************************
 *                                                              *
 *                       MSP Functions                          *
 *                                                              *
 ****************************************************************/

/********************** UART2 Msp Functions *********************/

void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{

    if( huart->Instance == USART2 )
    {

        /** GPIO Init Structure **/
        GPIO_InitTypeDef hgpio_uart2;

        /** UART2 Clock Init **/
        __HAL_RCC_USART2_CLK_ENABLE();

        /** PA2 and PA15 GPIO Configuration **/
        hgpio_uart2.Pin         = GPIO_PIN_2 | GPIO_PIN_15;
        hgpio_uart2.Mode        = GPIO_MODE_AF_PP;
        hgpio_uart2.Pull        = GPIO_NOPULL;
        hgpio_uart2.Speed       = GPIO_SPEED_FREQ_HIGH;
        hgpio_uart2.Alternate   = GPIO_AF7_USART2;
        HAL_GPIO_Init(GPIOA, &hgpio_uart2);

    }

}

void HAL_UART_MspDeInit(UART_HandleTypeDef *huart)
{

    if( huart->Instance == USART2 )
    {
        /** Disable UART2 Clock **/
        __HAL_RCC_USART1_CLK_DISABLE();

        /** GPIO DeInit **/
        HAL_GPIO_DeInit(GPIOA, GPIO_PIN_2 | GPIO_PIN_15);
    }

}

/********************** I2C1 Msp Functions **********************/

void HAL_I2C_MspInit(I2C_HandleTypeDef *hi2c)
{

    if( hi2c->Instance == I2C1 )
    {

        /** GPIO Init Structure **/
        GPIO_InitTypeDef hgpio_i2c1;

        /** Enable I2C1 Clock **/
        __HAL_RCC_I2C1_CLK_ENABLE();

        /** PB6 and PB7 Configuration **/
        hgpio_i2c1.Pin          = GPIO_PIN_6 | GPIO_PIN_7;
        hgpio_i2c1.Mode         = GPIO_MODE_AF_OD;
        hgpio_i2c1.Pull         = GPIO_PULLUP;
        hgpio_i2c1.Speed        = GPIO_SPEED_FREQ_HIGH;
        hgpio_i2c1.Alternate    = GPIO_AF4_I2C1;
        HAL_GPIO_Init(GPIOB, &hgpio_i2c1);

    }

}

void HAL_I2C_MspDeInit(I2C_HandleTypeDef *hi2c)
{

    if(hi2c->Instance == I2C1)
    {
        /** Disable I2C1 Clock **/
        __HAL_RCC_I2C1_CLK_DISABLE();

        /** GPIO DeInit **/
        HAL_GPIO_DeInit(GPIOB, GPIO_PIN_6 | GPIO_PIN_7);
    }

}

/********************** SPI1 Msp Functions *********************/

void HAL_SPI_MspInit(SPI_HandleTypeDef *hspi)
{

    if( hspi->Instance  == SPI1 )
    {

        /** GPIO Init Structure **/
        //GPIO_InitTypeDef hgpio_spi1;

        /** Enable SPI1 Clock **/
        __HAL_RCC_SPI1_CLK_ENABLE();

    }

}

void HAL_SPI_MspDeInit(SPI_HandleTypeDef *hspi)
{

    if( hspi->Instance == SPI1 )
    {

        /** Disable SPI1 Clock **/
        __HAL_RCC_I2C1_CLK_DISABLE();

        /** Disable GPIO Pins related to SPI1 **/


    }

}