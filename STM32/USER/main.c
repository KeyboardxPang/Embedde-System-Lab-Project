#include "sys.h"
#include "delay.h"
#include "oled_iic.h"
#include "stdio.h"
#include "key.h"
#include "timer.h"
#include "as608.h"
#include "usart3.h"
#include "usart.h"
#include "rc522.h"
#include "PWM.h"


int main(void)
{		
	extern const u8 BMP1[];
	HZ= GB16_NUM();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	delay_init();
	usart3_init(57600);
	KEY_Init();
	uart_init(9600);	 	//���ڳ�ʼ��Ϊ9600
	OLED_Init();
	
	OLED_Clear();
	// RC522_Init();       //��ʼ����Ƶ��ģ��
	
	OLED_ShowCH(6, 0, "Sign in System");
	OLED_ShowCH(6, 3, "K5 Fingerprint");
	OLED_ShowCH(6, 5, "K6 Human Face");
	PWM_Init();
	PWM_SetCompare3(2500);
	while(1)
	{
		//RC522_Handel();
		alarm_num = 0;
		key_num = KEY_Scan(0);
		if(key_num==1)
		{
			key_num=0;
			OLED_Clear();
			Add_FR();
		}
		if(key_num==3)
		{
			key_num=0;
			OLED_Clear();
			Del_FR();
		}
		if(key_num==5)
		{
			key_num=0;
			OLED_Clear();
			OLED_ShowCH(16, 2, "Please Press");
			OLED_ShowCH(20, 4, "K1 Go Back");
			uart_sendbyte('1');	//'1'����ʼָ����֤
			press_FR();
		}	
	}
}


