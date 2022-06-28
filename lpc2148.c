#include<lpc214x.h>
#define ROW 4
#define COL 4
int w;
char code;
char pass[4] = {'2','2','0','7'};
int key[4];
#define time 5
char String[]="Enter the 4-digit PIN : ";
void delay(int t)
   {
        unsigned int t1,t2;
        for(t1=0;t1<t;t1++)                 
                for(t2=0;t2<1275;t2++);
   }
 
	 
 void initUART0(void)
{
	PINSEL0|=0X00000005;	//Setting P0.0 and p0.1 to RxD & TxD
	U0LCR = 0x83;
	U0DLL = 97;
	U0LCR = 0x03;
}
void u0write(char data)
{
	while(!(U0LSR&(1<<5)));
	U0THR=data;
}
void sendstring(char* stringptr)
{
	while(*stringptr!=0x00)
	{
		u0write(*stringptr);
		stringptr++;
	}
}
void initKeypad()
{
PINSEL1=0x00000000;
PINSEL2=0x00000000;
IO1DIR=0x00FF0000;
IO1DIR=(1<<22)|(1<<21)|(1<<20)|(1<<19)|(1<<18)|(1<<17)|(1<<16);

}
char keypad()
{
	char out='z';
    int i=0;
	int j = 1;
	while(j)
	{
	for(i=0;i<ROW;i++)
	{
        IO1SET=0X00FF0000;
       IO1CLR=1<<(i+16);
	if((IO1PIN&0X00100000)==0&&i==0)
	{
		delay(time);
		out ='0';
		j=0;
	}
	if((IO1PIN&0X00200000)==0&&i==0)
	{
		delay(time);
		out ='1';
		j=0;
	}
	if((IO1PIN&0X00400000)==0&&i==0)
	{
		delay(time);
		out ='2';
		j=0;

	}
	if((IO1PIN&0X00800000)==0&&i==0)  //Correct key
	{
		delay(time);
		out ='3';
		j=0;
	}

	if((IO1PIN&0X00100000)==0&&i==1)
	{
		delay(time);
		out ='4';
		j=0;
	}
	if((IO1PIN&0X00200000)==0&&i==1)
	{
		delay(time);
		out ='5';
		j=0;
	}
	if((IO1PIN&0X00400000)==0&&i==1)
	{
		delay(time);
		out ='6';
		j=0;
	}
	if((IO1PIN&0X00800000)==0&&i==1)
	{
		delay(time);
		out ='7';
		j=0;
	}

	if((IO1PIN&0X00100000)==0&&i==2)
	{
		delay(time);
		out ='8';
		j=0;
	}
	if((IO1PIN&0X00200000)==0&&i==2)
	{
		delay(time);
		out ='9';
		j=0;
	}
	if((IO1PIN&0X00400000)==0&&i==2)
	{
		delay(time);
		out ='a';
		j=0;
	}
	if((IO1PIN&0X00800000)==0&&i==2)
	{
		delay(time);
		out ='b';
		j=0;
	}

	if((IO1PIN&0X00100000)==0&&i==3)	 //cancel
	{
		delay(time);
		out ='c';
		j=0;
	}
	if((IO1PIN&0X00200000)==0&&i==3)
	{
		delay(time);
		out ='d';
		j=0;
	}
	if((IO1PIN&0X00400000)==0&&i==3)  //Ent
	{
		delay(time);
		out ='e';
		j=0;
	}
	if((IO1PIN&0X00800000)==0&&i==3)
	{
		delay(time);
		out = 'f';
		j=0;
	}
	 }
 }
	return out;
	}
int main (void)
   {
		 IO1DIR=0x0f<<16;      
        initUART0();
        while(1)
          {
						sendstring(String);
						for(w=0 ; w<4 ; w++)
						{
							code = keypad();
							u0write(code);
							key[w]=code;
							delay(1800);
						}
						if(pass[0]==key[0] && pass[1]==key[1] && pass[2]==key[2] && pass[3]==key[3])
						{
							sendstring("     Welcome to LPC-2148  ");
							sendstring("\r\n");
							break;
						}
						else
						{
							sendstring("     Wrong PIN");
							sendstring("\r\n");
							break;
						}
          } 
        return 0;
   }
	 
