#ifndef __DS18B20_H__
#define __DS18B20_H__

#include "main.h"
#include "usart.h"

//DS1302引脚定义,可根据实际情况自行修改端口定义
//#define DS1302_OutPut_Mode() {GPIOA->MODER &= 0xFFFF7FFF;GPIOA->MODER |= 0x00004000;}
//#define DS1302_InPut_Mode()  {GPIOA->MODER &= 0xFFFF3FFF;}
 
#define DS1302_IN_GPIO  GPIOA
#define DS1302_OUT_GPIO GPIOA
#define DS1302_RST_GPIO GPIOA
#define DS1302_CLK_GPIO GPIOA

#define DS1302_IN_PIN  GPIO_PIN_7
#define DS1302_OUT_PIN GPIO_PIN_7
#define DS1302_RST_PIN GPIO_PIN_6
#define DS1302_CLK_PIN GPIO_PIN_5

struct TIMEData
{
	uint16_t year;
	uint8_t  month;
	uint8_t  day;
	uint8_t  hour;
	uint8_t  minute;
	uint8_t  second;
	uint8_t  week;
};
extern struct TIMEData TimeData;
extern uint8_t readtime[15];
void DS1302_Init(void);
void DS1302_WriteByte(uint8_t addr,uint8_t data);
uint8_t   DS1302_ReadByte(uint8_t addr);
void DS1302_WriteTime(void);
void DS1302_ReadTime(void);
void DS1302_GetTime(void);
void DS1302_OutPut_Mode(void);
void DS1302_InPut_Mode(void);
 
#endif
