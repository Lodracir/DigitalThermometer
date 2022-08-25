/** Include Main Header **/
#include "main.h"


/** MCU Peripherals Objects **/
extern I2C_HandleTypeDef hi2c1;
extern TIM_HandleTypeDef htim2;

/** App UML Declaration **/
volatile APP_UML_t APPStateMachine = STATE_DEFAULT;

/** App Objects **/
HDC2010_t   HDC2010;
EEPROM_t    Memory;

/** Extern Variables **/
extern volatile bool MeasureFLAG;

/** Global Variables **/
const char welcomeTxt[10] = "Welcome!\r\n";
float TempBuff[5], HumBuff[5];
uint16_t TempBuffBits[5], HumBuffBits[5];
char devID[20], devMnfr[20], TempTXT[11], HumTXT[10];
Value_t Temperature, Humidity;
HDC2010_DeviceInfo_t  SensorInfo;

/** Prototype Functions **/
void APP_START_MEASUREMENT(void);
void APP_STORE_DATA_TO_BUFFER(void);
void APP_STORE_DATA_TO_EEPROM(void);
void APP_DEFAULT(void);

int main()
{
    /** Local Variables **/

 
    /** Clear all String **/
    memset(devID, ' ', sizeof(devID));
    memset(devMnfr, ' ', sizeof(devMnfr));
    memset(TempTXT, ' ', sizeof(TempTXT));
    memset(HumTXT, ' ', sizeof(HumTXT));

    /** Init HAL Driver **/
    HAL_Init();

    /** Init MCU Peripherals */
    MCU_DRV_Init();

    /** Set PB3 Low **/
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_SET);

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
    //Memory.write.D16BIT(&hi2c1, MEM_BLOCK_0, DevMnfr_MemAddr, SensorInfo.Manufacturer);
    //Memory.write.D16BIT(&hi2c1, MEM_BLOCK_0, DevID_MemAddr, SensorInfo.Device);
    /****************************************************************/

    /*************************** Init TIM2 **************************/
    HAL_TIM_Base_Start_IT(&htim2);
    /****************************************************************/

    while(1)
    {

        switch(APPStateMachine)
        {
            case START_MEASUREMENT:
                HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_SET);
                APP_START_MEASUREMENT();
                APPStateMachine = STATE_DEFAULT;
                break;

            case STATE_DEFAULT:
                APP_DEFAULT();
                break;
        }

    }

}

void APP_START_MEASUREMENT(void)
{
    /** Request Measurement **/
    HDC2010.pollMeasurement(&hi2c1);
    HDC2010.getTemperature(&hi2c1, &Temperature.value);
    HDC2010.getHumidity(&hi2c1, &Humidity.value);

}

void APP_DEFAULT(void)
{
    // Do something.....
}