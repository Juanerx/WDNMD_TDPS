#include "SR04.h"
#include "delay.h"

float distant;      //distance measurement
uint32_t measure_Buf[3] = {0};   //An array that holds the timer counts
uint8_t  measure_Cnt = 0;    //Status flag bit
uint32_t high_time;   //High level time returned by the ultrasonic module


//===============================================distance measurement
float SR04_GetData(void)
{
switch (measure_Cnt){
	case 0:
         TRIG_1_H;
//	       TRIG_2_H;
//	       TRIG_3_H;
         delay_us(30);
         TRIG_1_L;
//	       TRIG_2_L;
//	       TRIG_3_L;
		measure_Cnt++;
		__HAL_TIM_SET_CAPTUREPOLARITY(&htim2, TIM_CHANNEL_2, TIM_INPUTCHANNELPOLARITY_RISING);
		HAL_TIM_IC_Start_IT(&htim2, TIM_CHANNEL_2);	//enable the input capture                                                                                       		
		return 0;
	break;
	case 3:
    	high_time = measure_Buf[1]- measure_Buf[0];    //high level time
       //    printf("\r\n----high level time-%d-us----\r\n",high_time);							
		distant=(high_time*0.034)/2;  //unit cm
	      
//        printf("\r\n-distance is-%.6f-cm-\r\n",distant);          
		measure_Cnt = 0;  //clear the flag bit
        TIM2->CNT=0;     //clear the count in timer
	      return distant;
		break;
				
	}
}


//===============================================interrupt callback function
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)//
{
	
	if(TIM2 == htim->Instance)// the timer for judging the  trigged interrupt is timer 2
	{
		switch(measure_Cnt){
			case 1:
				measure_Buf[0] = HAL_TIM_ReadCapturedValue(&htim2,TIM_CHANNEL_2);//obtain the present capture value
				__HAL_TIM_SET_CAPTUREPOLARITY(&htim2,TIM_CHANNEL_2,TIM_ICPOLARITY_FALLING);  //set to falling edge capture
				measure_Cnt++;                                            
				break;              
			case 2:
				measure_Buf[1] = HAL_TIM_ReadCapturedValue(&htim2,TIM_CHANNEL_2);//obtain the present capture value
				HAL_TIM_IC_Stop_IT(&htim2,TIM_CHANNEL_2); //stop capture 
				measure_Cnt++;  
                         
		}
	
	}
	
}

