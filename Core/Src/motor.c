///created by fuyufei motor���ƺ�����������
#include "sys.h"
#include "usart.h"
#include "delay.h"
#include "timer.h"
#include "motor.h"
#include "key.h"
#include "string.h"


//////////////////////////////////////////////////////////////////////////
void Motor_Init(int MOTOR_START){
	volatile int motor_cnt =0;
	if(MOTOR_START==1) {
		IN1_FRONT(0);//define in the .h file 0 is reset and 1 is set
		IN2_FRONT(1);
		IN3_FRONT(0);
		IN4_FRONT(1);
		IN1_BEHIND(0);
		IN2_BEHIND(1);
		IN3_BEHIND(0);
		IN4_BEHIND(1);///����Ϊ����ת��
			while(motor_cnt<1){TIM_SetTIM3Compare1(GO);	//�޸ıȽ�ֵ���޸�ռ�ձ�
		TIM_SetTIM3Compare2(GO);	//�޸ıȽ�ֵ���޸�ռ�ձ�
		TIM_SetTIM3Compare3(GO);	//�޸ıȽ�ֵ���޸�ռ�ձ�
		TIM_SetTIM3Compare4(GO);	//�޸ıȽ�ֵ���޸�ռ�ձ�
			HAL_Delay(1000);
			motor_cnt = motor_cnt +1;
				printf("%d",motor_cnt);
			HAL_Delay(1000);
	}
}
	else{
		IN1_FRONT(0);
		IN2_FRONT(0);
		IN3_FRONT(0);
		IN4_FRONT(0);
		IN1_BEHIND(0);
		IN2_BEHIND(0);
		IN3_BEHIND(0);
		IN4_BEHIND(0);
		HAL_Delay(1000);
	}
}

void motor_direction(int direction){
	if (direction == STRAIGHT){
		IN1_FRONT(0);//define in the .h file 0 is reset and 1 is set
		IN2_FRONT(1);
		IN3_FRONT(0);
		IN4_FRONT(1);
		IN1_BEHIND(0);
		IN2_BEHIND(1);
		IN3_BEHIND(0);
		IN4_BEHIND(1);///����Ϊ����ת��
		}
	else if(direction == LEFT){
		IN1_FRONT(0); // right
  	IN2_FRONT(1);
		IN3_FRONT(1); // left
		IN4_FRONT(0);
	  IN1_BEHIND(1); // left
		IN2_BEHIND(0);
		IN3_BEHIND(0); // right
		IN4_BEHIND(1);
	}
	else if(direction == RIGHT){
		IN1_FRONT(1); // right
  	IN2_FRONT(0);
		IN3_FRONT(0); // left
		IN4_FRONT(1);
	  IN1_BEHIND(0); // left
		IN2_BEHIND(1);
		IN3_BEHIND(1); // right
		IN4_BEHIND(0);
	}
	else if(direction == BACK){
		IN1_FRONT(1); // right
  	IN2_FRONT(0);
		IN3_FRONT(1); // left
		IN4_FRONT(0);
	  IN1_BEHIND(1); // left
		IN2_BEHIND(0);
		IN3_BEHIND(1); // right
		IN4_BEHIND(0);
	}
	else{
		IN1_FRONT(0); // right
  	IN2_FRONT(0);
		IN3_FRONT(0); // left
		IN4_FRONT(0);
	  IN1_BEHIND(0); // left
		IN2_BEHIND(0);
		IN3_BEHIND(0); // right
		IN4_BEHIND(0);
	}
}

void Motor_Straight(int speed,int duration){
volatile int motor_cnt=0;
		motor_direction(STRAIGHT);
			while(motor_cnt<1){TIM_SetTIM3Compare1(speed);	//��ǰ
		TIM_SetTIM3Compare2(speed);	//��ǰ
		TIM_SetTIM3Compare3(speed);	//�Һ�
		TIM_SetTIM3Compare4(speed);	//���
			HAL_Delay(duration);
			motor_cnt = motor_cnt +1;
			
	}
}


int left_pwm; //����pwm
int right_pwm; //����pwm
int direction; //����

void mapping(uint8_t* USART_RX_BUF_int1,int *left_pwm,int *right_pwm,int *direction){
	//ֱ��
	if (strncmp((char*)USART_RX_BUF_int1,"A",1)==0){ 
		*direction = STRAIGHT;
		*left_pwm = 300;
		*right_pwm = 300;
	}
	//ֱ��
	else if (strncmp((char*)USART_RX_BUF_int1,"B",1)==0){ 
		*direction = STRAIGHT;
		*left_pwm = 350;
		*right_pwm = 200;         
	}
	//ֱ��
	else if (strncmp((char*)USART_RX_BUF_int1,"C",1)==0){ 
		*direction = STRAIGHT;
		*left_pwm = 200;
		*right_pwm = 350;
	}
	//��ת
	else if (strncmp((char*)USART_RX_BUF_int1,"D",1)==0){ 
		*direction = LEFT;
		*left_pwm = 175;
		*right_pwm = 125;
	}
	//��ת
	else if (strncmp((char*)USART_RX_BUF_int1,"E",1)==0){
		*direction = RIGHT;
		*left_pwm = 125;
		*right_pwm = 175;
	}
	//����ת
	else if (strncmp((char*)USART_RX_BUF_int1,"F",1)==0){
		*direction = LEFT;
		*left_pwm = 125;
		*right_pwm = 75;
	}
	//����ת
	else if (strncmp((char*)USART_RX_BUF_int1,"G",1)==0){
		*direction = RIGHT;
		*left_pwm = 75;
		*right_pwm = 125;
	}
	else{
		*direction = STOP;
		*left_pwm = 500;
		*right_pwm = 500;
		}
	
}
void Motor_LineTracking(int *left_pwm,int *right_pwm,int *direction){ 
	volatile int motor_cnt=0;
	
		motor_direction(*direction);
		while(motor_cnt < 1){TIM_SetTIM3Compare1(*right_pwm);	//��ǰ
		TIM_SetTIM3Compare2(*left_pwm);	//��ǰ
		TIM_SetTIM3Compare3(*right_pwm);	//�Һ�
		TIM_SetTIM3Compare4(*left_pwm);	//���
			HAL_Delay(300);
			motor_cnt= motor_cnt +1;
			printf("%d",motor_cnt);
			
}
		}

		
void testing(){
volatile int motor_cnt=0;
		IN1_FRONT(0);//right
		IN2_FRONT(1);
		IN3_FRONT(0);//left
		IN4_FRONT(1);
		IN1_BEHIND(0);//left
		IN2_BEHIND(1);
		IN3_BEHIND(0); //right
		IN4_BEHIND(1);
			while(motor_cnt<1){TIM_SetTIM3Compare1(GO);	//��ǰ
		TIM_SetTIM3Compare2(GO);	//��ǰ
		TIM_SetTIM3Compare3(GO);	//�Һ�
		TIM_SetTIM3Compare4(GO);	//���
			HAL_Delay(1000);
			motor_cnt = motor_cnt +1;
			printf("%d",motor_cnt);
			HAL_Delay(1000);
	}
}


void Motor_Left_90(int duration){
  	motor_direction(LEFT);
		volatile int motor_cnt=0;
		while(motor_cnt<1){	TIM_SetTIM3Compare1(100);	//�޸ıȽ�ֵ���޸�ռ�ձ�
		TIM_SetTIM3Compare2(100);	//�޸ıȽ�ֵ���޸�ռ�ձ� ��������
		TIM_SetTIM3Compare3(100);	//�޸ıȽ�ֵ���޸�ռ�ձ�
		TIM_SetTIM3Compare4(100);
			HAL_Delay(duration);
				motor_cnt= motor_cnt +1;
		}

}
void Motor_Right_90(int duration){
		motor_direction(RIGHT);
		volatile int motor_cnt=0;
		while(motor_cnt<1){	TIM_SetTIM3Compare1(100);	//�޸ıȽ�ֵ���޸�ռ�ձ�
		TIM_SetTIM3Compare2(100);	//�޸ıȽ�ֵ���޸�ռ�ձ� ��������
		TIM_SetTIM3Compare3(100);	//�޸ıȽ�ֵ���޸�ռ�ձ�
		TIM_SetTIM3Compare4(100);
			HAL_Delay(duration);
				motor_cnt= motor_cnt +1;
		}

}


void Motor_Stop(int MOTOR_STOP){
		IN1_FRONT(0);
		IN2_FRONT(0);
		IN3_FRONT(0);
		IN4_FRONT(0);
		IN1_BEHIND(0);
		IN2_BEHIND(0);
		IN3_BEHIND(0);
		IN4_BEHIND(0);///STOP
		HAL_Delay(MOTOR_STOP);
	
}
 
