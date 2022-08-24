/* Include Main Header */
#include "main.h"
#include "APP/HDC2010.h"
#include "APP/eeprom.h"

/** DEFINES **/


/*- MCU Peripherals Objects -*/
extern I2C_HandleTypeDef hi2c1;
extern TIM_HandleTypeDef htim2;

/*- App Objects -*/
HDC2010_t   HDC2010;
EEPROM_t    Memory;

/** Extern Variables **/
extern bool MeasureFLAG;

/** Global Variables **/
const char welcomeTxt[10] = "Welcome!\r\n";


int main()
{

    /* Local Variables */
    char devID[20], devMnfr[20], TempTXT[15], HumTXT[15];
    Value_t Temperature, Humidity;
    uint16_t tempValue = 0, humValue = 0;
    HDC2010_DeviceInfo_t  SensorInfo;
    HDC2010_Values_t SensorValues;
 
    /** **/
    memset(devID, ' ', sizeof(devID));
    memset(devID, ' ', sizeof(devMnfr));
    memset(devID, ' ', sizeof(TempTXT));
    memset(devID, ' ', sizeof(HumTXT));

    /** Init HAL Driver **/
    HAL_Init();

    /** Init MCU Peripherals */
    MCU_DRV_Init();

    /** Set PB3 Low **/
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_RESET);

    /** Init App Drivers **/
    HDC2010_Init(&HDC2010);
    EEPROM_Init(&Memory);

    /** Transmit Initial Message **/
    Serial.Transmit((uint8_t *)welcomeTxt, sizeof(welcomeTxt));

    /** Get Information **/
    HDC2010.readInfo(&hi2c1, &SensorInfo);

    /**************** Print Device Info through UART ****************/
    sprintf(devMnfr, "Mnfr ID: 0x%04X\r\n", SensorInfo.Manufacturer);
    sprintf(devID, "Dev ID: 0x%04X\r\n", SensorInfo.Device);

    Serial.Transmit( (uint8_t *)devMnfr, sizeof(devMnfr));
    Serial.Transmit( (uint8_t *)devID, sizeof(devID) );
    /****************************************************************/

    /***************** Store Sensor info to EEPROM  *****************/
    Memory.write.D16BIT(&hi2c1, MEM_BLOCK_0, DevMnfr_MemAddr, SensorInfo.Manufacturer);
    Memory.write.D16BIT(&hi2c1, MEM_BLOCK_0, DevID_MemAddr, SensorInfo.Device);
    /****************************************************************/

    /*************************** Init TIM2 **************************/
    HAL_TIM_Base_Start_IT(&htim2);
    /****************************************************************/

    while(1)
    {

        if(MeasureFLAG == true)
        {

            /* Request Measurement */
            HDC2010.pollMeasurement(&hi2c1, &SensorValues); // .pollMeasurement(&hi2c1)
                                                            // .getTemperature(&hi2c1, &Temperature.value)
                                                            // .getHumidity(&hi2c1, &Humidity.value)

            Temperature.value = SensorValues.Temp.value;
            Humidity.value  = SensorValues.Hum.value;

            sprintf(TempTXT, "Temp: %i\r\n", (int)Temperature.value);
            sprintf(HumTXT, "HUM: %i\r\n", (int)Humidity.value);

            Serial.Transmit((uint8_t *)TempTXT, sizeof(TempTXT));
            Serial.Transmit((uint8_t *)HumTXT, sizeof(HumTXT));

            MeasureFLAG = false;

        }

    }

}


