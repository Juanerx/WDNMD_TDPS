//
// Created by FUYUFEI 2022/3/8
//

#ifndef TDPS_PROJECT_MOTOR_H
#define TDPS_PROJECT_MOTOR_H

////���е������־���������ʱ������Ϳ���Щ���򿪵������
#include "stm32h7xx_hal.h"
//LED �˿ڶ���
#define IN1_FRONT(n) (n?HAL_GPIO_WritePin(GPIOC,GPIO_PIN_0,GPIO_PIN_SET):HAL_GPIO_WritePin(GPIOC,GPIO_PIN_0,GPIO_PIN_RESET))
#define IN2_FRONT(n) (n?HAL_GPIO_WritePin(GPIOC,GPIO_PIN_1,GPIO_PIN_SET):HAL_GPIO_WritePin(GPIOC,GPIO_PIN_1,GPIO_PIN_RESET))
#define IN3_FRONT(n) (n?HAL_GPIO_WritePin(GPIOC,GPIO_PIN_2,GPIO_PIN_SET):HAL_GPIO_WritePin(GPIOC,GPIO_PIN_2,GPIO_PIN_RESET))
#define IN4_FRONT(n) (n?HAL_GPIO_WritePin(GPIOC,GPIO_PIN_3,GPIO_PIN_SET):HAL_GPIO_WritePin(GPIOC,GPIO_PIN_3,GPIO_PIN_RESET))
#define IN1_BEHIND(n) (n?HAL_GPIO_WritePin(GPIOD,GPIO_PIN_8,GPIO_PIN_SET):HAL_GPIO_WritePin(GPIOD,GPIO_PIN_8,GPIO_PIN_RESET))
#define IN2_BEHIND(n) (n?HAL_GPIO_WritePin(GPIOD,GPIO_PIN_9,GPIO_PIN_SET):HAL_GPIO_WritePin(GPIOD,GPIO_PIN_9,GPIO_PIN_RESET))
#define IN3_BEHIND(n) (n?HAL_GPIO_WritePin(GPIOD,GPIO_PIN_10,GPIO_PIN_SET):HAL_GPIO_WritePin(GPIOD,GPIO_PIN_10,GPIO_PIN_RESET))
#define IN4_BEHIND(n) (n?HAL_GPIO_WritePin(GPIOD,GPIO_PIN_11,GPIO_PIN_SET):HAL_GPIO_WritePin(GPIOD,GPIO_PIN_11,GPIO_PIN_RESET))
#define GO 150             //ռ�ձ�����
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

extern int left_pwm; //����pwm
extern int right_pwm; //����pwm
extern int direction; //����


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
/////////////////////////////////////////////////////////////////////���º�����δ�õ�
void Motor_SPIN1(int MOTOR_OPENMV_FIGURE1,int ANGLE_LA,int ANGLE_RB);///��һ��������ת������ת��ֱ��
void Motor_SPIN2(int MOTOR_OPENMV_FIGURE2);///�ڶ�����ֱ�У���ֱ��
void Motor_SPIN3(int MOTOR_OPENMV_FIGURE3,int ANGLE_RA,int ANGLE_LB);///������������ת������ת��ֱ��
//// patio2 figure route123

void Motor_TRACK_SLIGHT_LEFT(int MOTOR_OPENMV_LEFT);

void Motor_TRACK_SLIGHT_Right(int MOTOR_OPENMV_RIGHT);
//// openmvת��
void Motor_Stop(int MOTOR_STOP);

/////PID�㷨
void Motor_PID(float GYRO_INPUT);

#endif  //TDPS_PROJECT_MOTOR_H