#ifndef _TIMER_H
#define _TIMER_H
#include "sys.h"
///////////////////////////////////////////////////////////////////////////////
extern TIM_HandleTypeDef TIM15_Handler;      //��ʱ��15PWM��� 
extern TIM_HandleTypeDef TIM12_Handler;      //��ʱ��12PWM���
extern TIM_OC_InitTypeDef TIM12_CH1Handler; 	//��ʱ��12ͨ��1���
extern TIM_OC_InitTypeDef TIM12_CH2Handler; 	//��ʱ��12ͨ��2���
extern TIM_OC_InitTypeDef TIM15_CH1Handler; 	//��ʱ��15ͨ��1���
extern TIM_OC_InitTypeDef TIM15_CH2Handler; 	//��ʱ��15ͨ��2���

void TIM12_Init(u16 arr,u16 psc);    		//��ʱ����ʼ��
void TIM15_Init(u16 arr,u16 psc); 
void TIM_PWM_Init(u16 arr,u16 psc);
void TIM_SetTIM3Compare1(u32 compare1);
void TIM_SetTIM3Compare2(u32 compare2);
void TIM_SetTIM3Compare3(u32 compare3);
void TIM_SetTIM3Compare4(u32 compare4);

#endif

