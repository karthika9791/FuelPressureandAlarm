//**************************** FuelPressure&Alarm ****************************** 
//  Copyright (c) 2026 Trenser Technology Solutions 
//  All Rights Reserved 
//****************************************************************************** 
// 
// File    : sensor.c
// Summary : File which contains functions for sensor initialozation and data 
//           transfer
// Note    : None
// Author  : Karthika V T
// Date    : 25-03-2026
// 
//******************************************************************************

//******************************* Include Files ********************************
#include "sensor.h"
#include "main.h"

//******************************* Local Types **********************************

//***************************** Local Constants ********************************

//***************************** Local Variables ********************************

//****************************** Local Functions *******************************
static uint16_t sensorPressure_Read (void);

//****************************** FUNCTION_HEADER ******************************* 
//Purpose : This function creates a message queue object and the pressure varia- 
//          ble reads value from Pressure_Read function. The incoming pressure
//          value is send to the validation process using mq_send.
//Inputs  : None
//Outputs : Created messagequeue and pressure data is send to queue 
//Return  : None
//Notes   : None
//****************************************************************************** 
void * sensorThread (void * arg)
{
    mqd_t mqDescriptor;
    fuelPressureData spfuelPressureData;

    mqDescriptor = mq_open(SENSOR_QUEUE, O_WRONLY);
    if (mqDescriptor == (mqd_t)-1)
    {
        perror ("Senosr mq open");
    }
    while (1)
    {
        spfuelPressureData.unPressureVal = sensorPressure_Read ();
        spfuelPressureData.unTime = time (NULL);

        if (mq_send (mqDescriptor, (char * )&spfuelPressureData, 
                    sizeof(spfuelPressureData),0) == -1)
        {
            perror ("mq_send");
        }
        sleep (1);
        
    }
    
}

//****************************** FUNCTION_HEADER ******************************* 
//Purpose : This function hardcode an arbitrary value for pressure and it is ma-
//          nipulated using rand() library function to get varying pressure val-
//          ue
//Inputs  : None
//Outputs : pressure value is calculated 
//Return  : unPressureVal - float value for pressure data
//Notes   : None
//****************************************************************************** 
static uint16_t sensorPressure_Read (void)
{
    static uint16_t unPressureVal = 95.0;
    unPressureVal += (rand() % 5);
    return unPressureVal;

}

// EOF