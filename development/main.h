//*************************** FuelPressure&Alarm *******************************
//  Copyright (c) 2026 Trenser Technology Solutions 
//  All Rights Reserved 
//****************************************************************************** 
// 
// Summary : Header file with common data structures that is to be passed betwe-
//           en functions
// Note    : This module decalres the common data structures used between each 
//           modules. It consists of structure variable for pressure data and 
//           maximum and minimum pressure values 
//
//****************************************************************************** 
#ifndef MAIN_H
#define MAIN_H

//******************************* Include Files ********************************
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <mqueue.h>
#include <unistd.h>

//******************************* Global Types ********************************* 
typedef struct
{
    uint16_t unPressureVal;
    uint32_t unTime;
}fuelPressureData;
 
//***************************** Global Constants ******************************* 
#define SENSOR_QUEUE "/sensorqueue"
#define VALIDATION_QUEUE "/validationqueue"

//***************************** Global Variables ******************************* 

//**************************** Function Declarations ***************************
bool validationFuelPressure(void);  

#endif // MAIN_H_ 
// EOF
