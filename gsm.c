#include <LPC21xx.H> 


void PLL_INIT()
{
 PLLCON = 0x01;   
 PLLCFG = 0x24;  
 PLLFEED = 0xAA;  
 PLLFEED = 0x55;
 
 while(!(PLLSTAT & 0x00000400)); 
 
 PLLCON = 0x03;   
 PLLFEED = 0xAA; 
 PLLFEED = 0x55;
 VPBDIV = 0x01; 
}

void delay(unsigned int count)
{
	unsigned int i,j;
	for(i=0;i<count;i++)
			for(j=0;j<1275;j++);
}
void INIT_UART()
{
PINSEL0=0x05;
U0LCR=0x83;
U0DLL=135;		  
U0DLM=1;

U0LCR&=0x0F;
}

void U0WRITE(char data)
{
while(!(U0LSR & (1<<5)));
U0THR=data;
}

void transmit(char *address )
{

while(*address !=0x00)
{
U0WRITE(*address);
address++;
   
}

}

char receive_data (void) 
 {     
   while (!(U0LSR & 0x01));
     return(U0RBR);
 
}





  int main()
  {
	 PLL_INIT();
	 INIT_UART();
	 
	 transmit("ATE0\r\n");
	 delay(3000);
	 transmit("AT+CMGF=1\r\n");
	 delay(500);
	 transmit("AT+CMGS=\"1234567890\"\r\n");
	 delay(500);
	 transmit("GSM INterfacing");
	 delay(500);
	 U0WRITE(0x1A);
	 while(1);
  }

