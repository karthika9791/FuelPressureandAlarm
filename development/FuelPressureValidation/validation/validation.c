//**************************** FuelPressure&Alarm ****************************** 
//  Copyright (c) 2026 Trenser Technology Solutions 
//  All Rights Reserved 
//****************************************************************************** 
// 
// File    : validation.c
// Summary : File which contains functions for validating pressure value shared 
//           via message queue and if thepressure is out of range event signal 
//           is generated
// Note    : None
// Author  : Karthika V T
// Date    : 25-03-2026
// 
//******************************************************************************

//******************************* Include Files ********************************
#include "validation.h"
#include "main.h"

//******************************* Local Types **********************************

//***************************** Local Constants ********************************
#define MIN_PRESSURE 10.0f
#define MAX_PRESSURE 110.0f

//***************************** Local Variables ********************************
static pthread_t sensorThreadId;
static pthread_t valRxThreadId;
static pthread_t valProcThreadId;
static pthread_t alarmThreadId;

//****************************** Local Functions *******************************

//****************************** FUNCTION_HEADER ******************************* 
//Purpose : This function creates a message queue object and the pressure varia- 
//          ble reads value from Pressure_Read function. The incoming pressure
//          value is send to the validation process using mq_send.
//Inputs  : None
//Outputs : Created messagequeue and pressure data is send to queue 
//Return  : blReturnFlag - bool value based on execution
//Notes   : None
//****************************************************************************** 
bool validationFuelPressure (void)
{
    bool blReturnFlag = true;
    struct mq_attr attr;
    attr.mq_flags   = 0;
    attr.mq_maxmsg  = 5;
    attr.mq_msgsize = sizeof (fuelPressureData);
    attr.mq_curmsgs = 0;
    mq_unlink (SENSOR_QUEUE);
    mq_unlink (VALIDATION_QUEUE);

    if (mq_open (SENSOR_QUEUE, O_CREAT | O_RDWR, 0644, &attr) == -1)
    {
        perror ("mq_open sensor");
        blReturnFlag = false;
        exit (1);
    }

    if(mq_open (VALIDATION_QUEUE, O_CREAT | O_RDWR, 0644, &attr) == -1)
    {
        perror ("mq_open validation");
        blReturnFlag = false;
        exit (1);
    }
    
    pthread_create (&sensorThreadId, NULL, sensorThread, NULL);
    pthread_create (&valRxThreadId, NULL, validationRxThread, NULL);
    pthread_create (&alarmThreadId, NULL, alarmThread, NULL);
    pthread_create (&valProcThreadId, NULL, validationProcessThread, NULL);

    pthread_join (sensorThreadId, NULL);
    pthread_join (valRxThreadId, NULL);
    pthread_join (alarmThreadId, NULL);
    pthread_join (valProcThreadId, NULL);

    return blReturnFlag;
    
}

//****************************** FUNCTION_HEADER ******************************* 
//Purpose : This function hardcode receives fuel pressure value from the sensor
//          queue using mq_in descriptor to pass it to validation queue using 
//          mq_out descriptor
//Inputs  : None
//Outputs : data shared from sensor queue to validation queue
//Return  : None
//Notes   : None
//****************************************************************************** 
void * validationRxThread (void * arg)
{
    mqd_t mqSensorDescriptor, mqVldDescriptor;
    fuelPressureData spfuelPressureData;
    mqSensorDescriptor = mq_open (SENSOR_QUEUE,O_RDONLY);
    mqVldDescriptor = mq_open (VALIDATION_QUEUE, O_WRONLY);

    if (mqSensorDescriptor == -1 || mqVldDescriptor == -1)
    {
        perror ("Error validation receive");
        return NULL;
    }

    while (1)
    {
        if (mq_receive (mqSensorDescriptor, (char * )&spfuelPressureData, 
                        sizeof(spfuelPressureData),NULL) > 0)
        {
            mq_send (mqVldDescriptor, (char * )&spfuelPressureData, 
                        sizeof(spfuelPressureData),0);
        }
        
    }   
    
}

//****************************** FUNCTION_HEADER ******************************* 
//Purpose : This function opens the validation queue and inputs the pressure dat
//          a. It compares this data with the predefined threshold values and if
//          found out of range a signal is generated.
//Inputs  : None
//Outputs : Generated signal when out of range situation is occured
//Return  : None
//Notes   : None
//****************************************************************************** 
void * validationProcessThread (void * arg)
{
    mqd_t mqDescriptor;
    fuelPressureData spfuelPressureData;
    mqDescriptor = mq_open (VALIDATION_QUEUE,O_RDONLY);

    if (mqDescriptor == -1 )
    {
        perror ("Error validation process");
        return NULL;
    }

    while (1)
    {
        if (mq_receive (mqDescriptor, (char * )&spfuelPressureData, 
                        sizeof(spfuelPressureData),NULL) > 0)
        {
            if ((spfuelPressureData.unPressureVal < MIN_PRESSURE) || 
                 (spfuelPressureData.unPressureVal < MAX_PRESSURE))
            {
                pthread_kill (alarmThreadId, SIGUSR1);
            }
            
        }
        
    }   
    
}

// EOF