#include "timer.h"
 //四个通道输出PWM
TIM_HandleTypeDef TIM12_Handler;//定时器句柄 
TIM_HandleTypeDef TIM15_Handler;//定时器句柄
TIM_OC_InitTypeDef TIM12_CH1Handler;     //定时器12通道1句柄
TIM_OC_InitTypeDef TIM12_CH2Handler;     //定时器12通道2句柄
TIM_OC_InitTypeDef TIM15_CH1Handler;     //定时器15通道1句柄
TIM_OC_InitTypeDef TIM15_CH2Handler;     //定时器15通道2句柄


//通用定时器1215中断初始化,定时器12/15在APB1上，APB1的定时器时钟为200MHz
//arr：自动重装值。
//psc：时钟预分频数
//定时器溢出时间计算方法:Tout=((arr+1)*(psc+1))/Ft us.
//Ft=定时器工作频率,单位:Mhz
//这里使用的是定时器12/15!(定时器12/15挂在APB1上，时钟为HCLK/2)
void TIM12_Init(u16 arr,u16 psc)
{  
    TIM12_Handler.Instance=TIM12;                          //通用定时器12
    TIM12_Handler.Init.Prescaler=psc;                     //分频
    TIM12_Handler.Init.CounterMode=TIM_COUNTERMODE_UP;    //向上计数器
    TIM12_Handler.Init.Period=arr;                        //自动装载值
    TIM12_Handler.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;//时钟分频因子
    HAL_TIM_Base_Init(&TIM12_Handler);
    
    HAL_TIM_Base_Start_IT(&TIM12_Handler); //使能定时器12和定时器12更新中断：TIM_IT_UPDATE    
}
void TIM15_Init(u16 arr,u16 psc)
{  
    TIM15_Handler.Instance=TIM15;                          //通用定时器15
    TIM15_Handler.Init.Prescaler=psc;                     //分频
    TIM15_Handler.Init.CounterMode=TIM_COUNTERMODE_UP;    //向上计数器
    TIM15_Handler.Init.Period=arr;                        //自动装载值
    TIM15_Handler.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;//时钟分频因子
    HAL_TIM_Base_Init(&TIM15_Handler);
    
    HAL_TIM_Base_Start_IT(&TIM15_Handler); //使能定时器15和定时器15更新中断：TIM_IT_UPDATE    
}

//TIM12/15 PWM部分初始化 
//PWM输出初始化
//arr：自动重装值
//psc：时钟预分频数
void TIM_PWM_Init(u16 arr,u16 psc)
{ 
    TIM15_Handler.Instance=TIM15;            //定时器15
    TIM15_Handler.Init.Prescaler=psc;       //定时器分频
    TIM15_Handler.Init.CounterMode=TIM_COUNTERMODE_UP;//向上计数模式
    TIM15_Handler.Init.Period=arr;          //自动重装载值
    TIM15_Handler.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;
    HAL_TIM_PWM_Init(&TIM15_Handler);       //初始化PWM
	TIM12_Handler.Instance=TIM12;            //定时器12
    TIM12_Handler.Init.Prescaler=psc;       //定时器分频
    TIM12_Handler.Init.CounterMode=TIM_COUNTERMODE_UP;//向上计数模式
    TIM12_Handler.Init.Period=arr;          //自动重装载值
    TIM12_Handler.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;
    HAL_TIM_PWM_Init(&TIM12_Handler);       //初始化PWM
    
    TIM15_CH1Handler.OCMode=TIM_OCMODE_PWM1; //模式选择PWM1
    TIM15_CH1Handler.Pulse=arr/2;            //设置比较值,此值用来确定占空比，
	  TIM15_CH2Handler.OCMode=TIM_OCMODE_PWM1; //模式选择PWM1
    TIM15_CH2Handler.Pulse=arr/2;            
	  TIM12_CH1Handler.OCMode=TIM_OCMODE_PWM1; //模式选择PWM1
    TIM12_CH1Handler.Pulse=arr/2;            
	  TIM12_CH2Handler.OCMode=TIM_OCMODE_PWM1; //模式选择PWM1
    TIM12_CH2Handler.Pulse=arr/2;            
                                            //默认比较值为自动重装载值的一半,即占空比为50%
    TIM15_CH1Handler.OCPolarity=TIM_OCPOLARITY_LOW; //输出比较极性为低
TIM15_CH2Handler.OCPolarity=TIM_OCPOLARITY_LOW; //输出比较极性为低
TIM12_CH1Handler.OCPolarity=TIM_OCPOLARITY_LOW; //输出比较极性为低
TIM12_CH2Handler.OCPolarity=TIM_OCPOLARITY_LOW; //输出比较极性为低	
    
	HAL_TIM_PWM_ConfigChannel(&TIM12_Handler,&TIM12_CH1Handler,TIM_CHANNEL_1);//配置TIM12通道1
	HAL_TIM_PWM_ConfigChannel(&TIM12_Handler,&TIM12_CH2Handler,TIM_CHANNEL_2);//配置TIM12通道2
	HAL_TIM_PWM_ConfigChannel(&TIM15_Handler,&TIM15_CH1Handler,TIM_CHANNEL_1);//配置TIM15通道1
	HAL_TIM_PWM_ConfigChannel(&TIM15_Handler,&TIM15_CH2Handler,TIM_CHANNEL_2);//配置TIM15通道2
    HAL_TIM_PWM_Start(&TIM12_Handler,TIM_CHANNEL_1);//开启PWM通道1
		 HAL_TIM_PWM_Start(&TIM12_Handler,TIM_CHANNEL_2);//开启PWM通道2
		  HAL_TIM_PWM_Start(&TIM15_Handler,TIM_CHANNEL_1);//开启PWM通道1
			 HAL_TIM_PWM_Start(&TIM15_Handler,TIM_CHANNEL_2);//开启PWM通道2
}
//定时器底层驱动，时钟使能，引脚配置
//此函数会被HAL_TIM_PWM_Init()调用
//htim:定时器句柄

void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim)
{
    GPIO_InitTypeDef GPIO_Initure;
	__HAL_RCC_TIM12_CLK_ENABLE();			//使能定时器12
	__HAL_RCC_TIM15_CLK_ENABLE();			//使能定时器15
    __HAL_RCC_GPIOE_CLK_ENABLE();			//开启GPIOB&E时钟
	__HAL_RCC_GPIOB_CLK_ENABLE();
	
    GPIO_Initure.Pin=GPIO_PIN_14;           	//PB14
    GPIO_Initure.Mode=GPIO_MODE_AF_PP;  	//复用推完输出
    GPIO_Initure.Pull=GPIO_PULLUP;          //上拉
    GPIO_Initure.Speed=GPIO_SPEED_FREQ_VERY_HIGH;     //高速
	GPIO_Initure.Alternate=GPIO_AF2_TIM12;	//复用为TIM12_CH1
    HAL_GPIO_Init(GPIOB,&GPIO_Initure);
	GPIO_Initure.Pin=GPIO_PIN_15;           	//PB15
    GPIO_Initure.Mode=GPIO_MODE_AF_PP;  	//复用推完输出
    GPIO_Initure.Pull=GPIO_PULLUP;          //上拉
    GPIO_Initure.Speed=GPIO_SPEED_FREQ_VERY_HIGH;     //高速
	GPIO_Initure.Alternate=GPIO_AF2_TIM12;	//复用为TIM12_CH2
	HAL_GPIO_Init(GPIOB,&GPIO_Initure);
////////////////////////////////////////////////////////////	
	GPIO_Initure.Pin=GPIO_PIN_5;           	//PE5
    GPIO_Initure.Mode=GPIO_MODE_AF_PP;  	//复用推完输出
    GPIO_Initure.Pull=GPIO_PULLUP;          //上拉
    GPIO_Initure.Speed=GPIO_SPEED_FREQ_VERY_HIGH;     //高速
	GPIO_Initure.Alternate=GPIO_AF4_TIM15;	//复用为TIM15_CH1
	HAL_GPIO_Init(GPIOE,&GPIO_Initure);
	GPIO_Initure.Pin=GPIO_PIN_6;           	//PE6
    GPIO_Initure.Mode=GPIO_MODE_AF_PP;  	//复用推完输出
    GPIO_Initure.Pull=GPIO_PULLUP;          //上拉
    GPIO_Initure.Speed=GPIO_SPEED_FREQ_VERY_HIGH;     //高速
	GPIO_Initure.Alternate=GPIO_AF4_TIM15;	//复用为TIM15_CH2
		HAL_GPIO_Init(GPIOE,&GPIO_Initure);
}

//定时器底册驱动，开启时钟，设置中断优先级
//此函数会被HAL_TIM_Base_Init()函数调用
void HAL_TIM_Base_MspInit_motor(TIM_HandleTypeDef *htim)
{
    if(htim->Instance==TIM12)
	{
		__HAL_RCC_TIM12_CLK_ENABLE();            //使能TIM12时钟
		HAL_NVIC_SetPriority(TIM8_BRK_TIM12_IRQn,1,3);    //设置中断优先级，抢占优先级1，子优先级3
		HAL_NVIC_EnableIRQ(TIM8_BRK_TIM12_IRQn);          //开启ITM12中断   
	}  
	if(htim->Instance==TIM15)
	{
		__HAL_RCC_TIM15_CLK_ENABLE();            //使能TIM15时钟
		HAL_NVIC_SetPriority(TIM15_IRQn,1,3);    //设置中断优先级，抢占优先级1，子优先级3
		HAL_NVIC_EnableIRQ(TIM15_IRQn);          //开启ITM15中断   
	}  
}

//定时器3中断服务函数
void TIM3_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&TIM12_Handler);
	 HAL_TIM_IRQHandler(&TIM15_Handler);
}

//定时器3中断服务函数调用
void HAL_TIM_PeriodElapsedCallback_motor(TIM_HandleTypeDef *htim)
{
  //  if(htim==(&TIM3_Handler))
    //{
      //  LED1_Toggle;        //LED0反转
//return 0;
	//}
}

//设置TIM通道1234的占空比
//compare:比较值
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
