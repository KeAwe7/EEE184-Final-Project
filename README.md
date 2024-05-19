**Project Title**: Enhanced Alarm Clock with DS1302 RTC and LCD1602 Display

**Description**:

This project implements an alarm clock using an 8051 microcontroller, a DS1302 real-time clock (RTC) module, and an LCD1602 display. It allows the user to:

-View the current time (hours, minutes, seconds).
-Set the time.
-Set an alarm time.
-Dismiss the alarm.

**Hardware Requirements**:

-8051 microcontroller development board
-DS1302 RTC module
-LCD1602 display module (with appropriate driver code - not included here)
-Buzzer connected to P2.5 (for alarm indication)
-3 LEDs connected to P2.0, P2.1, P2.2 (for alarm indication)
-4 push buttons (K1, K2, K3, K4) connected to P3.0, P3.1, P3.2, P3.3 respectively.
-Software Requirements:

Keil C compiler or similar toolchain for 8051 development
Code Structure:

-main.c: Contains the main program logic.
-ds1302.c and ds1302.h: Handles communication with the DS1302 RTC module.
-lcd.c and lcd.h: Provides functions for LCD1602 control.

**Functionality**:

**Time Display**:

In normal mode, the LCD displays the initialized date and time read from the DS1302 RTC.
The time is formatted as HH-MM-SS.
The date is formatted as YY-MM-DD DoW

**Setting Mode (K3 Button)**:

Pressing K3 enters setting mode, stopping the time update and displaying an indicator letter ('S', 'M', 'H', etc.) at position 0xC9 to show which component is being edited.
K1 and K2 buttons are used to adjust the time value for the selected component.

**Alarm Mode (K4 Button)**:

In setting mode, pressing K4 toggles the alarm mode.
When the alarm mode is on, the letter 'A' is displayed at position 0xCD.
The alarm time is initially set to 00:00:00 and can be modified using the same K1 and K2 buttons.

**Alarm Trigger**:

When the alarm is set and the current time matches the alarm time, the buzzer buzzes and the LEDs blink.
Pressing K4 stops the alarm.

How to Use:

1. Compile and flash the code to your 8051 microcontroller.
2. Connect the hardware components as described above.
3. Press K3 to enter setting mode and adjust the time using K1 and K2.
4. Press K4 to toggle the alarm and set the alarm time.
5. Press K4 again to exit alarm mode.
6. Press K3 again to exit setting mode.
7. The alarm will trigger when the set time is reached.
8. Press K4 to stop the alarm.
