/** Include Main Header **/
#include "main.h"

/** App UML Declaration **/
volatile APP_UML_t APPStateMachine = STATE_DEFAULT;

/** **/
typedef struct 
{
    uint8_t     SensorInfo; 
}EE_Flags_t;


/** **/
typedef struct 
{
    EE_Flags_t  Stored;
}Flags_t;


/** App Objects **/
HDC2010_t   HDC2010;
EEPROM_t    Memory;

/** Extern Variables **/
extern volatile bool MeasureFLAG;

/** Global Variables **/
const char welcomeTxt[10] = "Welcome!\r\n";
char msg[20];
uint8_t MsgSize = 0x00;
float TempBuff[5], HumBuff[5];
uint16_t TempBuffBits[5], HumBuffBits[5];
char devID[20], devMnfr[20], TempTXT[11], HumTXT[10];
Value_t Temperature, Humidity;
Flags_t Flag;
HDC2010_DeviceInfo_t  SensorInfo;
uint8_t EE_SensorInfo_Flag = 0x00, EE_SensorInfo_Flag_EE_Addr = 0x20;

/** Prototype Functions **/
void APPInit( void );

void APP_START_MEASUREMENT(void);
void APP_STORE_DATA_TO_BUFFER(void);
void APP_STORE_DATA_TO_EEPROM(void);
void APP_DEFAULT(void);

int main()
{
    /** Local Variables **/

 
    /** Clear all String **/
    memset(devID, 0x00, sizeof(devID));
    memset(devMnfr, 0x00, sizeof(devMnfr));
    memset(TempTXT, 0x00, sizeof(TempTXT));
    memset(HumTXT, 0x00, sizeof(HumTXT));

    /** Init HAL Driver **/
    HAL_Init();

    /** Init MCU Peripherals */
    MCU_DRV_Init();

    /** Set PB3 Low **/
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_SET);

    /** Init App Drivers **/
    AppInit();
    APPInit();

    /** Transmit Initial Message **/
    Serial.PrintLn("Digital Thermometer Program V0.1b");

    /** **/
    //APP_CheckStoredSensorInfo_Flag(&Flag.Stored.SensorInfo);

    /** Check Flags from EEPROM **/
    Memory.ReadData( MEM_BLOCK_0, EE_SensorInfo_Flag_EE_Addr, (void *)&Flag.Stored.SensorInfo, D_UINT8 );

    if(Flag.Stored.SensorInfo != 0x01)
    {
        // Read Sensor information from HDC2010 Sensor
        HDC2010.readInfo( &SensorInfo );    

        // Store Sensor data to EEPROM 
        Memory.WriteData(MEM_BLOCK_0, DevMnfr_MemAddr, (void *)&SensorInfo.Manufacturer, D_UINT16);
        Memory.WriteData(MEM_BLOCK_0, DevID_MemAddr, (void *)&SensorInfo.Device, D_UINT16 );

        // Store Sensor Info FLAG Information
        Flag.Stored.SensorInfo = 0x01;
        Memory.WriteData(MEM_BLOCK_0, EE_SensorInfo_Flag_EE_Addr, (void*)&Flag.Stored.SensorInfo, D_UINT8);
    }
    else    // Read Info from EEPROM
    {
        Memory.ReadData(MEM_BLOCK_0, DevMnfr_MemAddr, (void *)&SensorInfo.Manufacturer, D_UINT16);
        Memory.ReadData(MEM_BLOCK_0, DevID_MemAddr, (void *)&SensorInfo.Device, D_UINT16 );
    }
    
    /**************** Print Device Info through UART ****************/
    MsgSize = sprintf(devMnfr, "Mnfr ID: 0x%04X\r\n", SensorInfo.Manufacturer);
    Serial.Transmit( (uint8_t *)devMnfr, MsgSize );

    MsgSize = sprintf(devID, "Dev ID: 0x%04X\r\n", SensorInfo.Device);
    Serial.Transmit( (uint8_t *)devID, MsgSize );
    /****************************************************************/

    /*************************** Init TIM2 **************************/
    DRV_TIM2_Start_IT(); //TODO: Will be relocated
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

void APPInit( void )
{
    /* Init External objects */
    HDC2010_Init( &HDC2010 );
    EEPROM_Init( &Memory );
}

void APP_START_MEASUREMENT(void)
{
    /** Request Measurement **/
    HDC2010.pollMeasurement();
    HDC2010.getTemperature( &Temperature.value );
    HDC2010.getHumidity( &Humidity.value );


    /** Transmit Sensor Data (Test Purpuse) **/
    sprintf(TempTXT, "T: %i C\r\n", (int)Temperature.value);
    sprintf(HumTXT, "H: %i RH\r\n", (int)Humidity.value);

    //Serial.Transmit( (uint8_t *)TempTXT, sizeof(devMnfr));
    //Serial.Transmit( (uint8_t *)HumTXT, sizeof(devID) );

}

void APP_DEFAULT(void)
{
    // Do something.....
}