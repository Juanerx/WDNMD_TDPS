#include "DS1302.h"
#include "delay.h"
//#include "delay.h"
//#include "usart.h"
/*
DS1302�ӿ�:
	GPIOA_5 ->DS1302_CLK
	GPIOA_6 ->DS1302_RST
	GPIOA_7 ->DS1302_DAT
*/
#include <stdio.h>
struct TIMEData TimeData;
//DS1302��ַ����
#define DS1302_SEC_ADDR           0x80		//�����ݵ�ַ
#define DS1302_MIN_ADDR           0x82		//�����ݵ�ַ
#define DS1302_HOUR_ADDR          0x84		//ʱ���ݵ�ַ
#define DS1302_DAY_ADDR           0x86		//�����ݵ�ַ
#define DS1302_MONTH_ADDR         0x88		//�����ݵ�ַ
#define DS1302_WEEK_ADDR          0x8a		//�������ݵ�ַ
#define DS1302_YEAR_ADDR          0x8c		//�����ݵ�ַ
#define DS1302_CONTROL_ADDR       0x8e		//�������ݵ�ַ
#define DS1302_CHARGER_ADDR       0x90 		//��繦�ܵ�ַ			 
#define DS1302_CLKBURST_ADDR      0xbe      //���崮�Ĵ���
 
//��ʼʱ�䶨��
uint8_t time_buf[8] = {0x20,0x22,0x05,0x03,0x12,0x46,0x00,0x02};//��ʼʱ��2022��5��3��12��46��00�� ���ڶ�
uint8_t readtime[15];//��ǰʱ��
uint8_t sec_buf=0;  //�뻺��
uint8_t sec_flag=0; //���־λ

//GPIO��ʼ���ṹ��
GPIO_InitTypeDef GPIO_InitStruct;

//���ģʽ
void DS1302_OutPut_Mode(void)
{
	GPIO_InitStruct.Pin = DS1302_OUT_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;//GPIO_PULLUP
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(DS1302_OUT_GPIO, &GPIO_InitStruct); 

}

//����ģʽ
void DS1302_InPut_Mode(void)
{
	GPIO_InitStruct.Pin = DS1302_IN_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;//��������,DS1302_DAT pin has an internal 40k�� (typ) pulldown resistor to ground.
    GPIO_InitStruct.Pull = GPIO_NOPULL;//GPIO_PULLUP;//GPIO_NOPULL
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;//GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(DS1302_IN_GPIO, &GPIO_InitStruct);
}
	
 
////DS1302��ʼ������
//void DS1302_Init(void) 
//{
//	/*1.GPIOAʱ��*/
////	RCC->APB2ENR |= 1<<2;
//	/*2. ����GPIOA_5/6/7ģʽ*/
//	GPIOA->CRL &= 0X000FFFFF;
//	GPIOA->CRL |= 0X33300000;
//	GPIOA->ODR |=1<<6;
//	//printf("DS1302_Init OK!\n");
// 
//}
//��DS1302д��һ�ֽ�����
void DS1302_WriteByte(uint8_t addr,uint8_t data) 
{
	uint8_t i;
	HAL_GPIO_WritePin (DS1302_RST_GPIO, DS1302_RST_PIN, GPIO_PIN_RESET); //��ֹ���ݴ��� ��������������Ҫ
	HAL_GPIO_WritePin (DS1302_CLK_GPIO, DS1302_CLK_PIN, GPIO_PIN_RESET); //ȷ��д����ǰSCLKΪ�͵�ƽ
	HAL_GPIO_WritePin (DS1302_RST_GPIO, DS1302_RST_PIN, GPIO_PIN_SET);	 //����DS1302����	
	DS1302_OutPut_Mode();
	addr=addr&0xFE;  //���λ���㣬�Ĵ���0λΪ0ʱд��Ϊ1ʱ��
	for(i=0;i<8;i++) //д��Ŀ���ַ��addr
	{
		if (addr&0x01) HAL_GPIO_WritePin (DS1302_OUT_GPIO, DS1302_OUT_PIN, GPIO_PIN_SET);
		else HAL_GPIO_WritePin (DS1302_OUT_GPIO, DS1302_OUT_PIN, GPIO_PIN_RESET);
		HAL_GPIO_WritePin (DS1302_CLK_GPIO, DS1302_CLK_PIN, GPIO_PIN_SET); //ʱ��������д������
		delay_us(2);
		HAL_GPIO_WritePin (DS1302_CLK_GPIO, DS1302_CLK_PIN, GPIO_PIN_RESET);
		delay_us(2);
		addr=addr>>1;
	}	
	for (i=0;i<8;i++) //д�����ݣ�data
	{
		if(data&0x01) HAL_GPIO_WritePin (DS1302_OUT_GPIO, DS1302_OUT_PIN, GPIO_PIN_SET);
		else HAL_GPIO_WritePin (DS1302_OUT_GPIO, DS1302_OUT_PIN, GPIO_PIN_RESET);
		HAL_GPIO_WritePin (DS1302_CLK_GPIO, DS1302_CLK_PIN, GPIO_PIN_SET);    //ʱ��������д������
		delay_us(2);
		HAL_GPIO_WritePin (DS1302_CLK_GPIO, DS1302_CLK_PIN, GPIO_PIN_RESET);
		delay_us(2);
		data = data >> 1;
	}
	HAL_GPIO_WritePin (DS1302_CLK_GPIO, DS1302_CLK_PIN, GPIO_PIN_SET);    // ��ʱ�ӵ�ƽ���ڸߵ�ƽ״̬ ��������֪״̬
	HAL_GPIO_WritePin (DS1302_RST_GPIO, DS1302_RST_PIN, GPIO_PIN_RESET);	//ֹͣDS1302����
}
 
//��DS1302����һ�ֽ�����
uint8_t DS1302_ReadByte(uint8_t addr) 
{
	uint8_t i,temp;	
	HAL_GPIO_WritePin (DS1302_RST_GPIO, DS1302_RST_PIN, GPIO_PIN_RESET); //��������Ҫ
	HAL_GPIO_WritePin (DS1302_CLK_GPIO, DS1302_CLK_PIN, GPIO_PIN_RESET); //�Ƚ�SCLK�õ͵�ƽ,ȷ��д����ǰSCLK������
	HAL_GPIO_WritePin (DS1302_RST_GPIO, DS1302_RST_PIN, GPIO_PIN_SET);   //����DS1302����
	DS1302_OutPut_Mode();
	//д��Ŀ���ַ��addr
	addr=addr|0x01; //���λ�øߣ��Ĵ���0λΪ0ʱд��Ϊ1ʱ��
	for(i=0;i<8;i++) 
	{
		if (addr&0x01) HAL_GPIO_WritePin (DS1302_OUT_GPIO, DS1302_OUT_PIN, GPIO_PIN_SET);
		else HAL_GPIO_WritePin (DS1302_OUT_GPIO, DS1302_OUT_PIN, GPIO_PIN_RESET);
		HAL_GPIO_WritePin (DS1302_CLK_GPIO, DS1302_CLK_PIN, GPIO_PIN_SET); //д����
		delay_us(2);
		HAL_GPIO_WritePin (DS1302_CLK_GPIO, DS1302_CLK_PIN, GPIO_PIN_RESET);
		delay_us(2);
		addr = addr >> 1;
	}	
	//��DS1302�������ݣ�temp
	DS1302_InPut_Mode();
	for(i=0;i<8;i++)
	{
		temp=temp>>1;
		if (HAL_GPIO_ReadPin (DS1302_IN_GPIO, DS1302_IN_PIN)) temp|=0x80;
		else temp&=0x7F;
		HAL_GPIO_WritePin (DS1302_CLK_GPIO, DS1302_CLK_PIN, GPIO_PIN_SET);
		delay_us(2);
		HAL_GPIO_WritePin (DS1302_CLK_GPIO, DS1302_CLK_PIN, GPIO_PIN_RESET);
		delay_us(2);
	}	
	HAL_GPIO_WritePin (DS1302_CLK_GPIO, DS1302_CLK_PIN, GPIO_PIN_SET);    //��ʱ�ӵ�ƽ������֪״̬
	HAL_GPIO_WritePin (DS1302_RST_GPIO, DS1302_RST_PIN, GPIO_PIN_RESET);	//ֹͣDS1302����
	return temp;
}
//��DS1302д��ʱ������,����ʱ��У׼�޸�
void DS1302_WriteTime(void) 
{
	DS1302_WriteByte(DS1302_CONTROL_ADDR,0x00);       //�ر�д���� 
	DS1302_WriteByte(DS1302_SEC_ADDR,0x80);           //��ͣʱ�� 
	//DS1302_WriteByte(DS1302_CHARGER_ADDR,0xa9);     //������ 
	DS1302_WriteByte(DS1302_YEAR_ADDR,time_buf[1]);   //�� 
	DS1302_WriteByte(DS1302_MONTH_ADDR,time_buf[2]);  //�� 
	DS1302_WriteByte(DS1302_DAY_ADDR,time_buf[3]);    //�� 
	DS1302_WriteByte(DS1302_HOUR_ADDR,time_buf[4]);   //ʱ 
	DS1302_WriteByte(DS1302_MIN_ADDR,time_buf[5]);    //��
	DS1302_WriteByte(DS1302_SEC_ADDR,time_buf[6]);    //��
	DS1302_WriteByte(DS1302_WEEK_ADDR,time_buf[7]);	  //�� 
	DS1302_WriteByte(DS1302_CHARGER_ADDR,0xA5);//�򿪳�繦�� ѡ��2K�����緽ʽ
	DS1302_WriteByte(DS1302_CONTROL_ADDR,0x80);//��д����     
}
//��DS1302����ʱ������
void DS1302_ReadTime(void)  
{
	time_buf[1]=DS1302_ReadByte(DS1302_YEAR_ADDR);          //�� 
	time_buf[2]=DS1302_ReadByte(DS1302_MONTH_ADDR);         //�� 
	time_buf[3]=DS1302_ReadByte(DS1302_DAY_ADDR);           //�� 
	time_buf[4]=DS1302_ReadByte(DS1302_HOUR_ADDR);          //ʱ 
	time_buf[5]=DS1302_ReadByte(DS1302_MIN_ADDR);           //�� 
	time_buf[6]=(DS1302_ReadByte(DS1302_SEC_ADDR))&0x7f;    //�룬������ĵ�7λ�����ⳬ��59
	time_buf[7]=DS1302_ReadByte(DS1302_WEEK_ADDR);          //�� 	
}
 
//������
void DS1302_GetTime(void)
{ 
    DS1302_ReadTime(); //��ȡʱ��
    TimeData.year=(time_buf[0]>>4)*1000+(time_buf[0]&0x0F)*100+(time_buf[1]>>4)*10+(time_buf[1]&0x0F); //�������
    TimeData.month=(time_buf[2]>>4)*10+(time_buf[2]&0x0F);  //�����·�
    TimeData.day=(time_buf[3]>>4)*10+(time_buf[3]&0x0F);    //��������
    TimeData.hour=(time_buf[4]>>4)*10+(time_buf[4]&0x0F);   //����Сʱ
    TimeData.minute=(time_buf[5]>>4)*10+(time_buf[5]&0x0F); //�������
    TimeData.second=(time_buf[6]>>4)*10+(time_buf[6]&0x0F); //��������
    TimeData.week=(time_buf[7]&0x0F);                       //��������
  //printf("ʱ��:%d-%d-%d %d:%d:%d %d \n",TimeData.year,TimeData.month,TimeData.day,TimeData.hour,TimeData.minute,TimeData.second,TimeData.week);																												
}
