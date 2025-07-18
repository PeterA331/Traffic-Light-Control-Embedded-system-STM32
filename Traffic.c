/**
******************************************************************************
@brief   Project, functions for Traffic lights-program
@file    Traffic.c
@author  Peter Alatallah
@version 1.0
@date    16-December-2024
@brief   Program Traffic lights program task1
******************************************************************************/
#include "main.h"
#include "spi.h"
#include "usart.h"
#include "gpio.h"
#include "Test_traffic.h"
#include "Traffic_functions.h"
#include "Traffic.h"


#include <string.h>
#include <stdio.h>


typedef enum {
    Start,
    Toggle_Indicator_Orangedelay, // Transition phase (Orange delay)
    Ped_Crossing                  // Pedestrian crossing
} states;

static states State, NextState;

/**
@brief Main state machine controlling the traffic lights.
Switches between states based on input conditions.
@param void
@return void
*/
void Task1(void) {
    while (1) {
        ped1_active = HAL_GPIO_ReadPin(SW7_SW8_GPIO_Port, SW7_SW8_Pin) == GPIO_PIN_RESET ? 1 : 0;
        State = NextState;

        switch (State) {
            case Start:
                shiftRegisterWrite(pattern5, 3); // Pattern 5: Green light
                if (ped1_active == 1) {
                    NextState = Toggle_Indicator_Orangedelay;
                } else {
                    NextState = Start;
                }
                break;

            case Toggle_Indicator_Orangedelay:
                toggleFreq();
                orangeDelay();
                HAL_Delay(3000);
                NextState = Ped_Crossing;
                break;

            case Ped_Crossing:
                walkingDelay();
                orangeDelay();
                NextState = Start;
                break;

            default:
                break;
        }
    }
}

