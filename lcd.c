#include "lcd.h"  // Include header file for LCD functions

// Function: Lcd1602_Delay1ms
// Description: Creates a delay of approximately 1 millisecond.
// Input: c (Number of times to repeat the delay loop)
// Output: None
void Lcd1602_Delay1ms(uint c) { 
    uchar a, b;   // Declare loop counters
    for (; c > 0; c--) {   // Outer loop: Repeat 'c' times
        for (b = 199; b > 0; b--) {  // Middle loop: Repeat 199 times
            for (a = 1; a > 0; a--);  // Inner loop: Execute once (for fine-tuning delay)
        }
    }
}

// Function: LcdWriteCom
// Description: Writes a command byte to the LCD1602.
// Input: com (The command byte to send)
// Output: None
#ifndef LCD1602_4PINS  // If NOT in 4-bit mode (i.e., 8-bit mode)
void LcdWriteCom(uchar com) {
    LCD1602_E = 0;      // Pull enable (E) pin low
    LCD1602_RS = 0;     // Set register select (RS) for command (0)
    LCD1602_RW = 0;     // Set read/write (RW) for write (0)

    LCD1602_DATAPINS = com;    // Send the command byte on the data pins
    Lcd1602_Delay1ms(1);       // Short delay for data setup time

    LCD1602_E = 1;      // Pulse the enable (E) pin high to initiate write
    Lcd1602_Delay1ms(5);       // Hold E high for a sufficient time
    LCD1602_E = 0;      // Pull E low to complete the write
}
#else  // If in 4-bit mode
void LcdWriteCom(uchar com) {
    LCD1602_E = 0;      // Pull E low
    LCD1602_RS = 0;     // Select command mode
    LCD1602_RW = 0;     // Select write mode

    LCD1602_DATAPINS = com;    // Send high nibble of the command (doesn't need shifting)
    Lcd1602_Delay1ms(1);       // Short delay

    LCD1602_E = 1;      // Pulse E high to write high nibble
    Lcd1602_Delay1ms(5);       // Hold E high
    LCD1602_E = 0;      // Pull E low

    LCD1602_DATAPINS = com << 4; // Shift low nibble of the command to high nibble position
    Lcd1602_Delay1ms(1);       // Short delay

    LCD1602_E = 1;      // Pulse E high to write low nibble
    Lcd1602_Delay1ms(5);       // Hold E high
    LCD1602_E = 0;      // Pull E low
}
#endif 


// Function: LcdWriteData
// Description: Writes a data byte to the LCD1602.
// Input: dat (The data byte to send)
// Output: None
#ifndef LCD1602_4PINS  // If NOT in 4-bit mode (i.e., 8-bit mode)
void LcdWriteData(uchar dat) { 
    LCD1602_E = 0;      // Pull E low
    LCD1602_RS = 1;     // Set RS for data (1)
    LCD1602_RW = 0;     // Set RW for write (0)
    
    LCD1602_DATAPINS = dat;    // Send the data byte
    Lcd1602_Delay1ms(1);       // Short delay

    LCD1602_E = 1;      // Pulse E high to initiate write
    Lcd1602_Delay1ms(5);       // Hold E high
    LCD1602_E = 0;      // Pull E low
}
#else // If in 4-bit mode
void LcdWriteData(uchar dat) {
   // Same as LcdWriteCom, but with LCD1602_RS = 1 (data mode) 
   // (code omitted for brevity, since it's identical to LcdWriteCom's 4-bit mode)
	  LCD1602_E = 0;      // Pull E low
    LCD1602_RS = 1;     // Select command mode
    LCD1602_RW = 0;     // Select write mode

    LCD1602_DATAPINS = dat;    // Send high nibble of the command (doesn't need shifting)
    Lcd1602_Delay1ms(1);       // Short delay

    LCD1602_E = 1;      // Pulse E high to write high nibble
    Lcd1602_Delay1ms(5);       // Hold E high
    LCD1602_E = 0;      // Pull E low

    LCD1602_DATAPINS = dat << 4; // Shift low nibble of the command to high nibble position
    Lcd1602_Delay1ms(1);       // Short delay

    LCD1602_E = 1;      // Pulse E high to write low nibble
    Lcd1602_Delay1ms(5);       // Hold E high
    LCD1602_E = 0;      // Pull E low
}
#endif

// Function: LcdInit
// Description: Initializes the LCD1602.
// Input: None
// Output: None
#ifndef LCD1602_4PINS  // If NOT in 4-bit mode (i.e., 8-bit mode)
void LcdInit() {
    LcdWriteCom(0x38);  // Function Set: 8-bit, 2 lines, 5x8 font
    LcdWriteCom(0x0F);  // Display on, cursor on, blink on
    LcdWriteCom(0x06);  // Entry Mode Set: Increment cursor, no shift
    LcdWriteCom(0x01);  // Clear display
    LcdWriteCom(0x80);  // Set DDRAM address to 0x00 (start of first line)
}
#else  // If in 4-bit mode
void LcdInit() {
    LcdWriteCom(0x32);  // Special 4-bit mode initialization
    LcdWriteCom(0x28);  // Function Set: 4-bit, 2 lines, 5x8 font
    LcdWriteCom(0x0F);  // Display on, cursor on, blink on
    LcdWriteCom(0x06);  // Entry Mode Set: Increment cursor, no shift
    LcdWriteCom(0x01);  // Clear display
    LcdWriteCom(0x80);  // Set DDRAM address to 0x00 (start of first line)
}
#endif
