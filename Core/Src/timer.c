#include "timer.h"
 //�ĸ�ͨ�����PWM
TIM_HandleTypeDef TIM12_Handler;//��ʱ����� 
TIM_HandleTypeDef TIM15_Handler;//��ʱ�����
TIM_OC_InitTypeDef TIM12_CH1Handler;     //��ʱ��12ͨ��1���
TIM_OC_InitTypeDef TIM12_CH2Handler;     //��ʱ��12ͨ��2���
TIM_OC_InitTypeDef TIM15_CH1Handler;     //��ʱ��15ͨ��1���
TIM_OC_InitTypeDef TIM15_CH2Handler;     //��ʱ��15ͨ��2���


//ͨ�ö�ʱ��1215�жϳ�ʼ��,��ʱ��12/15��APB1�ϣ�APB1�Ķ�ʱ��ʱ��Ϊ200MHz
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��
//��ʱ�����ʱ����㷽��:Tout=((arr+1)*(psc+1))/Ft us.
//Ft=��ʱ������Ƶ��,��λ:Mhz
//����ʹ�õ��Ƕ�ʱ��12/15!(��ʱ��12/15����APB1�ϣ�ʱ��ΪHCLK/2)
void TIM12_Init(u16 arr,u16 psc)
{  
    TIM12_Handler.Instance=TIM12;                          //ͨ�ö�ʱ��12
    TIM12_Handler.Init.Prescaler=psc;                     //��Ƶ
    TIM12_Handler.Init.CounterMode=TIM_COUNTERMODE_UP;    //���ϼ�����
    TIM12_Handler.Init.Period=arr;                        //�Զ�װ��ֵ
    TIM12_Handler.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;//ʱ�ӷ�Ƶ����
    HAL_TIM_Base_Init(&TIM12_Handler);
    
    HAL_TIM_Base_Start_IT(&TIM12_Handler); //ʹ�ܶ�ʱ��12�Ͷ�ʱ��12�����жϣ�TIM_IT_UPDATE    
}
void TIM15_Init(u16 arr,u16 psc)
{  
    TIM15_Handler.Instance=TIM15;                          //ͨ�ö�ʱ��15
    TIM15_Handler.Init.Prescaler=psc;                     //��Ƶ
    TIM15_Handler.Init.CounterMode=TIM_COUNTERMODE_UP;    //���ϼ�����
    TIM15_Handler.Init.Period=arr;                        //�Զ�װ��ֵ
    TIM15_Handler.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;//ʱ�ӷ�Ƶ����
    HAL_TIM_Base_Init(&TIM15_Handler);
    
    HAL_TIM_Base_Start_IT(&TIM15_Handler); //ʹ�ܶ�ʱ��15�Ͷ�ʱ��15�����жϣ�TIM_IT_UPDATE    
}

//TIM12/15 PWM���ֳ�ʼ�� 
//PWM�����ʼ��
//arr���Զ���װֵ
//psc��ʱ��Ԥ��Ƶ��
void TIM_PWM_Init(u16 arr,u16 psc)
{ 
    TIM15_Handler.Instance=TIM15;            //��ʱ��15
    TIM15_Handler.Init.Prescaler=psc;       //��ʱ����Ƶ
    TIM15_Handler.Init.CounterMode=TIM_COUNTERMODE_UP;//���ϼ���ģʽ
    TIM15_Handler.Init.Period=arr;          //�Զ���װ��ֵ
    TIM15_Handler.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;
    HAL_TIM_PWM_Init(&TIM15_Handler);       //��ʼ��PWM
	TIM12_Handler.Instance=TIM12;            //��ʱ��12
    TIM12_Handler.Init.Prescaler=psc;       //��ʱ����Ƶ
    TIM12_Handler.Init.CounterMode=TIM_COUNTERMODE_UP;//���ϼ���ģʽ
    TIM12_Handler.Init.Period=arr;          //�Զ���װ��ֵ
    TIM12_Handler.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;
    HAL_TIM_PWM_Init(&TIM12_Handler);       //��ʼ��PWM
    
    TIM15_CH1Handler.OCMode=TIM_OCMODE_PWM1; //ģʽѡ��PWM1
    TIM15_CH1Handler.Pulse=arr/2;            //���ñȽ�ֵ,��ֵ����ȷ��ռ�ձȣ�
	  TIM15_CH2Handler.OCMode=TIM_OCMODE_PWM1; //ģʽѡ��PWM1
    TIM15_CH2Handler.Pulse=arr/2;            
	  TIM12_CH1Handler.OCMode=TIM_OCMODE_PWM1; //ģʽѡ��PWM1
    TIM12_CH1Handler.Pulse=arr/2;            
	  TIM12_CH2Handler.OCMode=TIM_OCMODE_PWM1; //ģʽѡ��PWM1
    TIM12_CH2Handler.Pulse=arr/2;            
                                            //Ĭ�ϱȽ�ֵΪ�Զ���װ��ֵ��һ��,��ռ�ձ�Ϊ50%
    TIM15_CH1Handler.OCPolarity=TIM_OCPOLARITY_LOW; //����Ƚϼ���Ϊ��
TIM15_CH2Handler.OCPolarity=TIM_OCPOLARITY_LOW; //����Ƚϼ���Ϊ��
TIM12_CH1Handler.OCPolarity=TIM_OCPOLARITY_LOW; //����Ƚϼ���Ϊ��
TIM12_CH2Handler.OCPolarity=TIM_OCPOLARITY_LOW; //����Ƚϼ���Ϊ��	
    
	HAL_TIM_PWM_ConfigChannel(&TIM12_Handler,&TIM12_CH1Handler,TIM_CHANNEL_1);//����TIM12ͨ��1
	HAL_TIM_PWM_ConfigChannel(&TIM12_Handler,&TIM12_CH2Handler,TIM_CHANNEL_2);//����TIM12ͨ��2
	HAL_TIM_PWM_ConfigChannel(&TIM15_Handler,&TIM15_CH1Handler,TIM_CHANNEL_1);//����TIM15ͨ��1
	HAL_TIM_PWM_ConfigChannel(&TIM15_Handler,&TIM15_CH2Handler,TIM_CHANNEL_2);//����TIM15ͨ��2
    HAL_TIM_PWM_Start(&TIM12_Handler,TIM_CHANNEL_1);//����PWMͨ��1
		 HAL_TIM_PWM_Start(&TIM12_Handler,TIM_CHANNEL_2);//����PWMͨ��2
		  HAL_TIM_PWM_Start(&TIM15_Handler,TIM_CHANNEL_1);//����PWMͨ��1
			 HAL_TIM_PWM_Start(&TIM15_Handler,TIM_CHANNEL_2);//����PWMͨ��2
}
//��ʱ���ײ�������ʱ��ʹ�ܣ���������
//�˺����ᱻHAL_TIM_PWM_Init()����
//htim:��ʱ�����

void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim)
{
    GPIO_InitTypeDef GPIO_Initure;
	__HAL_RCC_TIM12_CLK_ENABLE();			//ʹ�ܶ�ʱ��12
	__HAL_RCC_TIM15_CLK_ENABLE();			//ʹ�ܶ�ʱ��15
    __HAL_RCC_GPIOE_CLK_ENABLE();			//����GPIOB&Eʱ��
	__HAL_RCC_GPIOB_CLK_ENABLE();
	
    GPIO_Initure.Pin=GPIO_PIN_14;           	//PB14
    GPIO_Initure.Mode=GPIO_MODE_AF_PP;  	//�����������
    GPIO_Initure.Pull=GPIO_PULLUP;          //����
    GPIO_Initure.Speed=GPIO_SPEED_FREQ_VERY_HIGH;     //����
	GPIO_Initure.Alternate=GPIO_AF2_TIM12;	//����ΪTIM12_CH1
    HAL_GPIO_Init(GPIOB,&GPIO_Initure);
	GPIO_Initure.Pin=GPIO_PIN_15;           	//PB15
    GPIO_Initure.Mode=GPIO_MODE_AF_PP;  	//�����������
    GPIO_Initure.Pull=GPIO_PULLUP;          //����
    GPIO_Initure.Speed=GPIO_SPEED_FREQ_VERY_HIGH;     //����
	GPIO_Initure.Alternate=GPIO_AF2_TIM12;	//����ΪTIM12_CH2
	HAL_GPIO_Init(GPIOB,&GPIO_Initure);
////////////////////////////////////////////////////////////	
	GPIO_Initure.Pin=GPIO_PIN_5;           	//PE5
    GPIO_Initure.Mode=GPIO_MODE_AF_PP;  	//�����������
    GPIO_Initure.Pull=GPIO_PULLUP;          //����
    GPIO_Initure.Speed=GPIO_SPEED_FREQ_VERY_HIGH;     //����
	GPIO_Initure.Alternate=GPIO_AF4_TIM15;	//����ΪTIM15_CH1
	HAL_GPIO_Init(GPIOE,&GPIO_Initure);
	GPIO_Initure.Pin=GPIO_PIN_6;           	//PE6
    GPIO_Initure.Mode=GPIO_MODE_AF_PP;  	//�����������
    GPIO_Initure.Pull=GPIO_PULLUP;          //����
    GPIO_Initure.Speed=GPIO_SPEED_FREQ_VERY_HIGH;     //����
	GPIO_Initure.Alternate=GPIO_AF4_TIM15;	//����ΪTIM15_CH2
		HAL_GPIO_Init(GPIOE,&GPIO_Initure);
}

//��ʱ���ײ�����������ʱ�ӣ������ж����ȼ�
//�˺����ᱻHAL_TIM_Base_Init()��������
void HAL_TIM_Base_MspInit_motor(TIM_HandleTypeDef *htim)
{
    if(htim->Instance==TIM12)
	{
		__HAL_RCC_TIM12_CLK_ENABLE();            //ʹ��TIM12ʱ��
		HAL_NVIC_SetPriority(TIM8_BRK_TIM12_IRQn,1,3);    //�����ж����ȼ�����ռ���ȼ�1�������ȼ�3
		HAL_NVIC_EnableIRQ(TIM8_BRK_TIM12_IRQn);          //����ITM12�ж�   
	}  
	if(htim->Instance==TIM15)
	{
		__HAL_RCC_TIM15_CLK_ENABLE();            //ʹ��TIM15ʱ��
		HAL_NVIC_SetPriority(TIM15_IRQn,1,3);    //�����ж����ȼ�����ռ���ȼ�1�������ȼ�3
		HAL_NVIC_EnableIRQ(TIM15_IRQn);          //����ITM15�ж�   
	}  
}

//��ʱ��3�жϷ�����
void TIM3_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&TIM12_Handler);
	 HAL_TIM_IRQHandler(&TIM15_Handler);
}

//��ʱ��3�жϷ���������
void HAL_TIM_PeriodElapsedCallback_motor(TIM_HandleTypeDef *htim)
{
  //  if(htim==(&TIM3_Handler))
    //{
      //  LED1_Toggle;        //LED0��ת
//return 0;
	//}
}

//����TIMͨ��1234��ռ�ձ�
//compare:�Ƚ�ֵ
void TIM_SetTIM3Compare1(u32 compare1)
{
	TIM15->CCR1=compare1; 
}
void TIM_SetTIM3Compare2(u32 compare2)
{
	TIM15->CCR2=compare2; 
}
void TIM_SetTIM3Compare3(u32 compare3)
{
	TIM12->CCR1=compare3; 
}
void TIM_SetTIM3Compare4(u32 compare4)
{
	TIM12->CCR2=compare4; 
}
