# Smart Home System AVR
Smart Home System Controlled by Two MCU AVR Microcontroller using UART Communication Protocol. The system is divided into two parts.
### User Interface (First Part)
This Part Contain [ Master AVR atmega32 + EEPROM + Kypad + LCD + Servo Motor (Door) + Buzzer ]
Master AVR used for Login System and show all Features system on LCD and Read Input Signals from user using the Kypad. Based on this inputs Master AVR will Send Data To Slave AVR using UART Communication Protocol.
### Control Home (Second Part)
This Part Contain [ Slave AVR atmega32 + LM35 (Temperature Sensor) + DC Motor (Air conditioner) + MPX4115 (Smoke Sensor) + DC Motor (Water Pump) + Servo Motor (Window) + LEDs (TV) + LDR (Light Sensor) + LED (Light Home) + LCD ]
The Slave AVR Recieve Data From Master AVR then Based on this data. Slave AVR Control The Home in Two Modes [ Manual Mode + Automatic Mode ].

# System Features:
### 1- Security System : 
each user have a Password Saved in EEPROM by I2C Communication Protocol. at Start of System The Program ask user Name then User Password
user have Three tries only to entre the correct password. after Three tries of Rong Password the System 
will Alarm by Turn On Buzzer and Close the System. if user entre the correct Password the System 
will Open and Open The Door by Servo Motor.
### 2- Manual Mode : 
In this Mode The System of Home Full Controlled by the User. 
Master AVR will Display all Systems on LCD [ TV + Light + Air conditioner + Pumb ]. User will choose any one form thim by KYPAD and chooses Turn ON or OFF . then Master AVR will Send this Data to Slave AVR. Slave Will Run Functions to Turn ON or OFF the Target System. Slave AVR will Show the Status of Home on LCD. ( TV [ON-OFF] + Light [ON-OFF] + Air conditioner [ON-OFF] + Pumb [ON-OFF] ).
### 3- Automatic Mode : 
In this Mode The System of Home Full Controlled Automaticly by AVR.
Slave AVR When Recieve Automatic Mode will control the Home by Reading of all Sensors.
##### Air conditioner -> Controlled by Reading of Temperature Sensor, if Temperature More than 25 C System Will Open Air conditioner and Close the Window by turn on Servo Motor with angle 0. else if Temperature Less than 25 C System Will Close Air conditioner and Open the Window by turn on Servo Motor with angle 180.   
##### Light -> Controlled by Reading of LDR Sensor, if Light of Sun is High System will turn OFF the Light of Home, else if Light of Sun is Low System will turn ON the Light of Home.
##### Water Pumb -> Fire Alarm System Controlled by Reading of Smoke Sensor, if Smoke Sensor Readind More than 50 System Will Open The Water Pumb and Turn on Buzzer and show Fire!! on LCD.
##### TV -> if User Entre the Home From Door TV will Open automaticly . and if user leave the home TV will Turn OFF.
### 4- Change Password :
