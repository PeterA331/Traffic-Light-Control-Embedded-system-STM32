/**
******************************************************************************
@brief   Project, functions for Traffic lights-program
@file    Traffic_functions.h
@author  Mhnna Alatallah
@version 1.0
@date    16-December-2024
@brief   Functions and Variables declarations for program Traffic lights program task1
******************************************************************************/



#ifndef INC_TRAFFIC_FUNCTIONS_H_
#define INC_TRAFFIC_FUNCTIONS_H_

#include <stdint.h>
#include<stdbool.h>


/**********************************************/
extern uint8_t pattern1[3];
extern uint8_t pattern2[3];
extern uint8_t pattern3[3];
extern uint8_t pattern4[3];
extern uint8_t pattern5[3];
extern uint8_t pattern6[3];
extern uint8_t pattern7[3];
extern uint8_t pattern8[3];
extern uint8_t pattern9[3];

extern uint8_t i;

extern volatile uint8_t ped1_active;
extern volatile uint8_t car2_active;

/***********************************************/

void shiftRegisterWrite(uint8_t *data, uint8_t length);
void resetShiftRegisters(void);
void enableShiftRegisters(void);
void disableShiftRegisters(void);
//void Test_traffic_system(void);
//void Task1(void);
bool Pedstrain_Upper(void);
void EXTI4_IRQHandler(void);
void EXTI15_10_IRQHandler(void);
void Test_TL3_car_Pin_iterrupt(void);
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);
void Test_TL1_car_Pin_iterrupt(void);
void orangeDelay(void);
void walkingDelay (void);
void test_car_pedstrain(void);
void toggleFreq (void);
void toggle_pattern1 (void);
void clearShiftRegistersViaSPI(void);

#endif
