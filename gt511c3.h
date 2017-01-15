#include "LPC177x_8x.h"
#include "uart1.h"

void initfpsuart(void)
{
	 uart1_init();
}
//****************enroll***********************************************888
uint8_t initfps(uint8_t x)
{
	int i=0;
	uint8_t temp,ch;
	uart1_tra(0x55);
	uart1_tra(0xaa);
	
	uart1_tra(0);
	uart1_tra(1);//offset= 0 to 3 
	//device id is 0001
	
	uart1_tra(0);
	uart1_tra(0);
	uart1_tra(0);
	uart1_tra(0);//4-byte parameter
	
	uart1_tra(0);//2-byte command
	uart1_tra(1);//2-byte command
	
	uart1_tra(0x01);//checsum=0x101
	uart1_tra(0x01);//2-byte checksum
	
	for(i=0;i<=11;i++)//12-bytes total(assuming 2-byte checksum)
  { temp=uart1_rec();
		if(i==9)
		{
		 ch=temp;
		}
		
	}//
	if(ch==0x30)
	{
		return 1;//acknowledged
	}
	else if(ch==0x31)
	{
		return 0 ;//not acknowledged
	}
	else
	{
	return 0xff;//false acknowlefgement
	}
	
	

}
int i=0;
uint8_t temp,ch;//did this as shpwing error if declare INSIDE block

uint8_t enroll_start(uint8_t id)
{
	
	uint16_t checksum = 0x122+id;
	uint8_t csl,csh;
	csl=checksum&(0X00ff);
	csh=((checksum>>8)&(0X00ff));
	
	//int i=0;
//uint8_t temp,ch;
	uart1_tra(0x55);
	uart1_tra(0xaa);
	
	uart1_tra(0);
	uart1_tra(1);//offset= 0 to 3 
	//device id is 0001
	
	uart1_tra(0);
	uart1_tra(0);
	uart1_tra(0);
	uart1_tra(id);//4-byte parameter
	
	uart1_tra(0);//2-byte command
	uart1_tra(0x22);//2-byte command
	

	
	uart1_tra(csh);//checsum=0x122+id
	uart1_tra(csl);//2-byte checksum
	
	
	for(i=0;i<=11;i++)//12-bytes total(assuming 2-byte checksum)
  { temp=uart1_rec();
		if(i==9)
		{
		 ch=temp;
		}
		
	}//
	if(ch==0x30)
	{
		return 1;//acknowledged
	}
	else if(ch==0x31)
	{//display somethimg wrong;check for NACK parameter
		return 0 ;//not acknowledged
	}
	else
	{
	return 0xff;//false acknowlefgement
	}
	
}

uint8_t capture_fing_enrol(void)
{
	
	int i=0;
	uint8_t temp,ch;
	uart1_tra(0x55);
	uart1_tra(0xaa);
	
	uart1_tra(0);
	uart1_tra(1);//offset= 0 to 3 
	//device id is 0001
	
	uart1_tra(0);
	uart1_tra(0);
	uart1_tra(0);//non-zero parameter;best but slow image
	uart1_tra(0x01);//4-byte parameter
	
	uart1_tra(0);//2-byte command
	uart1_tra(0x60);//2-byte command
	
	uart1_tra(0x01);//checsum=0x161
	uart1_tra(0x61);//2-byte checksum
	
	
	for(i=0;i<=11;i++)//12-bytes total(assuming 2-byte checksum)
  { temp=uart1_rec();
		if(i==9)
		{
		 ch=temp;
		}
		
	}//
	if(ch==0x30)
	{
		return 1;//acknowledged
	}
	else if(ch==0x31)
	{//display somethimg wrong;check for NACK parameter
		return 0 ;//not acknowledged
	}
	else
	{
	return 0xff;//false acknowlefgement
	}
	
}

uint8_t enrol1(void)
{
	
	int i=0;
	uint8_t temp,ch;
	uart1_tra(0x55);
	uart1_tra(0xaa);
	
	uart1_tra(0);
	uart1_tra(1);//offset= 0 to 3 
	//device id is 0001
	
	uart1_tra(0);
	uart1_tra(0);
	uart1_tra(0);//no parameter specified
	uart1_tra(0x00);//4-byte parameter
	
	uart1_tra(0);//2-byte command
	uart1_tra(0x23);//2-byte command
	
	uart1_tra(0x01);//checsum=0x123
	uart1_tra(0x23);//2-byte checksum
	
	
	for(i=0;i<=11;i++)//12-bytes total(assuming 2-byte checksum)
  { temp=uart1_rec();
		if(i==9)
		{
		 ch=temp;
		}
		
	}//
	if(ch==0x30)
	{
		return 1;//acknowledged
	}
	else if(ch==0x31)
	{//display somethimg wrong;check for NACK parameter
		return 0 ;//not acknowledged
	}
	else
	{
	return 0xff;//false acknowlefgement
	}
	
	
	
}

uint8_t enrol2(void)
{
	
	int i=0;
	uint8_t temp,ch;
	uart1_tra(0x55);
	uart1_tra(0xaa);
	
	uart1_tra(0);
	uart1_tra(1);//offset= 0 to 3 
	//device id is 0001
	
	uart1_tra(0);
	uart1_tra(0);
	uart1_tra(0);//no parameter specified
	uart1_tra(0x00);//4-byte parameter
	
	uart1_tra(0);//2-byte command
	uart1_tra(0x24);//2-byte command
	
	uart1_tra(0x01);//checsum=0x124
	uart1_tra(0x24);//2-byte checksum
	
	
	for(i=0;i<=11;i++)//12-bytes total(assuming 2-byte checksum)
  { temp=uart1_rec();
		if(i==9)
		{
		 ch=temp;
		}
		
	}//
	if(ch==0x30)
	{
		return 1;//acknowledged
	}
	else if(ch==0x31)
	{//display somethimg wrong;check for NACK parameter
		return 0 ;//not acknowledged
	}
	else
	{
	return 0xff;//false acknowlefgement
	}
	
	
	
}

uint8_t enrol3(void)
{
	
	int i=0;
	uint8_t temp,ch;
	uart1_tra(0x55);
	uart1_tra(0xaa);
	
	uart1_tra(0);
	uart1_tra(1);//offset= 0 to 3 
	//device id is 0001
	
	uart1_tra(0);
	uart1_tra(0);
	uart1_tra(0);//no parameter specified
	uart1_tra(0x00);//4-byte parameter
	
	uart1_tra(0);//2-byte command
	uart1_tra(0x25);//2-byte command
	
	uart1_tra(0x01);//checsum=0x125
	uart1_tra(0x25);//2-byte checksum
	
	
	for(i=0;i<=11;i++)//12-bytes total(assuming 2-byte checksum)
  { temp=uart1_rec();
		if(i==9)
		{
		 ch=temp;
		}
		
	}//
	if(ch==0x30)
	{
		return 1;//acknowledged
	}
	else if(ch==0x31)
	{//display somethimg wrong;check for NACK parameter
		return 0 ;//not acknowledged
	}
	else
	{
	return 0xff;//false acknowlefgement
	}
	
	
	
}
int flag=0;
uint8_t isPressFinger(void)
{
	
	int i=0;
	uint8_t temp,ch;
	uart1_tra(0x55);
	uart1_tra(0xaa);
	
	uart1_tra(0);
	uart1_tra(1);//offset= 0 to 3 
	//device id is 0001
	
	uart1_tra(0);
	uart1_tra(0);
	uart1_tra(0);//no parameter specified
	uart1_tra(0x00);//4-byte parameter
	
	uart1_tra(0);//2-byte command
	uart1_tra(0x26);//2-byte command
	
	uart1_tra(0x01);//checsum=0x126
	uart1_tra(0x26);//2-byte checksum
	
	//int flag=0;//aSUMING false  FROM B4// if 0,finger pressed
	
	for(i=0;i<=11;i++)//12-bytes total(assuming 2-byte checksum)
  { temp=uart1_rec();
		if(i==9)
		{
		 ch=temp;
		}
		if(((i==4)||(i==5)||(i==6)||(i==7))&&flag==0)
		{
			if(temp!=0)
			{
				flag=1;//means finger is not presed
				//flag=1 means finger not pressed, so can move on
			}
		}
		
	}//
	if((ch==0x30)&&(flag==1))
	{
		return 0x1a;//acknowledged+not pressed
	}
	else if((ch==0x30)&&(flag==0))
	{
		return 0x1b;//acknowledged+ pressed
	}
	else if(ch==0x31)
	{//display somethimg wrong;check for NACK parameter
		return 0 ;//not acknowledged
	}
	else
	{
	return 0xff;//false acknowlefgement
	}
	
	
	
}

void enroll_final(uint8_t id)
{
  uint8_t x;	
	x=enroll_start(id);
	if(x==1)
	{
		 x=capture_fing_enrol();
		if(x==1)
		 {
			 x=enrol1();
			 if(x==1)
			 {
				 //check for isFingerPressed
				 x=0x1b;
				 while(x==0x1b)
				 {
					 x=isPressFinger();
				 }
				 if(x==0x1a)
				  {
						x=capture_fing_enrol();
						if(x==1)
						{
							x=enrol2();
							if(x==1)
							{
								x=0x1b;
								while(x==0x1b)
								{
									x=isPressFinger();
								}
								if(x==0x1a)
								{
									x=capture_fing_enrol();
								  if(x==1)
									{
										x=enrol3();
										/*if(x==1)
										{
											//DISPLAY ENROLL SUCCESFULL
							
									  }*/
									}
								}
							}
						}
					}
				}
			}
		}
	}//END OF ENROLL

	//*****************************************************************************************************
			 
	//6.2Identifying and Verifying
	
	uint8_t capture_finger_verify(void)//exactly same as above, only different type of template
	{
		int i=0;
	uint8_t temp,ch;
	uart1_tra(0x55);
	uart1_tra(0xaa);
	
	uart1_tra(0);
	uart1_tra(1);//offset= 0 to 3 
	//device id is 0001
	
	uart1_tra(0);
	uart1_tra(0);
	uart1_tra(0);//zero parameter;bad but fast image(for verification)
	uart1_tra(0x00);//4-byte parameter
	
	uart1_tra(0);//2-byte command
	uart1_tra(0x60);//2-byte command
	
	uart1_tra(0x01);//checsum=0x161
	uart1_tra(0x61);//2-byte checksum
	
	
	for(i=0;i<=11;i++)//12-bytes total(assuming 2-byte checksum)
  { temp=uart1_rec();
		if(i==9)
		{
		 ch=temp;
		}
		
	}//
	if(ch==0x30)
	{
		return 1;//acknowledged
	}
	else if(ch==0x31)
	{//display somethimg wrong;check for NACK parameter
		return 0 ;//not acknowledged
	}
	else
	{
	return 0xff;//false acknowlefgement
	}
		
		
		
		
		
		
	}
	
uint8_t identify(void)
{
	uint8_t x,id;
	x=capture_finger_verify();
	if(x==1)//start identification
	{
			int i=0;
	uint8_t temp,ch;
	uart1_tra(0x55);
	uart1_tra(0xaa);
	
	uart1_tra(0);
	uart1_tra(1);//offset= 0 to 3 
	//device id is 0001
	
	uart1_tra(0);
	uart1_tra(0);
	uart1_tra(0);//no parameter specigied
	uart1_tra(0);//4-byte parameter
	
	uart1_tra(0);//2-byte command
	uart1_tra(0x51);//2-byte command
	
	uart1_tra(0x01);//checsum=0x151
	uart1_tra(0x51);//2-byte checksum
	
	
	for(i=0;i<=11;i++)//12-bytes total(assuming 2-byte checksum)
  { temp=uart1_rec();
		if(i==9)
		{
		 ch=temp;
		}
		if(i==7)
		{id=temp;
		}
		
		
	}//
	if(ch==0x30)
	{
		return id;//acknowledged
	}
	else if(ch==0x31)
	{//display somethimg wrong;check for NACK parameter
		return 0xfe ;//not acknowledged(different return from other)
	}
	else
	{
	return 0xff;//false acknowlefgement
	}
		
		
		
		
		
	}
	return 0xff;
	
		
		
}

//end of identification***************************************************8


uint8_t deleteall_fingers(void)
{
	int i=0;
	uint8_t temp,ch;
	uart1_tra(0x55);
	uart1_tra(0xaa);
	
	uart1_tra(0);
	uart1_tra(1);//offset= 0 to 3 
	//device id is 0001
	
	uart1_tra(0);
	uart1_tra(0);
	uart1_tra(0);
	uart1_tra(0);//4-byte parameter
	
	uart1_tra(0);//2-byte command
	uart1_tra(0x41);//2-byte command
	
	uart1_tra(0x01);//checsum=0x101
	uart1_tra(0x41);//2-byte checksum
	
	for(i=0;i<=11;i++)//12-bytes total(assuming 2-byte checksum)
  { temp=uart1_rec();
		if(i==9)
		{
		 ch=temp;
		}
		
	}//
	if(ch==0x30)
	{
		return 1;//acknowledged
	}
	else if(ch==0x31)
	{
		return 0 ;//not acknowledged
	}
	else
	{
	return 0xff;//false acknowlefgement
	}
	
	
	
}

uint8_t deleteid_finger(uint8_t id)
{
	
	int i=0;
	uint8_t temp,ch;
	uart1_tra(0x55);
	uart1_tra(0xaa);
	
	uart1_tra(0);
	uart1_tra(1);//offset= 0 to 3 
	//device id is 0001
	
	uart1_tra(0);
	uart1_tra(0);
	uart1_tra(0);
	uart1_tra(id);//4-byte parameter
	
	uart1_tra(0);//2-byte command
	uart1_tra(0x40);//2-byte command
	
	uart1_tra(0x01);//checsum=0x101
	uart1_tra(0x40);//2-byte checksum
	
	for(i=0;i<=11;i++)//12-bytes total(assuming 2-byte checksum)
  { temp=uart1_rec();
		if(i==9)
		{
		 ch=temp;
		}
		
	}//
	if(ch==0x30)
	{
		return 1;//acknowledged
	}
	else if(ch==0x31)
	{
		return 0 ;//not acknowledged
	}
	else
	{
	return 0xff;//false acknowlefgement
	}
}
	


uint8_t get_enroll_count(void)
	{
			int i=0;
		uint8_t n;
	uint8_t temp,ch;
	uart1_tra(0x55);
	uart1_tra(0xaa);
	
	uart1_tra(0);
	uart1_tra(1);//offset= 0 to 3 
	//device id is 0001
	
	uart1_tra(0);
	uart1_tra(0);
	uart1_tra(0);//no parameter specigied
	uart1_tra(0);//4-byte parameter
	
	uart1_tra(0);//2-byte command
	uart1_tra(0x20);//2-byte command
	
	uart1_tra(0x01);//checsum=0x120
	uart1_tra(0x20);//2-byte checksum
	
	
	for(i=0;i<=11;i++)//12-bytes total(assuming 2-byte checksum)
  { temp=uart1_rec();
		if(i==9)
		{
		 ch=temp;
		}
		if(i==7)
		{n=temp;
		}
		
		
	}//
	if(ch==0x30)
	{
		return n;//acknowledged
	}
	else if(ch==0x31)
	{//display somethimg wrong;check for NACK parameter
		return 0xfe ;//not acknowledged(different return from other)
	}
	else
	{
	return 0xff;//false acknowlefgement
	}
}