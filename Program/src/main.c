/* Include Main Header */
#include "main.h"
#include "APP/HDC2010.h"
#include "APP/eeprom.h"

/* MCU Peripherals Objects */
extern I2C_HandleTypeDef hi2c1;

/* App Objects */
HDC2010_t   HDC2010;
EEPROM_t    Memory;

/* Global Variables */
const char welcomeTxt[10] = "Welcome!\r\n";
uint8_t MemoryAddr = (0x50 << 1);
uint8_t TransmitBuff[2];

int main()
{

    /* Local Variables */
    char devID[20], devMnfr[20], TempTXT[15], HumTXT[15], msg[15];
    uint16_t tempValue = 0, humValue = 0;
    HDC2010_DeviceInfo_t  SensorInfo;
    HDC2010_Values_t      SensorValues;
    uint8_t data, data2send = 0x54;

    /**/
    memset(devID, 0, sizeof(devID));
    memset(devID, 0, sizeof(devMnfr));
    memset(devID, 0, sizeof(TempTXT));
    memset(devID, 0, sizeof(HumTXT));

    /* Init HAL Driver */
    HAL_Init();

    /* Init MCU Peripherals */
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

    //sprintf(devMnfr, "Mnfr ID: 0x%04X\r\n", SensorInfo.Manufacturer);
    //sprintf(devID, "Dev ID: 0x%04X\r\n", SensorInfo.Device);

    //Serial.Transmit( (uint8_t *)devMnfr, sizeof(devMnfr));
    //Serial.Transmit( (uint8_t *)devID, sizeof(devID) );

    /****************************************************************/

    /********************* Read Info from EEPROM ********************/

    Memory.read.D8BIT(&hi2c1, MEM_BLOCK_0, 0x48, &data);

    sprintf(msg, "Data: 0x%02X\r\n", data);
    Serial.Transmit( (uint8_t *)msg, sizeof(msg) );

    /****************************************************************/

    /********************* Write Info to EEPROM *********************/

    Memory.write.D8BIT(&hi2c1, MEM_BLOCK_0, 0x48, 0x3C);

    HAL_Delay(1000);

    Memory.read.D8BIT(&hi2c1, MEM_BLOCK_0, 0x48, &data);

    sprintf(msg, "Data: 0x%02X\r\n", data);
    Serial.Transmit( (uint8_t *)msg, sizeof(msg) );

    /****************************************************************/

    while(1)
    {



    }

}


