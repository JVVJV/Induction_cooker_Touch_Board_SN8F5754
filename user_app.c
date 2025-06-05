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

volatile unsigned char buztime_500msF=0;

volatile unsigned char sw=close;
unsigned char status=0x01;
unsigned char mode=0;
unsigned char err_num = 0;


unsigned char set_watt;

unsigned char bflag=0;

unsigned char childLockActive=0;

unsigned char wat_level=4;
volatile unsigned char time_level=10;

unsigned char send_wat_tab[]={0x44,0x48,0x49,0x4a,0x4b,0x4c,0x4d,0x4e,0x4f};
unsigned int wat_tab[]={200,500,800,1000,1300,1600,1800,2000,2200};


unsigned char disp_time_tab;

volatile unsigned char knob_time=0;

volatile unsigned char disp_chan_tm1=2;
volatile unsigned char disp_chan_tm2=0xFF;
volatile unsigned char disp_delay;

unsigned char  temp;

// Returns 1 if FIFO is empty, 0 otherwise
unsigned char fifo_empty(void) {
    return (read == write);
}

// Function to read data from the FIFO buffer
unsigned char fiforead(void) 
{
    unsigned char Rdata;
  
    Rdata = fifobuf[read];
    read++;

    // Wrap around if the read index reaches the end of the buffer
    if (read >= KEY_FIFO_SIZE) 
        read = 0;

    return Rdata;
}
			
// Function to write data to the FIFO buffer
void fifowrite(unsigned char num)
{
    unsigned char next;

    // Calculate the next write index
    next = write + 1;

    // Wrap around if the next write index reaches the end of the buffer
    if (next >= KEY_FIFO_SIZE)
        next = 0;

    // If the buffer is full (next write index equals the read index)
    if (next == read)
    {
        // Move the read index forward to make space (overwrite the oldest data)
        read++;
        if (read >= KEY_FIFO_SIZE)
            read = 0;
    }

    fifobuf[write] = num;
    write = next;
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
	static unsigned char prev_mode = 0;       // 保存进入错误前的模式
	static unsigned char from_error = 0;      // 标记是否刚从错误恢复 ,

	buzzerOff();

	// 仅在非恢复场景下从 FIFO 读取 mode
	if (status == open && !from_error){        // from_error为0表示false，非0为true
		if (!fifo_empty()) {
      mode = fiforead();
    }	
  }
	
	// 重置恢复标记（确保只生效一次）
	if (from_error)
			from_error = 0;
		
  disp_time();
	
	switch(sw)
	{	                 
		case standby://待机状态 
			if(status != open && status != lock) {
			  MainWatCode= 0x00;	
			}
      
//			if( MainMegCode == 0x78 || MainMegCode == 0x74 ){  //HCW** comment
//				prev_mode = fifobuf[read-1];   // 保存当前模式
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
			  case open:                   //工作模式		
					if(bit_number == 0 || bit_number == 0x05 )
           bit_number = standby_n;

					switch(mode)
					{
						case hotpot:              //火锅模式
							wat_level = 5;
							bit_number = watt_n;
						  LED_B = 0x09;
							MainWatCode = 0x4C;
							knob_time = 0;          //旋钮调节功能为调节功率							
						break;
						
						case cook:                //炒菜模式
							wat_level = 6;
							bit_number = watt_n;
						  LED_B = 0x11;
							MainWatCode= 0x4D;			
							knob_time = 0;          //旋钮调节功能为调节功率							
						break;		
 
						case boil:                //烧水模式
							wat_level = 8;	
							bit_number = watt_n;
						  LED_B = 0x05;
							MainWatCode = 0x4F;	
							knob_time = 0;          //旋钮调节功能为调节功率
						break;				
							
						case timer:               //定时功能
							bit_number = time_n;
              knob_time = 1;          //处于定时状态
              disp_delay = 4;
						break;
						
						case adjust:              //调节功率
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

				case lock:                   //锁定状态
					if(bit_number != lock_n)
					  temp = bit_number;
					bit_number = lock_n;
					if( MainMegCode == 0x78 || MainMegCode == 0x74 )
						status = erro;	
					if(childLockActive == 0)   //解除锁定
					{
						status = open;
            bit_number = temp;
					}
					fifowrite(0x00);
				break;			

				case erro:                   //错误状态
					bit_number = Ero_n;
					if( MainMegCode == 0x70 )
					{			
						err_num = 0;
            status = open;      // 退出错误状态
						mode = prev_mode;   // 恢复之前的模式
						from_error = 1;     // 标记为“刚从错误恢复”															
					}						
				break;	
					
			}
		break;			
		
			
		case close:                   //关机状态
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





