/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "key.h"
#include "motor.h"
#include "timer.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include "DS1302.h"
#include <stdio.h>
#include <string.h>
#include "sys.h"
#include "delay.h"
#include "mpu.h"
#include "mpu9250.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"
#include "SR04.h"
#include "ball_release.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MPU_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MPU Configuration--------------------------------------------------------*/
  MPU_Config();

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();
/////////////////////////////////////////motor ���
	int motor_cnt=0;
	KEY_Init();
    TIM_PWM_Init(500-1,200-1);     		//200M/200=1M�ļ���Ƶ�ʣ��Զ���װ��Ϊ500����ôPWMƵ��Ϊ1M/500=2kHZ
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM3_Init();
  MX_TIM4_Init();
  MX_TIM12_Init();
  MX_TIM15_Init();
  MX_UART7_Init();
  MX_UART8_Init();
  MX_USART1_UART_Init();
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */
  
  extern uint8_t UART8_RX_BUF[800];     // �������ⲿת��ռ�
	uint8_t shape = 0;                    // ʶ�𵽵�ͼ��
	uint8_t len;
  uint8_t flag[1]={0};                  // OpenMV����ģʽ��־λ��0����Ѳ�ߣ�1������״ʶ��2����ֹͣ����
  
  float pitch,roll,yaw,yaw_init,yaw_now;// ŷ����
  short aacx,aacy,aacz;	        		    // ���ٶȴ�����ԭʼ����
  short gyrox,gyroy,gyroz;        	    // ������ԭʼ���� 
  short temp;		                	      // �¶�
	
	float distance;                       // �ϰ������
	uint8_t state;												// SR04����״̬��0����trig��1����echo
	
  Cache_Enable();                		    // ��L1-Cache
  delay_init(400);						          // ��ʱ��ʼ��
  MPU9250_Init();             			    // ��ʼ��MPU9250
	
	ball_release_0();                     // �����λ
	HAL_UART_Receive_IT(&huart8, (uint8_t *)aRxBuffer, RXBUFFERSIZE);             // ��UART�ж�
	
	DS1302_WriteTime();                   // д��ʱ��
  
  HAL_Delay (5000);                     // �ϵ�ǰ��ʱ5�룬�ȳ��ź�
  
  /* ģ���Լ� */
  
//  while(mpu_dmp_init())         
//  {   
//		printf("%d��\n",mpu_dmp_init());
//  }
//  printf("dmp_init ok!\n");
	
  /* ģ���Լ���� */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
		
		/* ֱ��ǰ��ʶ����״ */
		Motor_Straight(200,500);                 // ����ֱ���ٶȺ�ʱ�䣬ǰ��ʶ���
		Motor_Stop(1000);                        // ����ͣ��ʱ�䣬��ʼʶ��
		
		/* ʶ��ͼ�� */
		flag [0] = 1;                                                                 // flag��Ϊ��״ʶ��ģʽ  
		HAL_UART_Transmit(&huart8,flag,1,1000);                                       // ����OpenMVģʽָ��
		HAL_UART_Receive_IT(&huart8, (uint8_t *)aRxBuffer, RXBUFFERSIZE);             // ��UART�ж�
				   
		len = USART_RX_STA&0x3fff;                                    // �õ��˴ν��յ������ݳ���
		shape = USART_RX_BUF[0];                                      // ��ȡ��״
//	printf("\r\nInformation from OpenMV:\r\n");
//	HAL_UART_Transmit(&huart1,(uint8_t*)USART_RX_BUF,len,1000);	  // ���ͽ��յ�������
//	while(__HAL_UART_GET_FLAG(&huart1,UART_FLAG_TC)!=SET);		    // �ȴ����ͽ���
//	printf("\r\n\r\n");//���뻻��
		USART_RX_STA=0;                                               // ���ý���״̬���

		
		while (shape == 0x30){                                           // û�м�⵽����
			shape = USART_RX_BUF [0];                                   // �ٴζ�ȡ��״
			USART_RX_STA=0;                                             // ���ý���״̬���
		}
		
		flag[0] = 2;                                                  // ֹͣOpenMV
		HAL_UART_Transmit(&huart8,flag,1,1000);                       // ����OpenMVģʽָ��
		
		/* ����ͼ����ʻ */
		if (shape == 1){                                              // ʶ��������
			Motor_Left_90(1000); 																		    // ��ת45��
			Motor_Stop(1000);                                           // ͣ��
			Motor_Straight(300,1000);		                                // ֱ�е������α�־��
			Motor_Stop(1000);			                                      // ͣ��
			Motor_Right_90(1000);																				// ��ת90��
			Motor_Stop(1000);																						// ͣ��
			Motor_Straight(300,1000);																		// ֱ�е������α�־��
			Motor_Stop(1000);																						// ͣ��
		}
		else if (shape == 2){                                         // ʶ��Բ��
			Motor_Right_90(1000);                                       // ��ת45��
			Motor_Stop(1000);                                           // ͣ��
			Motor_Straight(300,1000);			                              // ֱ�е�Բ�α�־��
			Motor_Stop(1000);			                                      // ͣ��
			Motor_Left_90(1000);																				// ��ת90��
		  Motor_Stop(1000); 																					// ͣ��
			Motor_Straight(300,1000);																		// ֱ�е������α�־��
			Motor_Stop(1000);																						// ͣ��
		}
		else {                                                        // ʶ��������
			Motor_Straight(300,1000);																		// ֱ�е������α�־��
			Motor_Stop(1000);																						// ͣ��
		}
		
		/* ��ʻ��Ͷ�� */
		///��Ҫʵ�ؿ���ô�����߹�ȥ���˴�������ʱȱʧ��		
		/* Ͷ�� */
			ball_release_180();                                           // ��ת���
			HAL_Delay(2000);                                              // �ȴ�Ͷ��
			ball_release_0();                                             // �����λ
			
		/* ��ʻ��planter */
		////��Ҫʵ�ؿ���ô�����߹�ȥ�յ㣨�˴�������ʱȱʧ��
			/* ʱ��ģ�鿪ʼͨ�� */
		DS1302_GetTime();
		
		char Teamname[30];
		sprintf(Teamname,"%s%s","Team name: ","WDNMD\n");
		char Member[160];
		sprintf(Member,"%s%s%s%s%s%s%s%s%s%s%s","Members: ","Guo Junfu, ","Chen Lei, ","Fu Yufei, ","Huang Ruiwen, ","Wang Xiao, ","Jiang Hongyu, ","Lei Kaiyi, ","Xu Linyun, ","Bai Helin, ","Wu Shuangen\n");
		char Theday[30];
		sprintf(Theday,"%s%d%s%d%s%d","Today is ",TimeData.year,"/",TimeData.month,"/",TimeData.day);
		char Thetime[50];
		sprintf(Thetime,"%s%d%s%d%s%d%s",". The time is ",TimeData.hour,":",TimeData.minute,":",TimeData.second,"\n\n");
		char Info [270];
		sprintf(Info,"%s%s%s%s",Teamname,Member,Theday,Thetime);
		//char *b = "/";
		//strcat(a, b);
		//strcat(a, month);
	  HAL_UART_Transmit(&huart7, (uint8_t *)Info, 270, 0xffff);
		HAL_Delay(1000);
			
			/* �ߵ��յ� */
			
			/* ֹͣ���������ѭ�� */
			while(1){
				HAL_Delay(1000);
			}
			//////!!!!!!!!!����Ĵ�����Ҫȫ��ע�͵���Ҫ�þͷ����棩
	  //����Ϊ������Ҫʹ�õĵ���ģ��Ĵ��룬ǰ��ĺ�����������ǵģ�Ӧ��Ŀǰ�ò��ˣ�����openmv���Ժͳ������ĺ���

			/* ��������ȡ�ϰ������ */
			distance = SR04_GetData();
			while ((int)distance==0){
				distance = SR04_GetData();
			}

		/* Openmv���� */
		printf("Start testing");
		flag [0] = 0;
		HAL_UART_Transmit(&huart8,flag,1,1000);

		while(1){
			if(USART_RX_STA&0x8000)
			{					   
				len=USART_RX_STA&0x3fff;//�õ��˴ν��յ������ݳ���
				printf("\r\nInformation from OpenMV:\r\n");
				HAL_UART_Transmit(&huart1,(uint8_t*)USART_RX_BUF,len,1000);	//���ͽ��յ�������
				while(__HAL_UART_GET_FLAG(&huart1,UART_FLAG_TC)!=SET);		//�ȴ����ͽ���
				printf("\r\n\r\n");//���뻻��
				USART_RX_STA=0;
			}
		}
		
		flag [0] = 1;
		HAL_UART_Transmit(&huart8,flag,1,1000);
		HAL_Delay(10000);

		flag [0] = 2;
		HAL_UART_Transmit(&huart8,flag,1,1000);
		HAL_Delay(10000);
	  
  }
  /* USER CODE END 3 *///////////////////////////////////////////////////////////////////////////main��������
}
//////������CUBE�Զ����õģ����ù�
/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Supply configuration update enable
  */
  HAL_PWREx_ConfigSupply(PWR_LDO_SUPPLY);

  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  while(!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 5;
  RCC_OscInitStruct.PLL.PLLN = 160;
  RCC_OscInitStruct.PLL.PLLP = 2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1VCIRANGE_2;
  RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1VCOWIDE;
  RCC_OscInitStruct.PLL.PLLFRACN = 0;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2
                              |RCC_CLOCKTYPE_D3PCLK1|RCC_CLOCKTYPE_D1PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV2;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV2;
  RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV4;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/* MPU Configuration */

void MPU_Config(void)
{
  MPU_Region_InitTypeDef MPU_InitStruct = {0};

  /* Disables the MPU */
  HAL_MPU_Disable();

  /** Initializes and configures the Region and the memory to be protected
  */
  MPU_InitStruct.Enable = MPU_REGION_ENABLE;
  MPU_InitStruct.Number = MPU_REGION_NUMBER0;
  MPU_InitStruct.BaseAddress = 0x0;
  MPU_InitStruct.Size = MPU_REGION_SIZE_4GB;
  MPU_InitStruct.SubRegionDisable = 0x87;
  MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL0;
  MPU_InitStruct.AccessPermission = MPU_REGION_NO_ACCESS;
  MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_DISABLE;
  MPU_InitStruct.IsShareable = MPU_ACCESS_SHAREABLE;
  MPU_InitStruct.IsCacheable = MPU_ACCESS_NOT_CACHEABLE;
  MPU_InitStruct.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;

  HAL_MPU_ConfigRegion(&MPU_InitStruct);
  /* Enables the MPU */
  HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);

}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
