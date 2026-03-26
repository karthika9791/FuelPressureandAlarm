//*************************** FuelPressure&Alarm *******************************
//  Copyright (c) 2026 Trenser Technology Solutions 
//  All Rights Reserved 
//****************************************************************************** 
// 
// Summary : Header file with function prototypes for custom sensor operations.
// Note    : This module provides utilities to perform sensor initialization and
//           reading pressure value and shares the data via messagequeue to val- 
//           idate the pressure range
//
//****************************************************************************** 
#ifndef SENSOR_H
#define SENSOR_H

//******************************* Include Files ********************************
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <mqueue.h>
#include <time.h>

//******************************* Global Types ********************************* 
 
//***************************** Global Constants ******************************* 

//***************************** Global Variables ******************************* 

//**************************** Function Declarations ***************************
void * sensorThread(void * arg);

#endif // SENSOR_H_ 
// EOF
