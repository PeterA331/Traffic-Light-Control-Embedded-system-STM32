
/**
******************************************************************************
@brief   Project, functions for Traffic lights-program
@file   Test_traffic.c
@author  Peter Alatallah
@version 1.0
@date    16-December-2024
@brief   Test functions for program Traffic lights program task1
******************************************************************************/

#include <stdint.h>
#include<stdbool.h>
#include "Test_traffic.h"
#include"gpio.h"
#include "usart.h"
#include "stm32l4xx_hal_spi.h"
#include "spi.h"
#include "stm32l4xx_it.h"
#include "Traffic_functions.h"

#define PATTERN_DELAY 5000 // 5 seconds delay between patterns

/**
@brief Test the traffic light system by invoking the Task1 state machine.
@param void
@return void
*/
void Test_traffic_system(void) {
   // Task1();
	toggleFreq();
}
