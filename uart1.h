#include "LPC177x_8x.h"

void uart1_init(void)
{
	LPC_SC->PCONP|1u<<4;
	//enable uart1
	LPC_SC->PCLKSEL|=1U;//DIVIDE PCLK BY 1
	
	LPC_UART1->LCR|=1U<<7;//ENABLE DLAB
	LPC_UART1->DLL|=0X01; //SET SOME BAUD RATE	
	//LPC_UART1->DLM=??
  //LPC_UART1->FDR??
	//END OF BAUD RATE CALCULATIONS
  
LPC_UART1->LCR&=~(1U<<7);//DISABLE DLAB
LPC_UART1->LCR|=3U;//8-BITCHARACTER LENGTH
	
LPC_UART1->FCR|=1U;
//ENABLE FIFO REG
//LPC_UART1->IER|=3u;//to ENABLE INTERRUPTS
LPC_IOCON->P0_15|=1U;
LPC_IOCON->P0_16|=1;//ENABLE IOCON REGISTERS FOR UART OPERATION
	
		
}//END OF INITIALISATION
uint8_t c;

 uint8_t uart1_rec(void)
{
	while(!(LPC_UART1->LSR&1U));

		c=LPC_UART1->RBR;
	//LPC_UART1->LSR&=~(1u);//clear rdr bit//not sure if reqdd
	return c;
}

void uart1_tra(uint8_t x)
{
LPC_UART1->THR=x;
while(!(LPC_UART1->LSR&(1<<5)));
//LPC_UART1->LSR&=~(uint32_t)1<<5;//clear thre bit//not sure if reqdd	
}



	