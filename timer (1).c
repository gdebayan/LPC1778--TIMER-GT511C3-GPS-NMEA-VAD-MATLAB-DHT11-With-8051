#include "LPC177x_8x.h"

void timer0_init(void)
{
	LPC_SC->PCONP|=(1<<1);
	LPC_SC->PCLKSEL|=0X01;//DIVIDE BY 1
	LPC_IOCON->P3_25|=0X03;//SELECT P3.25 AS MATCH0 REGISTER 0(mr0)
  LPC_TIM0->MCR|=0X01;//THIS EBNALES MR0 Interrupt(match control register)
	LPC_TIM0->MCR|=(1<<1);//Timer counter will be reset automatically once MR0 matches it
	LPC_TIM0->PC&=0xFFFFFFFF;//Pre-scale counter value max
	LPC_TIM0->MR0=20;//TIMER MATCH REG VALUE; SO LESS AS PRESCAAR IS HIGH
	LPC_TIM0->TCR|=(1<<1);//RESET TIMER, CLEAR THIS OR IT WILL KEEP ON RESETTING
	LPC_TIM0->TCR&=~(1<<1);//CLEAR RESET IN TIMER
	NVIC_EnableIRQ(TIMER0_IRQn);//Enable timer0 interrupts
	LPC_TIM0->TCR|=0X01;//START PRESCALAR AND TIMER COUNTING
	
	
}

void TIMER0_IRQHandler(void)//not sure how lpc1778 will identify this as an interrupt hamdler,but online everywhere normenclature is like this
{
	 //CHECK FOR MR0 INTERRUPT
	if((LPC_TIM0->IR&=0X01)==0X01)
	{
		LPC_TIM0->IR&=~(0x01);//clear the interrupt
		//call gps function here 
	}
	
	
}
int main(void)
{
while(1)
{
}
}