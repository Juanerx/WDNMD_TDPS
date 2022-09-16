#ifndef _TIMER_H
#define _TIMER_H
#include "sys.h"
///////////////////////////////////////////////////////////////////////////////
extern TIM_HandleTypeDef TIM15_Handler;      //定时器15PWM句柄 
extern TIM_HandleTypeDef TIM12_Handler;      //定时器12PWM句柄
extern TIM_OC_InitTypeDef TIM12_CH1Handler; 	//定时器12通道1句柄
extern TIM_OC_InitTypeDef TIM12_CH2Handler; 	//定时器12通道2句柄
extern TIM_OC_InitTypeDef TIM15_CH1Handler; 	//定时器15通道1句柄
extern TIM_OC_InitTypeDef TIM15_CH2Handler; 	//定时器15通道2句柄

void TIM12_Init(u16 arr,u16 psc);    		//定时器初始化
void TIM15_Init(u16 arr,u16 psc); 
void TIM_PWM_Init(u16 arr,u16 psc);
void TIM_SetTIM3Compare1(u32 compare1);
void TIM_SetTIM3Compare2(u32 compare2);
void TIM_SetTIM3Compare3(u32 compare3);
void TIM_SetTIM3Compare4(u32 compare4);

#endif

