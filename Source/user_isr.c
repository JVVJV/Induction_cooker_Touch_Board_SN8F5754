//--------------------------------------------------------------------------
//Filename		: user_isr.c
//Function		: 
//--------------------------------------------------------------------------
#include "captouch_main.h"
#include "captouch_init.h"
#include "sysmode.h"
#include "app.h"
#include "disp.h"
#include "user_isr.h"


idata IntGnd_s IntGnd;

unsigned char set_time;
unsigned char timebase_500us;
unsigned char keylong_1ms;
unsigned char keylong_1msF;
unsigned int buztime_500ms=1000;

unsigned char scanT;

//--------------------------------------------------------------------------
//subroutine	: isr_timer0
//Function		: Timer0 interrupt service routine
//Note				: 如果有打开T0唤醒功能，必须有ISRTimer0中断程序才可实现唤醒功能
//--------------------------------------------------------------------------
void isr_timer0(void) interrupt ISRTimer0
{
	#if POWER_SAVE
	record_wakeup_source(TIMER0_WAKEUP_MODE);  //for touch low power sysmode
	#endif
}
//--------------------------------------------------------------------------
//subroutine	: isr_timer1
//Function		: Timer1 interrupt service routine
//--------------------------------------------------------------------------
void isr_timer1(void) interrupt ISRTimer1
{
	touch_isr_timer();		//500us intgnd for Touch
 
	if(++IntGnd.count1ms >= 2)               //1ms
	 {		
		IntGnd.count1ms =0;
		IntGnd.fTime1ms = 1;
		
		if(tm_keydelay!=0)
	    tm_keydelay--;
		
		keylong_1msF=1;			 
		display(); 
		
		if(++IntGnd.count100ms >= 100)         //100ms
		{
			IntGnd.count100ms =0;
			IntGnd.fTime100ms = 1;
			
    if(buztime_500msF!=0)
			buztime_500msF--;
			
			
			if(++IntGnd.count1s >= 10)           //1s
			{
				IntGnd.count1s =0;
				IntGnd.fTime1s = 1;

				if(disp_delay != 0)
				  disp_delay--;
				
				if(disp_chan_tm1 != 0)
				  disp_chan_tm1--;
				
				if(disp_chan_tm2 != 0)
				  disp_chan_tm2--;
				
				if(++IntGnd.count1min >= 60)       //1min
				{
					IntGnd.count1min =0;
					IntGnd.fTime1min = 1;
					
					if(knob_time)
					{
						if(--time_level==0)
							{
								sw = close;										
							}						
					}

					
					if(++IntGnd.count1h >= 60)       //1h
					{
						IntGnd.count1h = 0;
						IntGnd.fTime1h = 1;
					}						
				}    
			}
		}
	 }

		 
//	if(bflag)
//	{
//		if(--buztime_500ms==0)
//		{
//			buztime_500ms=1000;
//			buztime_500msF=1;
//		}		
//	}
//	
//	if(--keylong_1ms==0)
//	{
//		keylong_1ms=2;
//		keylong_1msF=1;
//	}
//	
//	if(--scanT==0)        //每1ms动态扫描数码管
//	{
//		scanT=2;
//		display();
//	}

}


//void intgnd_time()
//{
//	if(timebase_500us)
//	{
//		timebase_500us=0;

//		if(++IntGnd.count1ms >= 2)
//		 {		
//			IntGnd.count1ms =0;
//			IntGnd.fTime1ms = 1;
//			
//      keylong_1msF=1;			 
//			display(); 
//      
//			if(++IntGnd.count100ms >= 100)
//			{
//				IntGnd.count100ms =0;
//				IntGnd.fTime100ms = 1;
//				
//				if(++IntGnd.count1s >= 10)
//				{
//					IntGnd.count1s =0;
//					IntGnd.fTime1s = 1;
//					
//					if(++IntGnd.count1min >= 60)
//					{
//						IntGnd.count1min =0;
//						IntGnd.fTime1min = 1;
//						
//						if(set_time != 0)
//							set_time--;
//						
//						if(++IntGnd.count1h >= 60)
//						{
//							IntGnd.count1h = 0;
//							IntGnd.fTime1h = 1;
//						}						
//					}    
//				}
//			}
//		 }
//	 }
//}

//--------------------------------------------------------------------------
//subroutine	: isr_timer3
//Function		: Timer3 interrupt service routine
//--------------------------------------------------------------------------
//void isr_timer3(void) interrupt ISRTimer3
//{
//}
//--------------------------------------------------------------------------
//subroutine	: isr_uart0tx
//Function		: UART0 TX interrupt service routine
//--------------------------------------------------------------------------
//void isr_uart0tx(void) interrupt ISRUart0tx
//{
//}
//--------------------------------------------------------------------------
//subroutine	: isr_uart0rx
//Function		: UART0 RX interrupt service routine
//--------------------------------------------------------------------------
//void isr_uart0rx(void) interrupt ISRUart0rx
//{
//}
//--------------------------------------------------------------------------
//subroutine	: isr_uart1tx
//Function		: UART1 TX interrupt service routine
//--------------------------------------------------------------------------
//void isr_uart1tx(void) interrupt ISRUart1tx
//{
//}
//--------------------------------------------------------------------------
//subroutine	: isr_uart1rx
//Function		: UART1 RX interrupt service routine
//--------------------------------------------------------------------------
//void isr_uart1rx(void) interrupt ISRUart1rx
//{
//}
//--------------------------------------------------------------------------
//subroutine	: isr_i2c
//Function		: I2C interrupt service routine
//--------------------------------------------------------------------------
//void isr_i2c(void) interrupt ISRI2c
//{
//}
//--------------------------------------------------------------------------
//subroutine	: isr_pwm1
//Function		: PWM1 interrupt service routine
//--------------------------------------------------------------------------
//void isr_pwm1(void) interrupt ISRPwm1
//{
//}
//--------------------------------------------------------------------------
//subroutine	: isr_pwm2
//Function		: PWM2 interrupt service routine
//--------------------------------------------------------------------------
//void isr_pwm2(void) interrupt ISRPwm2
//{
//}
//--------------------------------------------------------------------------
//subroutine	: isr_int0
//Function		: INT1 interrupt service routine
//--------------------------------------------------------------------------
//void isr_int0(void) interrupt ISRInt0
//{
//}
//--------------------------------------------------------------------------
//subroutine	: isr_int1
//Function		: INT1 interrupt service routine
//--------------------------------------------------------------------------
//void isr_int1(void) interrupt ISRInt1
//{
//}
//--------------------------------------------------------------------------
//subroutine	: isr_int2
//Function		: INT2 interrupt service routine
//--------------------------------------------------------------------------
//void isr_int2(void) interrupt ISRInt2
//{
//}
//--------------------------------------------------------------------------
//subroutine	: isr_adc
//Function		: adc interrupt service routine
//--------------------------------------------------------------------------
void isr_adc(void) interrupt ISRAdc
{
	#if POWER_SAVE
	record_wakeup_source(ADC_WAKEUP_MODE);   //for touch low power sysmode
	#endif
}
