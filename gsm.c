#include <LPC21xx.H> 


void PLL_INIT()// initialise PLL clock
{
 PLLCON = 0x01;   // Enable PLL
 PLLCFG = 0x24;  // Configure to desired clock rate
 PLLFEED = 0xAA;  //feed Sequence
 PLLFEED = 0x55;  //feed sequence
 
 while(!(PLLSTAT & 0x00000400)); // wailt to lock PLL
 
 PLLCON = 0x03;   // Connect PLL
 PLLFEED = 0xAA; //feed sequence
 PLLFEED = 0x55; //feed sequence
 VPBDIV = 0x01; // PCLK=CCLK
}

void delay(unsigned int count) // function to generate delay
{
	unsigned int i,j;
	for(i=0;i<count;i++)
	{
		for(j=0;j<1275;j++)
		{
		}
	}
}
void INIT_UART()// function to initialse UART communication
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
	 transmit("AT+CMGS=\"1234567890\"\r\n");// mobile number of next person replace with 1234567890
	 delay(500);
	 transmit("GSM INterfacing");// text to be transmited to next person
	 delay(500);
	 U0WRITE(0x1A);
	 while(1);
  }

