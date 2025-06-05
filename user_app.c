#include "app.h"
#include "sn8f5754.h"
#include "captouch_main.h"
#include "disp.h"
#include "iic.h"
#include "user_isr.h"




unsigned char fifobuf[KEY_FIFO_SIZE];
unsigned char read=0;
unsigned char write=0;

unsigned char keybuf=0;

unsigned char buztime_500msF=0;

unsigned char sw=close;
unsigned char status=0x01;
unsigned char mode=0;
unsigned char err_num = 0;


unsigned char set_watt;

unsigned char bflag=0;

unsigned char childLockActive=0;

unsigned char wat_level=4;
unsigned char time_level=10;

unsigned char send_wat_tab[]={0x44,0x48,0x49,0x4a,0x4b,0x4c,0x4d,0x4e,0x4f};
unsigned int wat_tab[]={200,500,800,1000,1300,1600,1800,2000,2200};


unsigned char disp_time_tab;

unsigned char knob_time=0;

unsigned char disp_chan_tm1=2;
unsigned char disp_chan_tm2=-1;
unsigned char disp_delay;

unsigned char  temp;

// Returns 1 if FIFO is empty, 0 otherwise
unsigned char fifo_empty(void) {
    return (read == write);
}

//// Returns 1 if FIFO is full, 0 otherwise
//unsigned char fifo_full(void) {
//    unsigned char next = write + 1;
//    if (next >= KEY_FIFO_SIZE) next = 0;
//    return (next == read);
//}

unsigned char fiforead(void) 
{
  unsigned char Rdata;
  Rdata = fifobuf[read];
  read++;
  if (read >= KEY_FIFO_SIZE) read = 0;
  
  return Rdata;
}

void fifowrite(unsigned char num)
{
   fifobuf[write]=num;
	 write++;
	 if(write>=KEY_FIFO_SIZE)
	 {
			write=0;
	 }
}
			
void buzzerOn()
{
	buzOn;
	buztime_500msF=2;
}
			
void buzzerOff()
{
	if(buztime_500msF==0)
	{
    buzOff;
		bflag=0;
	}
}


void app()
{
	static unsigned char prev_mode = 0;       // ����������ǰ��ģʽ
	static unsigned char from_error = 0;      // ����Ƿ�մӴ���ָ� ,

	buzzerOff();

	// ���ڷǻָ������´� FIFO ��ȡ mode
	if (status == open && !from_error){        // from_errorΪ0��ʾfalse����0Ϊtrue
		if (!fifo_empty()) {
      mode = fiforead();
    }	
  }
	
	// ���ûָ���ǣ�ȷ��ֻ��Чһ�Σ�
	if (from_error)
			from_error = 0;
		
  disp_time();
	
	switch(sw)
	{	                 
		case standby://����״̬ 
			if(status != open && status != lock) {
			  MainWatCode= 0x00;	
			}
      
//			if( MainMegCode == 0x78 || MainMegCode == 0x74 ){  //HCW** comment
//				prev_mode = fifobuf[read-1];   // ���浱ǰģʽ
//				status = erro;		
//			}
      
      // Enter error state if (MainMegCode != 0x70)  //HCW** add
      if (status != erro) {
        if (MainMegCode != 0x70) {
          prev_mode = mode;
          err_num = (MainMegCode - 0x70);
          status = erro;
          buzzerOn(); // Beep once time when error occurs
        }
      }

		  switch(status)
			{
			  case open:                   //����ģʽ		
					if(bit_number == 0 || bit_number == 0x05 )
           bit_number = standby_n;

					switch(mode)
					{
						case hotpot:              //���ģʽ
							wat_level = 5;
							bit_number = watt_n;
						  LED_B = 0x09;
							MainWatCode = 0x4C;
							knob_time = 0;          //��ť���ڹ���Ϊ���ڹ���							
						break;
						
						case cook:                //����ģʽ
							wat_level = 6;
							bit_number = watt_n;
						  LED_B = 0x11;
							MainWatCode= 0x4D;			
							knob_time = 0;          //��ť���ڹ���Ϊ���ڹ���							
						break;		
 
						case boil:                //��ˮģʽ
							wat_level = 8;	
							bit_number = watt_n;
						  LED_B = 0x05;
							MainWatCode = 0x4F;	
							knob_time = 0;          //��ť���ڹ���Ϊ���ڹ���
						break;				
							
						case timer:               //��ʱ����
							bit_number = time_n;
              knob_time = 1;          //���ڶ�ʱ״̬
              disp_delay = 4;
						break;
						
						case adjust:              //���ڹ���
							bit_number = watt_n;	
							MainWatCode = send_wat_tab[wat_level];
						break;
            
            case notask:
							bit_number = standby_n;
							MainWatCode = 0x00;
							knob_time = 0;          
						break;
            
					}
        break;

				case lock:                   //����״̬
					if(bit_number != lock_n)
					  temp = bit_number;
					bit_number = lock_n;
					if( MainMegCode == 0x78 || MainMegCode == 0x74 )
						status = erro;	
					if(childLockActive == 0)   //�������
					{
						status = open;
            bit_number = temp;
					}
					fifowrite(0x00);
				break;			

				case erro:                   //����״̬
					bit_number = Ero_n;
					if( MainMegCode == 0x70 )
					{			
						err_num = 0;
            status = open;      // �˳�����״̬
						mode = prev_mode;   // �ָ�֮ǰ��ģʽ
						from_error = 1;     // ���Ϊ���մӴ���ָ���															
					}						
				break;	
					
			}
		break;			
		
			
		case close:                   //�ػ�״̬
			bit_number = close_n;
		  knob_time = 0;
		  from_error = 0; 
			MainWatCode= 0x00;	
      status = open;	
		  mode=0;
		break;
		

	}
	
}

void disp_time()
{
	if(knob_time)
	{
		if(disp_delay==0)
			bit_number = sw_n;
	}

}





