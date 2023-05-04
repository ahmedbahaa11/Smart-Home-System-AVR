# Smart Home System AVR
Smart Home System Controlled by Two MCU AVR Microcontroller using UART Communication Protocol. The system is divided into two parts.
### User Interface (First Part)
This Part Contain [ Master AVR atmega32 + EEPROM + Kypad + LCD + Servo Motor (Door) + Buzzer ]
Master AVR used for Login System and show all Features system on LCD and Read Input Signals from user using the Kypad. Based on this inputs Master AVR will Send Data To Slave AVR using UART Communication Protocol.
### Control Home (Second Part)
This Part Contain [ Slave AVR atmega32 + LM35 (Temperature Sensor) + DC Motor (Fan) + MPX4115 (Smoke Sensor) + DC Motor (Water Pump) + Servo Motor (Window) + LEDs (TV) + LDR (Light Sensor) + LED (Light Home) + LCD ]
The Slave AVR Recieve Data From Master AVR then Based on this data. Slave AVR Control The Home in Two Modes [ Manual Mode + Automatic Mode ].

# System Features:
### 1- Security System : 
 each user have a Password and at Start of System The Program ask User Name then User Password
 user have 3 tries only to entre the correct password. after 3 tries of Rong Password the System 
 will Alarm by Turn On Buzzer and Close the System. if user entre the correct Password the System 
 will Open and Open The Door by Servo Motor.
### 2- Manual Mode :
