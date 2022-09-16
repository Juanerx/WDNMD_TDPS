#include "ball_release.h"
void ball_release_180(void)
{
	uint16_t pwmVal=25; //define a variable pwmValue
	HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_2); //Open PWM wave input capture channel
	__HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_2,pwmVal);
	HAL_Delay(200);
}

void ball_release_0(void)
{
	uint16_t pwmVal=5; //define a variable pwmValue
	HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_2); //Open PWM wave input capture channel
	__HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_2,pwmVal);
	HAL_Delay(200);
}
