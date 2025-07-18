
/**
******************************************************************************
@brief   Project, functions for Traffic lights-program
@file    Traffic_functions.c
@author  Peter Alatallah
@version 1.0
@date    16-December-2024
@brief   Functions for program Traffic lights program task1
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
@brief Pattern array for traffic light configurations.
Each pattern represents the states of multiple traffic lights controlled by shift registers.
*/
uint8_t pattern1[3] = { 0b11111111, 0b11111111, 0b11111111 }; // Pattern 1: All lights on
uint8_t pattern2[3] = { 0b00000000, 0b00000000, 0b00000000 }; // Pattern 2: All lights off
uint8_t pattern3[3] = { 0b11111111, 0b00000000, 0b10101010 }; // Pattern 3
uint8_t pattern4[3] = { 0b00101000, 0b00000010, 0b00111100 }; // Pattern 4
uint8_t pattern5[3] = { 0b00100000, 0b00001100, 0b00000000 }; // Pattern 5: Green light
uint8_t pattern6[3] = { 0b00100000, 0b00101100, 0b00000000 }; // Pattern 6: Green toggle
uint8_t pattern7[3] = { 0b00100000, 0b00001100, 0b00000000 }; // Pattern 7: Red light
uint8_t pattern8[3] = { 0b00010000, 0b00001010, 0b00000000 }; // Pattern 8: Orange delay
uint8_t pattern9[3] = { 0b00001000, 0b00010001, 0b00000000 }; // Pattern 9: Walking delay

/**
@brief Counter variable used in loops for toggling patterns.
*/
uint8_t i;

/**
@brief Volatile variables for button press states.
`ped1_active` indicates the pedestrian button state.
`car2_active` indicates the car button state.
*/
volatile uint8_t ped1_active = 0;
volatile uint8_t car2_active = 0;

/**
@brief Toggles the traffic lights between patterns 6 and 7 for a visual effect.
@param void
@return void
*/
void toggleFreq(void) {
    for (i = 0; i < 4; i++) {
        shiftRegisterWrite(pattern6, 3);
        HAL_Delay(200);
        shiftRegisterWrite(pattern7, 3);
        HAL_Delay(200);
    }
    i = 0;
}

/**
@brief Toggles the traffic lights between patterns 1 and 2.
@param void
@return void
*/
void toggle_pattern1(void) {
    for (i = 0; i < 4; i++) {
        shiftRegisterWrite(pattern1, 3); // Pattern 1: All lights on
        HAL_Delay(200);
        shiftRegisterWrite(pattern2, 3); // Pattern 2: All lights off
        HAL_Delay(200);
    }
    i = 0;
}

/**
@brief Applies a delay with the orange light pattern.
@param void
@return void
*/
void orangeDelay(void) {
    shiftRegisterWrite(pattern8, 3); // Pattern 8: Orange delay
    HAL_Delay(3000);
}

/**
@brief Applies a delay with the walking light pattern.
@param void
@return void
*/
void walkingDelay(void) {
    shiftRegisterWrite(pattern9, 3); // Pattern 9: Walking delay
    HAL_Delay(3000);
}

/**
@brief Writes a pattern to the shift register to control traffic lights.
@param data Pointer to the data array to be written
@param length Length of the data array
@return void
*/
void shiftRegisterWrite(uint8_t *data, uint8_t length) {
    HAL_GPIO_WritePin(LATCH_PIN_GPIO_Port, LATCH_PIN_Pin, GPIO_PIN_RESET); // Pull LATCH low
    HAL_SPI_Transmit(&hspi3, data, length, PATTERN_DELAY);                // Transmit data via SPI
    HAL_Delay(200);
    HAL_GPIO_WritePin(LATCH_PIN_GPIO_Port, LATCH_PIN_Pin, GPIO_PIN_SET);  // Pull LATCH high
}

/**
@brief Resets the shift registers by toggling the reset pin.
@param void
@return void
*/
void resetShiftRegisters(void) {
    HAL_GPIO_WritePin(GPIOA, RESET_PIN_Pin, GPIO_PIN_RESET); // Pull Reset Pin low
    HAL_Delay(1);
    HAL_GPIO_WritePin(GPIOA, RESET_PIN_Pin, GPIO_PIN_SET);   // Pull Reset Pin high
}

/**
@brief Enables the shift registers by activating the enable pin.
@param void
@return void
*/
void enableShiftRegisters(void) {
    HAL_GPIO_WritePin(ENABLE_PIN_GPIO_Port, ENABLE_PIN_Pin, GPIO_PIN_RESET); // Enable active (low)
}

/**
@brief Disables the shift registers by deactivating the enable pin.
@param void
@return void
*/
void disableShiftRegisters(void) {
    HAL_GPIO_WritePin(ENABLE_PIN_GPIO_Port, ENABLE_PIN_Pin, GPIO_PIN_SET); // Enable inactive (high)
}

/**
@brief Clears the shift registers by sending zero values through SPI.
@param void
@return void
*/
void clearShiftRegistersViaSPI(void) {
    uint8_t clearData[3] = {0x00, 0x00, 0x00}; // 3 bytes of zeros
    HAL_GPIO_WritePin(LATCH_PIN_GPIO_Port, LATCH_PIN_Pin, GPIO_PIN_RESET); // Pull LATCH low
    HAL_SPI_Transmit(&hspi3, clearData, 3, HAL_MAX_DELAY);                 // Send zeros via SPI
    HAL_GPIO_WritePin(LATCH_PIN_GPIO_Port, LATCH_PIN_Pin, GPIO_PIN_SET);  // Pull LATCH high
}

/**
@brief Checks if the pedestrian button is pressed.
@param void
@return bool True if the pedestrian button is pressed, false otherwise.
*/
bool Pedstrain_Upper(void) {
    return HAL_GPIO_ReadPin(SW7_SW8_GPIO_Port, SW7_SW8_Pin) == GPIO_PIN_RESET;
}

/**
@brief Interrupt handler for EXTI line 4.
Checks and clears the interrupt flag for the TL1_car pin.
@param void
@return void
*/
void EXTI4_IRQHandler(void) {
    if (__HAL_GPIO_EXTI_GET_IT(TL1_car_Pin_Pin) != RESET) {
        __HAL_GPIO_EXTI_CLEAR_IT(TL1_car_Pin_Pin);
    }
}

/**
@brief Interrupt handler for EXTI lines 9 to 5.
Checks and clears the interrupt flag for the pedestrian button (SW7_SW8).
@param void
@return void
*/
void EXTI9_5_IRQHandler(void) {
    if (__HAL_GPIO_EXTI_GET_IT(SW7_SW8_Pin) != RESET) {
        __HAL_GPIO_EXTI_CLEAR_IT(SW7_SW8_Pin);
    }
}

/**
@brief Interrupt handler for EXTI lines 15 to 10.
Checks and clears the interrupt flags for TL3_Car, TL4_Car, TL2_Car, and SW5_SW6.
@param void
@return void
*/
void EXTI15_10_IRQHandler(void) {
    if (__HAL_GPIO_EXTI_GET_IT(TL3_Car_Pin) != RESET) {
        __HAL_GPIO_EXTI_CLEAR_IT(TL3_Car_Pin);
    }
    if (__HAL_GPIO_EXTI_GET_IT(TL4_Car_Pin | TL2_Car_Pin) != RESET) {
        __HAL_GPIO_EXTI_CLEAR_IT(TL4_Car_Pin | TL2_Car_Pin);
    }
    if (__HAL_GPIO_EXTI_GET_IT(SW5_SW6_Pin) != RESET) {
        __HAL_GPIO_EXTI_CLEAR_IT(SW5_SW6_Pin);
    }
}
