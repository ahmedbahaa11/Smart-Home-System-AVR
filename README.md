# Smart Home System AVR
Smart Home System Controlled by Two MCU AVR Microcontroller using UART Communication Protocol. The system is divided into two parts.
# User Interface (First Part)
this Part Contain [ Master AVR atmega32 + EEPROM + Kypad + LCD + Servo Motor + Buzzer ]
Master AVR used for Login System and show all Features system on LCD and Read Input Signals from user using the Kypad. Based on this inputs Master AVR start Send Data To Slave AVR using UART Communication Protocol. 

# 
# System Features:
# 1- Security System : 
 each user have a Password and at Start of System The Program ask User Name then User Password
 user have 3 tries only to entre the correct password. after 3 tries of Rong Password the System 
 will Alarm by Turn On Buzzer and Close the System. if user entre the correct Password the System 
 will Open and Open The Door by Servo Motor.
# 2- Manual Mode :
