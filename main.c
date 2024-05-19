#include <reg51.h>
#include "lcd.h"
#include "ds1302.h"

sbit Buzzer=P2^5;

sbit LED1 = P2^0;  // LED pins
sbit LED2 = P2^1;
sbit LED3 = P2^2;

sbit K1=P3^1;
sbit K2=P3^0;
sbit K3=P3^2;
sbit K4=P3^3;	 //????

unsigned char AlarmSet = 0;
unsigned char AlarmTriggered = 0;
unsigned char LEDState = 0;
unsigned char ALARM[7] = { 0x05,    0x00,  0x07, 0x20,  0x05, 0x01, 0x24}; // Initialize alarm time (7:00:05)
unsigned char TempTime[3];

void Int0Configuration();
void LcdDisplay();
unsigned char SetState,SetPlace;
void Delay10ms(void);   //?? 0us

typedef unsigned int u16;

void delay(u16 j)
{
	while(j--);
}

void main()
{
	unsigned char i;

	Int0Configuration();
	LcdInit();
	Ds1302Init();
	while(1)
	{	
		if(SetState==0)
		{
			if(!AlarmTriggered){
				Ds1302ReadTime();
			}
			LcdWriteCom(0xC9); 
      LcdWriteData(' ');
			
			// Check if alarm time matches current time
			if (!AlarmTriggered && TIME[0] == ALARM[0] && TIME[1] == ALARM[1] && TIME[2] == ALARM[2])
			{
					AlarmTriggered = 1;
			}
			
			if(AlarmTriggered){
				LEDState = !LEDState; // Toggle LED state to create blinking effect
				LED1 = LEDState;
				LED2 = LEDState;
				LED3 = LEDState;
				Buzzer = ~Buzzer;
				delay(100);
			}
			
			if(AlarmTriggered && K4 == 0) {
				Delay10ms();
				if(K4==0) {
					Buzzer = 1;
					AlarmTriggered = 0;
				}
				while(K4==0);
			
			}
			
		}
		else
		{
			
			LcdWriteCom(0xC9); // Set DDRAM address to 0xC9
        switch (SetPlace)
        {
            case 0:
                LcdWriteData('S'); // Seconds
                break;
            case 1:
                LcdWriteData('m'); // Minutes
                break;
            case 2:
                LcdWriteData('H'); // Hours
                break;
            case 3:
                LcdWriteData('D'); // Day
                break;
            case 4:
                LcdWriteData('M'); // Month
                break;
            case 5:
                LcdWriteData('W'); // Weekday
                break;
            case 6:
                LcdWriteData('Y'); // Year
                break;
        }
			
			if(K1==0)
			{
				Delay10ms();
				if(K1==0)
				{
					SetPlace++;
					if(SetPlace>=7)
						SetPlace=0;					
				}

				while((i<50)&&(K1==0))
				{
					Delay10ms();
					i++;
				}
				i=0;
			}
			if(K2==0)
			{
				Delay10ms();	//????
				if(K2==0)
				{
					
					if (AlarmSet) { // Only increment ALARM if alarm is set
                        ALARM[SetPlace]++; 
                        if ((ALARM[SetPlace] & 0x0f) > 9) {
                            ALARM[SetPlace] = ALARM[SetPlace] + 6; 
                        }
                        if ((ALARM[SetPlace] >= 0x60) && (SetPlace < 2)) {
                            ALARM[SetPlace] = 0;
                        }
                        if ((ALARM[SetPlace] >= 0x24) && (SetPlace == 2)) {
                            ALARM[SetPlace] = 0;
                        }
                    }
					
					else {
					
					
					TIME[SetPlace]++;
					if((TIME[SetPlace]&0x0f)>9)					 // Change to BCD code.
					{
						TIME[SetPlace]=TIME[SetPlace]+6;
					}
					if((TIME[SetPlace]>=0x60)&&(SetPlace<2))		// Minutes and seconds can only go to 59
					{
						TIME[SetPlace]=0;
					}
					if((TIME[SetPlace]>=0x24)&&(SetPlace==2))		// Hours only go to 23
					{
						TIME[SetPlace]=0;
					}
					if((TIME[SetPlace]>=0x32)&&(SetPlace==3))		// Day only goes to 31
					{
						TIME[SetPlace]=0;	
					}
					if((TIME[SetPlace]>=0x13)&&(SetPlace==4))		// Month can only go to 12
					{
						TIME[SetPlace]=0;
					}	
					if((TIME[SetPlace]>=0x7)&&(SetPlace==5))		// Week can only go to 7
					{
						TIME[SetPlace]=1;
					}		
				}
			}
				
				while((i<50)&&(K2==0))
				{
					Delay10ms();
					i++;
				}
				i=0;
			}
				if(K4==0){
					Delay10ms();
					if(K4==0) {
						AlarmSet = ~AlarmSet;
						LcdWriteCom(0xCD); // Set DDRAM address for 'A' position
                    if (AlarmSet) {
                        LcdWriteData('A');
												for (i = 0; i < 3; i++) {
                            TempTime[i] = TIME[i];
                        }
                    } else {
                        LcdWriteData(' '); // Clear 'A' if alarm mode is done
												for (i = 0; i < 3; i++) {
                            TIME[i] = TempTime[i];
                        }
                    }
					}
					while(K4==0);
				}
				if (AlarmSet) {
				for (i = 0; i < 3; i++) {
                TIME[i] = ALARM[i]; // Update TIME for display purposes
            }
				}
		}
					LcdDisplay();	
		}
	
		}
	


void LcdDisplay()
{
	LcdWriteCom(0x80+0X40);
	LcdWriteData('0'+TIME[2]/16);				// Hour 
	LcdWriteData('0'+(TIME[2]&0x0f));				 
	LcdWriteData('-');
	LcdWriteData('0'+TIME[1]/16);				// Minutes
	LcdWriteData('0'+(TIME[1]&0x0f));	
	LcdWriteData('-');
	LcdWriteData('0'+TIME[0]/16);				// Seconds
	LcdWriteData('0'+(TIME[0]&0x0f));

	LcdWriteCom(0x80);
	LcdWriteData('2');
	LcdWriteData('0');
	LcdWriteData('0'+TIME[6]/16);			// Year
	LcdWriteData('0'+(TIME[6]&0x0f));
	LcdWriteData('-');
	LcdWriteData('0'+TIME[4]/16);			// Month
	LcdWriteData('0'+(TIME[4]&0x0f));
	LcdWriteData('-');
	LcdWriteData('0'+TIME[3]/16);			// Day
	LcdWriteData('0'+(TIME[3]&0x0f));
	LcdWriteCom(0x8D);
	LcdWriteData('0'+(TIME[5]&0x07));	// Week		 
}

void Int0Configuration()
{
	// Setup INT0
	IT0=1;	// Jump edge departure mode (falling edge)
	EX0=1;	// Turn on interrupt allow for INT0.
	EA=1;		// Turn on general interrupt
}

void Int0() interrupt 0		 
{
	Delay10ms();
	if(K3==0)
	{
		SetState=~SetState;
		SetPlace=0;
		Ds1302Init();	
	}
}

void Delay10ms(void)
{
    unsigned char a,b,c;
    for(c=1;c>0;c--)
        for(b=38;b>0;b--)
            for(a=130;a>0;a--);
}