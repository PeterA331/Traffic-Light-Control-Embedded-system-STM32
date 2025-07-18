/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define USART_TX_Pin GPIO_PIN_2
#define USART_TX_GPIO_Port GPIOA
#define USART_RX_Pin GPIO_PIN_3
#define USART_RX_GPIO_Port GPIOA
#define LD2_Pin GPIO_PIN_5
#define LD2_GPIO_Port GPIOA
#define TL1_car_Pin_Pin GPIO_PIN_4
#define TL1_car_Pin_GPIO_Port GPIOC
#define TL1_car_Pin_EXTI_IRQn EXTI4_IRQn
#define LATCH_PIN_Pin GPIO_PIN_12
#define LATCH_PIN_GPIO_Port GPIOB
#define TL2_Car_Pin GPIO_PIN_13
#define TL2_Car_GPIO_Port GPIOB
#define TL2_Car_EXTI_IRQn EXTI15_10_IRQn
#define TL3_Car_Pin GPIO_PIN_14
#define TL3_Car_GPIO_Port GPIOB
#define TL3_Car_EXTI_IRQn EXTI15_10_IRQn
#define ENABLE_PIN_Pin GPIO_PIN_7
#define ENABLE_PIN_GPIO_Port GPIOC
#define RESET_PIN_Pin GPIO_PIN_9
#define RESET_PIN_GPIO_Port GPIOA
#define TL4_Car_Pin GPIO_PIN_10
#define TL4_Car_GPIO_Port GPIOA
#define TL4_Car_EXTI_IRQn EXTI15_10_IRQn
#define TMS_Pin GPIO_PIN_13
#define TMS_GPIO_Port GPIOA
#define TCK_Pin GPIO_PIN_14
#define TCK_GPIO_Port GPIOA
#define SW5_SW6_Pin GPIO_PIN_15
#define SW5_SW6_GPIO_Port GPIOA
#define SW5_SW6_EXTI_IRQn EXTI15_10_IRQn
#define SWO_Pin GPIO_PIN_3
#define SWO_GPIO_Port GPIOB
#define SW7_SW8_Pin GPIO_PIN_7
#define SW7_SW8_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
