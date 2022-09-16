#ifndef _MYIIC_H
#define _MYIIC_H
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F7������
//IIC��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2015/11/30
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	
//IO��������
#define SDA_IN()  {GPIOD->MODER&=~(3<<(13*2));GPIOD->MODER|=0<<13*2;}	//PD13����ģʽ
#define SDA_OUT() {GPIOD->MODER&=~(3<<(13*2));GPIOD->MODER|=1<<13*2;}   //PD13���ģʽ
//IO����
#define IIC_SCL(n)  (n?HAL_GPIO_WritePin(GPIOD,GPIO_PIN_12,GPIO_PIN_SET):HAL_GPIO_WritePin(GPIOD,GPIO_PIN_12,GPIO_PIN_RESET)) //SCL
#define IIC_SDA(n)  (n?HAL_GPIO_WritePin(GPIOD,GPIO_PIN_13,GPIO_PIN_SET):HAL_GPIO_WritePin(GPIOD,GPIO_PIN_13,GPIO_PIN_RESET)) //SDA
#define READ_SDA    HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_13)  //����SDA

//IIC���в�������
void IIC_Init(void);                //��ʼ��IIC��IO��				 
void IIC_Start(void);				//����IIC��ʼ�ź�
void IIC_Stop(void);	  			//����IICֹͣ�ź�
void IIC_Send_Byte(u8 txd);			//IIC����һ���ֽ�
u8 IIC_Read_Byte(unsigned char ack);//IIC��ȡһ���ֽ�
u8 IIC_Wait_Ack(void); 				//IIC�ȴ�ACK�ź�
void IIC_Ack(void);					//IIC����ACK�ź�
void IIC_NAck(void);				//IIC������ACK�ź�

void IIC_Write_One_Byte(u8 daddr,u8 addr,u8 data);
u8 IIC_Read_One_Byte(u8 daddr,u8 addr);	 
#endif

