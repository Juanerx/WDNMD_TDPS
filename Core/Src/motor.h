//
// Created by FUYUFEI 2022/3/8
//

#ifndef TDPS_PROJECT_MOTOR_H
#define TDPS_PROJECT_MOTOR_H

////所有的输入标志都在这里，到时候输入就靠这些来打开电机函数
#include "stm32h7xx_hal.h"
//LED 端口定义
#define IN1_FRONT(n) (n?HAL_GPIO_WritePin(GPIOC,GPIO_PIN_0,GPIO_PIN_SET):HAL_GPIO_WritePin(GPIOC,GPIO_PIN_0,GPIO_PIN_RESET))
#define IN2_FRONT(n) (n?HAL_GPIO_WritePin(GPIOC,GPIO_PIN_1,GPIO_PIN_SET):HAL_GPIO_WritePin(GPIOC,GPIO_PIN_1,GPIO_PIN_RESET))
#define IN3_FRONT(n) (n?HAL_GPIO_WritePin(GPIOC,GPIO_PIN_2,GPIO_PIN_SET):HAL_GPIO_WritePin(GPIOC,GPIO_PIN_2,GPIO_PIN_RESET))
#define IN4_FRONT(n) (n?HAL_GPIO_WritePin(GPIOC,GPIO_PIN_3,GPIO_PIN_SET):HAL_GPIO_WritePin(GPIOC,GPIO_PIN_3,GPIO_PIN_RESET))
#define IN1_BEHIND(n) (n?HAL_GPIO_WritePin(GPIOD,GPIO_PIN_8,GPIO_PIN_SET):HAL_GPIO_WritePin(GPIOD,GPIO_PIN_8,GPIO_PIN_RESET))
#define IN2_BEHIND(n) (n?HAL_GPIO_WritePin(GPIOD,GPIO_PIN_9,GPIO_PIN_SET):HAL_GPIO_WritePin(GPIOD,GPIO_PIN_9,GPIO_PIN_RESET))
#define IN3_BEHIND(n) (n?HAL_GPIO_WritePin(GPIOD,GPIO_PIN_10,GPIO_PIN_SET):HAL_GPIO_WritePin(GPIOD,GPIO_PIN_10,GPIO_PIN_RESET))
#define IN4_BEHIND(n) (n?HAL_GPIO_WritePin(GPIOD,GPIO_PIN_11,GPIO_PIN_SET):HAL_GPIO_WritePin(GPIOD,GPIO_PIN_11,GPIO_PIN_RESET))
#define GO 150             //占空比设置
#define SLOW 250
#define FAST 100
//#define KP 1
//#define KI 1
//#define KD 1
#define STRAIGHT 0
#define LEFT 1
#define RIGHT 2
#define BACK 3
#define STOP 4

extern int left_pwm; //左轮pwm
extern int right_pwm; //右轮pwm
extern int direction; //方向


void Motor_Init(int MOTOR_START);
////initial start
void mapping(uint8_t* USART_RX_BUF_int1,int *left_pwm,int *right_pwm,int *direction);
void Motor_LineTracking(int *left_pwm,int *right_pwm,int *direction);
void motor_direction(int direction);
//// straight line 
void Motor_Straight(int speed,int duration);
void Motor_Left_90(int duration);
void Motor_Right_90(int duration);
void testing(void);
/////////////////////////////////////////////////////////////////////以下函数暂未用到
void Motor_SPIN1(int MOTOR_OPENMV_FIGURE1,int ANGLE_LA,int ANGLE_RB);///第一条线向左转再向右转回直线
void Motor_SPIN2(int MOTOR_OPENMV_FIGURE2);///第二条线直行，再直行
void Motor_SPIN3(int MOTOR_OPENMV_FIGURE3,int ANGLE_RA,int ANGLE_LB);///第三条线先右转，再左转回直线
//// patio2 figure route123

void Motor_TRACK_SLIGHT_LEFT(int MOTOR_OPENMV_LEFT);

void Motor_TRACK_SLIGHT_Right(int MOTOR_OPENMV_RIGHT);
//// openmv转向
void Motor_Stop(int MOTOR_STOP);

/////PID算法
void Motor_PID(float GYRO_INPUT);

#endif  //TDPS_PROJECT_MOTOR_H