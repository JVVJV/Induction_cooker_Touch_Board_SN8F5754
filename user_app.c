#include "app.h"
#include "sn8f5754.h"
#include "captouch_main.h"
#include "disp.h"
#include "iic.h"
#include "user_isr.h"




unsigned char fifobuf[KEY_FIFO_SIZE];
unsigned char read=0;
unsigned char write=0;

//unsigned char keybuf=0;

volatile unsigned char buztime_500msF=0;

volatile AppState sw = APP_STATE_CLOSE;
unsigned char status = open;
unsigned char mode = MODE_NOTASK;
unsigned char err_num = 0;


unsigned char set_watt;

//unsigned char bflag=0;

unsigned char childLockActive=0;

unsigned char wat_level=4;
volatile unsigned char time_level=10;

unsigned char send_wat_tab[]={0x44,0x48,0x49,0x4a,0x4b,0x4c,0x4d,0x4e,0x4f};
unsigned int wat_tab[]={200,500,800,1000,1300,1600,1800,2000,2200};


//unsigned char disp_time_tab;

volatile unsigned char knob_time=0;

volatile unsigned char disp_chan_tm1=2;
volatile unsigned char disp_chan_tm2=0xFF;
volatile unsigned char disp_delay = 0;

unsigned char  temp;

static void process_i2c_command(unsigned char *from_error);
static void handle_open(void);
static void handle_lock(void);
static void handle_error(unsigned char *from_error, unsigned char prev_mode);
static void handle_standby(unsigned char *prev_mode, unsigned char *from_error);
static void handle_close(unsigned char *from_error);

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
//		bflag=0;
	}
}


void app()
{
	static unsigned char prev_mode = 0;
	static unsigned char from_error = 0;

	buzzerOff();

  process_i2c_command(&from_error);
 	
  disp_time();
	
  switch(sw)
  {
      case APP_STATE_STANDBY:
          handle_standby(&prev_mode, &from_error);
          break;

      case APP_STATE_CLOSE:
      default:
          handle_close(&from_error);
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


static void process_i2c_command(unsigned char *from_error)
{
    if(I2CErrorCode != I2C_ERR_NONE){
        err_num = 9;
        status = erro;
        I2CErrorCode = I2C_ERR_NONE;
    }
  
    if (status == open && !(*from_error)) {
        if (!fifo_empty()) {
            mode = fiforead();
        }
    }
    
    if (*from_error) {
        *from_error = 0;
    }
}

static void handle_open(void)
{
    if(bit_number == 0 || bit_number == 0x05)
        bit_number = standby_n;

    switch(mode)
    {
      case MODE_HOTPOT:
        wat_level = 5;
        bit_number = watt_n;
        LED_B = 0x09;
        MainWatCode = CMD_HOTPOT;
        knob_time = 0;
      break;
      
      case MODE_COOK:
        wat_level = 6;
        bit_number = watt_n;
        LED_B = 0x11;
        MainWatCode = CMD_COOK;			
        knob_time = 0;
      break;		

      case MODE_BOIL:
        wat_level = 8;	
        bit_number = watt_n;
        LED_B = 0x05;
        MainWatCode = CMD_BOIL;	
        knob_time = 0;
      break;				
        
      case MODE_TIMER:
        bit_number = time_n;
        knob_time = 1;
        disp_delay = 4;
      break;
      
      case MODE_ADJUST:
        bit_number = watt_n;	
        MainWatCode = send_wat_tab[wat_level];
      break;
      
      case MODE_NOTASK:
      default:
        bit_number = standby_n;
        MainWatCode = CMD_NONE;
        knob_time = 0;          
      break;
      
    }
}

static void handle_lock(void)
{
    if(bit_number != lock_n)
        temp = bit_number;

    bit_number = lock_n;

    if(MainMegCode == 0x78 || MainMegCode == 0x74)
        status = erro;

    if(childLockActive == 0)
    {
        status = open;
        bit_number = temp;
    }

    fifowrite(0x00);
}

static void handle_error(unsigned char *from_error, unsigned char prev_mode)
{
    bit_number = Ero_n;
  
    if(err_num == 9 && I2CErrorCode == I2C_ERR_NONE)
    {
      err_num = 0;
      status = open;
      mode = prev_mode;
      *from_error = 1;
      return;
    }
  
    if( MainMegCode == 0x70 )
    {			
      err_num = 0;
      status = open;      // exit error state
      mode = prev_mode;   // restore previous mode
      *from_error = 1;    // mark return from error          
    }
}

static void handle_standby(unsigned char *prev_mode, unsigned char *from_error)
{
    if(status != open && status != lock)
        MainWatCode = CMD_NONE;

    if(I2CErrorCode != I2C_ERR_NONE && status != erro)
    {
        *prev_mode = mode;
        err_num = 9;
        status = erro;
        buzzerOn();
    }
      
    if(status != erro)
    {
        if(MainMegCode != 0x70)
        {
            *prev_mode = mode;
            err_num = (MainMegCode - 0x70);
            status = erro;
            buzzerOn(); // Beep once time when error occurs
        }
    }

    switch(status)
    {
        case open:
            handle_open();
            break;

        case lock:
            handle_lock();
            break;

        case erro:
            handle_error(from_error, *prev_mode);
            break;
    }
}

static void handle_close(unsigned char *from_error)
{
    bit_number = close_n;
    knob_time = 0;
    *from_error = 0;
    MainWatCode = CMD_NONE;
    status = open;
    mode = MODE_NOTASK;
}


