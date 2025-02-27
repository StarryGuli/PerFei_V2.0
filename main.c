#include "stm32f10x.h"
#include "systick.h"
#include "led.h"
#include "pwm.h"
#include "iic.h"
#include "mpu6050.h"
#include "spi.h"
#include "adc.h"
#include "acc_cal.h"
#include "pid.h"
#include "timer.h"
#include "nvic.h"
#include "usart2.h"

int main(void)
{
    SystemInit();			//ϵͳ��ʼ��    
		SystickInit();		//ϵͳ�δ�ʱ����ʼ��
	
    LedInit();		//״̬�Ƴ�ʼ��
		
		Usart2Init(115200);		//����2��ʼ��
	
		PwmInit();		//pwm��ʼ
	
		delay_ms(100);		//��ʱ�����Ա㿪��������ƫ�ɼ�����ֹ˲�䶶��
		I2cInit();		///I2C��ʼ��
		mpu6050_init();		//mpu6050��ʼ�� 
    while(get_mpu_id()!=0x68){		//mpu6050��λ���                           
      delay_ms(10);  
			TopLedBlink(RED);			
    }
	
		delay_ms(100);
    SpiInit();
		NRF24L01Init();		//nrf24l01��ʼ��
		while(NRF24L01_Check()){		//nrf24l01��λ���
			delay_ms(30);
			TopLedBlink(RED);
		}
    NRF24L01ReceiveMode();		//����ģʽ
		
		get_iir_factor(&Mpu.att_acc_factor,0.005f,15);   	//��̬����ʱ���ٶȵ�ͨϵ�� 
		get_iir_factor(&Mpu.fix_acc_factor,0.005f,2);		//�߶��ں�ʱ���ٶȵ�ͨϵ��
		
		AdcInit();
		
		AllPidInit();		//pid������ʼ��
		
		read_cal_dat();		//flashУ׼���ݶ�ȡ
		
		delay_ms(100);
		TimerInit();		//��ʱ����ʼ��    
    NVIC_config();		//�ж����ó�ʼ��
		
    while(1){
			VoltageDetect();		//�͵�ѹ���
			LeftButtomLedBlinkSet();		//����˸
			//NrfTxPacket();
    }
}


