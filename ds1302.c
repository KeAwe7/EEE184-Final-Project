#include"ds1302.h"

//--- DS1302 write and read address commands for hours, minutes, and seconds --//
//---Seconds minutes hours days months anniversaries Lowest read/write bit;-------//
uchar code READ_RTC_ADDR[7] = {0x81, 0x83, 0x85, 0x87, 0x89, 0x8b, 0x8d};
uchar code WRITE_RTC_ADDR[7] = {0x80, 0x82, 0x84, 0x86, 0x88, 0x8a, 0x8c};


// For DoW (Days of the Week): Mon = 1, Tue = 2, Wed = 3, Thu = 4, Fri = 5, Sat = 6, Sun = 7 //
// Order is SECONDS, MINUTES, HOURS,  DAY, MONTH,  DoW, YEAR //
uchar TIME[7] = { 0,    0x00,  0x07, 0x20,  0x05, 0x01, 0x24};

void Ds1302Write(uchar addr, uchar dat)
{
	uchar n;
	RST = 0;
	_nop_();

	SCLK = 0;// First set SCLK low.
	_nop_();
	RST = 1; // Then set RST(CE) high.
	_nop_();

	for (n=0; n<8; n++)// Start transmitting the eight-bit address command
	{
		DSIO = addr & 0x01;// Data start transmitting from low bit
		addr >>= 1;
		SCLK = 1;// DS1302 reads data when data is on the rising edge
		_nop_();
		SCLK = 0;
		_nop_();
	}
	for (n=0; n<8; n++)// Write 8-bit data
	{
		DSIO = dat & 0x01;
		dat >>= 1;
		SCLK = 1;// DS1302 reads data when data is on the rising edge
		_nop_();
		SCLK = 0;
		_nop_();
	}

	RST = 0;// End of data transfer
	_nop_();
}

uchar Ds1302Read(uchar addr)
{
	uchar n,dat,dat1;
	RST = 0;
	_nop_();

	SCLK = 0;// Put SCLK low first.
	_nop_();
	RST = 1;// Then set RST(CE) high.
	_nop_();

	for(n=0; n<8; n++)// Start transmitting the eight-bit address command
	{
		DSIO = addr & 0x01;// Data start transmitting from low bit
		addr >>= 1;
		SCLK = 1;// DS1302 reads data when data is on the rising edge
		_nop_();
		SCLK = 0;// Data on falling edge, DS1302 places data
		_nop_();
	}
	_nop_();
	for(n=0; n<8; n++)// Read 8-bit data
	{
		dat1 = DSIO;// Start receiving from the lowest bit
		dat = (dat>>1) | (dat1<<7);
		SCLK = 1;
		_nop_();
		SCLK = 0;// DS1302 places data on falling edge
		_nop_();
	}

	RST = 0;
	_nop_();	// The following is the stabilization time for DS1302 reset, required.
	SCLK = 1;
	_nop_();
	DSIO = 0;
	_nop_();
	DSIO = 1;
	_nop_();
	return dat;
}

void Ds1302Init()
{
	uchar n;
	Ds1302Write(0x8E,0X00);		 // Disable write protection, that is, turn off the write protection function
	for (n=0; n<7; n++)// Write 7 bytes of clock signals: minutes seconds hours days months year
	{
		Ds1302Write(WRITE_RTC_ADDR[n],TIME[n]);
	}
	Ds1302Write(0x8E,0x80);		 // Turn on write-protect function
}

void Ds1302ReadTime()
{
	uchar n;
	for (n=0; n<7; n++)// Read 7 bytes of clock signal: minute second hour day month year
	{
		TIME[n] = Ds1302Read(READ_RTC_ADDR[n]);
	}

}


