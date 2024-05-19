#ifndef __LCD_H_
#define __LCD_H_
/**********************************
Define this when using 4-bit data transmission.
Uncomment this definition for 8-bit mode.
**********************************/
#define LCD1602_4PINS  

/**********************************
Include header files
**********************************/
#include <reg51.h>

//---Redefine keywords---//
#ifndef uchar
#define uchar unsigned char
#endif

#ifndef uint 
#define uint unsigned int
#endif

/**********************************
Pin definitions
**********************************/
#define LCD1602_DATAPINS P0
sbit LCD1602_E=P2^7;
sbit LCD1602_RW=P2^5;
sbit LCD1602_RS=P2^6;

/**********************************
Function declarations
**********************************/
/* Delay function for 51 microcontroller with 12MHz clock */
void Lcd1602_Delay1ms(uint c); // Error 0us
/* LCD1602 write 8-bit command function */
void LcdWriteCom(uchar com);
/* LCD1602 write 8-bit data function */ 
void LcdWriteData(uchar dat);
/* LCD1602 initialization function */ 
void LcdInit();

#endif
