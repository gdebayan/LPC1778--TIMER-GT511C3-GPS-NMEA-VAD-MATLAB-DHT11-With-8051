#include<reg51.h>
#include<stdio.h>

unsigned char DHT11_data[5];
void delay(int cnt)
{ int i;
	int k;
	for( i=0;i<cnt;i++)
	 
		 for( k=0;k<1270;k++);
		  
}
 void delay_us(unsigned char n)
{
	TMOD=0x02;//timer 0 in mode 2
	TL0=-1*n;
	TH0=-1*n;
	TR0=1;
	while(TF0==1);
	TR0=0;
	TF0=0;
}
sbit rs=P1^2; 	
sbit rw=P1^1; 	
sbit e=P1^0; 

void delay_ms(int cnt)
{
	 int k,i;
	for(i=0;i<cnt;i++)
	  for( k=0;k<1275;k++);
	
  
}
void write(int j) 
{
rs=1;  //selecting rs pin to data mode
rw=0;  //selecting rw pin to write mode
P0=j;  //putting value on the pins
e=1;  //high pulse 
delay(1);
e=0;	// low pulse
return;
}

void cmd(int j)  //command function
{
P0=j;  //put the data on pins
rs=0;  //selecting rw pin to command mode
rw=0;  //selecting to write
e=1;  
delay(1);
e=0;
return;
}

void putsa(char *a) // function to display string on LCD'
{
unsigned int p=0;
for(;a[p]!=0;p++)
write(a[p]);
}

void lcd_init(void) // function to initialise the LCD
{
cmd(0x38); 
delay(1);
cmd(0x0c); //LCD turning on cmd
delay(1);     
cmd(0x01); //clear lcd cmd 
cmd(0x80); // starting point of LCD
}


void DHT11_init();
unsigned char get_byte();
unsigned char get_data();
sbit DHT11_pin=P3^0;

void DHT11_init()
{
   //P1_0_bit = 1;
	  DHT11_pin=1;
   delay_ms(1000);
}

unsigned char get_byte()
{
   unsigned char s = 0;
   unsigned char value = 0;
   for(s = 0; s < 8; s += 1)
   {
      value = value<< 1;
      while((DHT11_pin == 0));
      delay_us(30);
      if(DHT11_pin == 1)
      {
          value |= 1;
      }
      while(DHT11_pin == 1);
   }
   return value;
}

unsigned char get_data()
{
   bit chk=0;
   unsigned char s = 0;
   unsigned char check_sum = 0;

   DHT11_pin = 1;
   DHT11_pin = 0;
   delay_ms(16);//was 18before this
   DHT11_pin = 1;
   delay_us(26);
 while(DHT11_pin==1);//should go low
   chk = DHT11_pin;
	
   if(chk)
   {
      return 1;
   }
   delay_us(80);
	 while(DHT11_pin==0);//should become high to continue
   
	 

   chk = DHT11_pin;//sensor should be pulled uo for 80us now
   if(!chk)
   {
      return 2;
   }
   delay_us(80);//for 80us  should be high
	 while(DHT11_pin==1);//incase high for slightly longer
 //data transmission starts here!!!!
   for(s = 0; s <= 4; s += 1)
   {
       DHT11_data[s] = get_byte();
   }

   DHT11_pin = 1;

   for(s = 0; s < 4; s += 1)
   {
       check_sum += DHT11_data[s];
   }

   if(check_sum != DHT11_data[4])
   {
      return 3;
   }
   else
   {
      return 0;
   }
}


void main() 
{
     unsigned char text[6];
     unsigned short state = 0;

     lcd_init();
//	int x;
     
     while(1)
     {
            state = get_data();

            switch(state)
            {
                  case 1:
                  {
                  }
                  case 2:
                  {
                    // lcd_cmd(_LCD_CLEAR);
                     //lcd_out(1, 1, "No Sensor Found!");
                    
										putsa("No sensor found"); 
										cmd(0x01);
										break;
                  }
                  case 3:
                  {
                    // lcd_cmd(_LCD_CLEAR);
                     //lcd_out(1, 1, "Checksum Error!");
										
                    putsa("Check sum error"); 
										cmd(0x01);
										break;
                  }
                  default:
                  {
                    // lcd_cmd(_LCD_CLEAR);
                     //lcd_out(1, 4, "R.H: ");
                     //lcd_out(2, 4, "Tmp: ");
                     //lcd_out(1, 13, "%");
                     //lcd_chr(2, 12, 0);
                     //lcd_out(2, 13, "C");
                     //ByteToStr(DHT11_data[0], Text);
                     //Lcd_Out(1, 9, Text);
                     //ByteToStr(DHT11_data[2], Text);
                     //Lcd_Out(2, 9, Text);
										 
                    
									  write(DHT11_data[4]);
										write(DHT11_data[3]);
										write(DHT11_data[2]);
										write(DHT11_data[1]);
										cmd(0x01);
										 break;
									}
            }
            delay_ms(600);
     };
}







