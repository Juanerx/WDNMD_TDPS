/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
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
#include "stm32h7xx_hal.h"

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
#define PWM_M1_Pin GPIO_PIN_5
#define PWM_M1_GPIO_Port GPIOE
#define PWM_M2_Pin GPIO_PIN_6
#define PWM_M2_GPIO_Port GPIOE
#define US3_TRIG_Pin GPIO_PIN_13
#define US3_TRIG_GPIO_Port GPIOC
#define IN2_M1_Pin GPIO_PIN_0
#define IN2_M1_GPIO_Port GPIOC
#define IN1_M1_Pin GPIO_PIN_1
#define IN1_M1_GPIO_Port GPIOC
#define IN2_M2_Pin GPIO_PIN_2
#define IN2_M2_GPIO_Port GPIOC
#define IN1_M2_Pin GPIO_PIN_3
#define IN1_M2_GPIO_Port GPIOC
#define US1_TRIG_Pin GPIO_PIN_0
#define US1_TRIG_GPIO_Port GPIOA
#define US1_ECHO_Pin GPIO_PIN_1
#define US1_ECHO_GPIO_Port GPIOA
#define US2_ECHO_Pin GPIO_PIN_2
#define US2_ECHO_GPIO_Port GPIOA
#define US3_ECHO_Pin GPIO_PIN_3
#define US3_ECHO_GPIO_Port GPIOA
#define US2_TRIG_Pin GPIO_PIN_4
#define US2_TRIG_GPIO_Port GPIOA
#define DS_CLK_Pin GPIO_PIN_5
#define DS_CLK_GPIO_Port GPIOA
#define DS_RST_Pin GPIO_PIN_6
#define DS_RST_GPIO_Port GPIOA
#define DS_DATA_Pin GPIO_PIN_7
#define DS_DATA_GPIO_Port GPIOA
#define HC12_SET_Pin GPIO_PIN_2
#define HC12_SET_GPIO_Port GPIOB
#define HC12_TX_Pin GPIO_PIN_7
#define HC12_TX_GPIO_Port GPIOE
#define HC12_RX_Pin GPIO_PIN_8
#define HC12_RX_GPIO_Port GPIOE
#define PWM_M4_Pin GPIO_PIN_14
#define PWM_M4_GPIO_Port GPIOB
#define PWM_M3_Pin GPIO_PIN_15
#define PWM_M3_GPIO_Port GPIOB
#define IN2_M3_Pin GPIO_PIN_8
#define IN2_M3_GPIO_Port GPIOD
#define IN1_M3_Pin GPIO_PIN_9
#define IN1_M3_GPIO_Port GPIOD
#define IN2_M4_Pin GPIO_PIN_10
#define IN2_M4_GPIO_Port GPIOD
#define IN1_M4_Pin GPIO_PIN_11
#define IN1_M4_GPIO_Port GPIOD
#define MPU_SCL_Pin GPIO_PIN_12
#define MPU_SCL_GPIO_Port GPIOD
#define MPU_SDA_Pin GPIO_PIN_13
#define MPU_SDA_GPIO_Port GPIOD
#define PWM_Sterring_Pin GPIO_PIN_5
#define PWM_Sterring_GPIO_Port GPIOB
#define Opmv_TX_Pin GPIO_PIN_0
#define Opmv_TX_GPIO_Port GPIOE
#define Opmv_RX_Pin GPIO_PIN_1
#define Opmv_RX_GPIO_Port GPIOE
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
