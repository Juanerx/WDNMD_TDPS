#include "key.h"
#include "delay.h"

//L298N IO���ƿڳ�ʼ������ ����˸�
void KEY_Init(void)
{
    GPIO_InitTypeDef GPIO_Initure;

	__HAL_RCC_GPIOD_CLK_ENABLE();           //����GPIODʱ��
__HAL_RCC_GPIOC_CLK_ENABLE();             //����GPIOCʱ��
    GPIO_Initure.Pin=GPIO_PIN_0;            //PC0
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;      //���
    GPIO_Initure.Pull=GPIO_PULLUP;        //����
    GPIO_Initure.Speed=GPIO_SPEED_FREQ_VERY_HIGH;     //����
	 HAL_GPIO_Init(GPIOC,&GPIO_Initure);
	GPIO_Initure.Pin=GPIO_PIN_1;            //PC1
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;      //���
    GPIO_Initure.Pull=GPIO_PULLUP;        //����
    GPIO_Initure.Speed=GPIO_SPEED_FREQ_VERY_HIGH;     //����
	 HAL_GPIO_Init(GPIOC,&GPIO_Initure);
GPIO_Initure.Pin=GPIO_PIN_2;            //PC2
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;      //���
    GPIO_Initure.Pull=GPIO_PULLUP;        //����
    GPIO_Initure.Speed=GPIO_SPEED_FREQ_VERY_HIGH;     //����   
 HAL_GPIO_Init(GPIOC,&GPIO_Initure);	
    GPIO_Initure.Pin=GPIO_PIN_3;           //PC3
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;      //���
    GPIO_Initure.Pull=GPIO_PULLUP;          //����
    GPIO_Initure.Speed=GPIO_SPEED_FREQ_VERY_HIGH;     //����
	 HAL_GPIO_Init(GPIOC,&GPIO_Initure);
	 GPIO_Initure.Pin=GPIO_PIN_8;           //PD8
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;      //���
    GPIO_Initure.Pull=GPIO_PULLUP;          //����
    GPIO_Initure.Speed=GPIO_SPEED_FREQ_VERY_HIGH;     //����
	 HAL_GPIO_Init(GPIOD,&GPIO_Initure);
		 GPIO_Initure.Pin=GPIO_PIN_9;           //PD9
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;      //���
    GPIO_Initure.Pull=GPIO_PULLUP;          //����
    GPIO_Initure.Speed=GPIO_SPEED_FREQ_VERY_HIGH;     //����
    HAL_GPIO_Init(GPIOD,&GPIO_Initure);
	////////////////////////////////////////
		GPIO_Initure.Pin=GPIO_PIN_10;           //PD10
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;      //���
    GPIO_Initure.Pull=GPIO_PULLUP;          //����
    GPIO_Initure.Speed=GPIO_SPEED_FREQ_VERY_HIGH;     //����
	HAL_GPIO_Init(GPIOD,&GPIO_Initure);
		GPIO_Initure.Pin=GPIO_PIN_11;           //PD11
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;      //���
    GPIO_Initure.Pull=GPIO_PULLUP;          //����
    GPIO_Initure.Speed=GPIO_SPEED_FREQ_VERY_HIGH;     //����
		HAL_GPIO_Init(GPIOD,&GPIO_Initure);
}