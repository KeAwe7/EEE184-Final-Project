#ifndef __DS1302_H_
#define __DS1302_H_

#include<reg51.h>
#include<intrins.h>

#ifndef uchar
#define uchar unsigned char
#endif

#ifndef uint 
#define uint unsigned int
#endif

//---Define the IO port used by the ds1302--//
sbit DSIO=P3^4;
sbit RST=P3^5;
sbit SCLK=P3^6;

//---Define the global function--//
void Ds1302Write(uchar addr, uchar dat);
uchar Ds1302Read(uchar addr);
void Ds1302Init();
void Ds1302ReadTime();

//---Add global change amount-//
extern uchar TIME[7];

#endif