//*************************** FuelPressure&Alarm *******************************
//  Copyright (c) 2026 Trenser Technology Solutions 
//  All Rights Reserved 
//****************************************************************************** 
// 
// Summary : Header file with function prototypes for validation operations.
// Note    : This module provides utilities to perform fuel pressure validation
//           It checks the incoming pressure data from the messagequeue and com-
//           pares it with the predefined pressure range. If it is out of range 
//           an event signal is generated and driven alarm module.
//
//****************************************************************************** 
#ifndef VALIDATION_H
#define VALIDATION_H

//******************************* Include Files ********************************
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <signal.h>
#include "sensor.h"
#include "alarm.h"

//******************************* Global Types ********************************* 
 
//***************************** Global Constants ******************************* 

//***************************** Global Variables ******************************* 

//**************************** Function Declarations ***************************
bool validationFuelPressure (void);
void * validationProcessThread (void * arg);
void * validationRxThread (void * arg);

#endif // VALIDATION_H_ 
// EOF
