#include "LPC177x_8x.h"
#include "uart1.h"

void gps_init(void)
{
	uart1_init();
}

uint8_t lat[12];
uint8_t lon[12];
uint8_t data;
void disp_cord()
{
	int count=0;
	int i,j;
	 while(count<1)
	 {
		 data=uart1_rec();
		 if(data=='$')
			{
				data=uart1_rec();
				if(data=='G')
					{
						data=uart1_rec();
							if(data=='P')
								{
          		    data=uart1_rec();
									  if(data=='G')
										  {
	                      data=uart1_rec();
												 
													 if(data=='G')
													   {
															 data=uart1_rec();
															  
																	if(data=='A')
																	 {
																		 data=uart1_rec();
																		  if(data==',')
																			{
																				data=uart1_rec();
																				while(data!=',')
																				{
																					data=uart1_rec();
																				}//GMT time part skipped
																				for(i=0;data!='N';i++)
																				 {
																					  data=uart1_rec();
																					 lat[i]=data;
																					 if(i==14)//if somethingwronghappens
																					 {
																						 break;
																					 }
																				 }//store latitude
																				 data=uart1_rec();
																				 if(data==',')
																				  {
																						for(j=0;data!='E';j++)
																						{
																							 data=uart1_rec();
																							lon[j]=data;
																							if(j==14)
																							{break;
																							}//ifsomethingwrong
																						}
																					count=1;//datasuccesfully aquired, can exit now
																					}//store longtitude
																				}
																			}
																		}
																	}
																}
															}
														
														}
													}
												}//end of func

/*void disp_cord(void)
{
	//display/compare with longitude/latitude and see if coordinates are correct or not
}*/

					
																					
																				
																		 
	 
	 
	 
	 
	 
	 
	 
	 
	 
	 
	 
	 }//end of while
	
	
	
	
	
	
	
	
	
	
	


}










