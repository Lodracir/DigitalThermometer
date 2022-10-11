/* Include Main Header */
#include "main.h"
#include "APP/HDC2010.h"
#include "APP/eeprom.h"

/** DEFINES **/
#define DevMnfr_MemAddr 0x10    
#define DevID_MemAddr   0x12

/* MCU Peripherals Objects */
extern I2C_HandleTypeDef hi2c1;
extern TIM_HandleTypeDef htim2;

// UART2
Uart_t huart2;
UartConfig_t huart2_cfg;

/* App Objects */
HDC2010_t   HDC2010;
EEPROM_t    Memory;

/** Extern Variables **/
extern bool MeasureFLAG;

/* Global Variables */
const char welcomeTxt[10] = "Welcome!\r\n";
uint8_t MemoryAddr = (0x50 << 1);
uint8_t TransmitBuff[2];

int main()
{

    /* Local Variables */
    char devID[20], devMnfr[20], TempTXT[15], HumTXT[15];
    uint16_t tempValue = 0, humValue = 0;
    HDC2010_DeviceInfo_t  SensorInfo;
    HDC2010_Values_t      SensorValues;
 
    /** **/
    memset(devID, 0, sizeof(devID));
    memset(devID, 0, sizeof(devMnfr));
    memset(devID, 0, sizeof(TempTXT));
    memset(devID, 0, sizeof(HumTXT));

    /** Init HAL Driver **/
    HAL_Init();

    /** Init MCU Peripherals */
    MCU_DRV_Init();

    /* Set PB3 Low */
    //BSP_LD3_WritePin(GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_RESET);

    /* Init App Drivers */
    HDC2010_Init(&HDC2010);
    EEPROM_Init(&Memory);

    /* Transmit Initial Message */
    Serial.Transmit((uint8_t *)welcomeTxt, sizeof(welcomeTxt));

    /* Get Information */
    HDC2010.readInfo(&hi2c1, &SensorInfo);

    /**************** Print Device Info through UART ****************/

    sprintf(devMnfr, "Mnfr ID: 0x%04X\r\n", SensorInfo.Manufacturer);
    sprintf(devID, "Dev ID: 0x%04X\r\n", SensorInfo.Device);

    Serial.Transmit( (uint8_t *)devMnfr, sizeof(devMnfr));
    Serial.Transmit( (uint8_t *)devID, sizeof(devID) );

    /****************************************************************/

    /***************** Store Sensor info to EEPROM  *****************/
    
    // Write Sensor info to EEPROM
    Memory.write.D16BIT(&hi2c1, MEM_BLOCK_0, DevMnfr_MemAddr, SensorInfo.Manufacturer);
    Memory.write.D16BIT(&hi2c1, MEM_BLOCK_0, DevID_MemAddr, SensorInfo.Device);

    /****************************************************************/

    /** Init TIM2 **/
    HAL_TIM_Base_Start_IT(&htim2);

    while(1)
    {

        if(MeasureFLAG == true)
        {

            /* Request Measurement */
            HDC2010.pollMeasurement(&hi2c1, &SensorValues);

            tempValue = (uint16_t)SensorValues.Temp.value;
            humValue  = (uint16_t)SensorValues.Hum.value;

                HAL_Delay(1000);
            sprintf(TempTXT, "Temp: %i\r\n", tempValue);
            sprintf(HumTXT, "HUM: %i\r\n", humValue);

        }

    }

}


