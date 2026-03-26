//*************************** FuelPressure&Alarm *******************************
//  Copyright (c) 2026 Trenser Technology Solutions 
//  All Rights Reserved 
//****************************************************************************** 
// 
// File    : main.c
// Summary : Entry point to the user function 
// Note    : None
// Author  : Karthika V T
// Date    : 25-03-2026
// 
//******************************************************************************

//******************************* Include Files ********************************
#include "validation.h"

//******************************* Local Types ********************************** 

//***************************** Local Constants ******************************** 

//***************************** Local Variables ******************************** 

//****************************** Local Functions *******************************

//****************************** FUNCTION_HEADER ******************************* 
//Purpose : It calls the function that implements the validation of fuel and 
//          pressure check logic
//Inputs  : None
//Outputs : Calls user intertface function to perform pressure check
//Return  : returns 0 
//Notes   : None
//****************************************************************************** 
int main ()
{	
	if (!validationFuelPressure ())
	{
		printf ("Program failed\n");
		return 0;
	}
	return 0;
}

// EOF
