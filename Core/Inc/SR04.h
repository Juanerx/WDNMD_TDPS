#ifndef __SR04_H
#define __SR04_H
#include "main.h"
#include "tim.h"
#include "stdio.h"

#define TRIG_1_H  HAL_GPIO_WritePin(US1_TRIG_GPIO_Port,US1_TRIG_Pin,GPIO_PIN_SET)
#define TRIG_1_L  HAL_GPIO_WritePin(US1_TRIG_GPIO_Port,US1_TRIG_Pin,GPIO_PIN_RESET)

//#define TRIG_2_H  HAL_GPIO_WritePin(US2_TRIG_GPIO_Port,US2_TRIG_Pin,GPIO_PIN_SET)
//#define TRIG_2_L  HAL_GPIO_WritePin(US2_TRIG_GPIO_Port,US2_TRIG_Pin,GPIO_PIN_RESET)

//#define TRIG_3_H  HAL_GPIO_WritePin(US3_TRIG_GPIO_Port,US3_TRIG_Pin,GPIO_PIN_SET)
//#define TRIG_3_L  HAL_GPIO_WritePin(US3_TRIG_GPIO_Port,US3_TRIG_Pin,GPIO_PIN_RESET)


//void delay_us(uint32_t us);
float SR04_GetData(void);

#endif
