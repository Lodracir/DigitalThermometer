/****************************************************************
 *                                                              *
 *                     Required Includes                        *
 *                                                              *
 ****************************************************************/

//App
#include "AppMain.h"

//Modules
#include "Modules/SerialComm.h"

/****************************************************************
 *                                                              *
 *                   Static Variables                           *
 *                                                              *
 ****************************************************************/

static SerialConfig_t SerialComm_Config = {
    .Instance = USART2,
    .Baudrate = SERIAL_COMM_BAUDRATE
};

/****************************************************************
 *                       Functions                              *
 ****************************************************************/

void AppInit(void)
{
    /** Init Modules **/
    SerialComm_Init(&SerialComm_Config);


}

void AppMain(void)
{

}
