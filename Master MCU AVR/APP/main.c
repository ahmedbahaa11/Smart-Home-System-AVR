/*=================================================================================*/
/*  Program     : Smart Home AVR Project                                           */
/*  Description : This Code For Master MCU at User Interface Board                 */
/*  Author      : Ahmed Bahaa Taha Nasr. Embedded SW Engineer                      */
/*  Date        : 28/4/2023                                                        */
/*  Linkedin    : https://www.linkedin.com/in/ahmed-bahaa1/                        */
/*  Git account : https://github.com/ahmedbahaa11                                  */
/*  mail        : ahmedbahaataha7@gmil.com                                         */
/*=================================================================================*/
/* Include Header Files From LIB */
#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"
/* Include Header Files From MCAL Layer */
#include "../MCAL/DIO/DIO_Interface.h"
#include "../MCAL/I2C/I2C_Interface.h"
#include"../MCAL/TIMERS/TIMER1/TIMER1_Interface.h"
#include"../MCAL/GIE/GIE_Interface.h"
#include"../MCAL/USART/USART_Interface.h"
/* Include Header Files From HAL Layer */
#include "../HAL/LCD/LCD_Interface.h"
#include "../HAL/EEPROM/EEPROM_Interface.h"
#include "../HAL/KPAD/KPAD_Interface.h"
#include"../HAL/SERVO_MOTOR/SERVO_Interface.h"
#define F_CPU 8000000UL
#include <util/delay.h>
/****** Functions Prototypes ******/
void StartProgram_AhmedBahaa (void);
void SmartHome_ManualMode    (void);
void SmartHome_AutoMode      (void);
void SelectUserName 		 (void);
u16  GetPassword    		 (void);
void EditPassword            (void);
void Control_TV    		 	 (void);
void Control_Light  		 (void);
void Control_Fan    		 (void);
void Control_Pumb   		 (void);
void OpenDoor  				 (void);
void CloseDoor 				 (void);
/******** Global Variables ********/
u8 Exit_EditPassFlag = 1 ;
u8 EEPROM_PASSWORD = 0 ;
u8 ModeKey = 0 ;
u8 User = 0 ;
int main()
{
	/*===========================================*/
	/*======   APP EEPROM Set Passwords   =======*/
	I2C_voidMasterInit(0);
	EEPROM_voidSendDataByte(1,123);		// Ahmed Password
	EEPROM_voidSendDataByte(2,147);		// Wafa Password
	EEPROM_voidSendDataByte(3,111);		// Islam Password
	EEPROM_voidSendDataByte(4,222);		// Lolo Password
	/*===========================================*/
	/*=========   APP Local Variables   =========*/
	u16 PASSWORD = 0 ;
	/*===========================================*/
	/*=========   APP Initializations   =========*/
	TIMER1_voidInit ();
	LCD_voidInit();
	KPAD_voidInit();
	USART_voidInit ();
	DIO_voidSetPinDirection(PORTD,PIN6,OUTPUT);  // Buzzer OUTPUT
	DIO_voidSetPinValue(PORTD,PIN6,LOW);		 // Buzzer OFF
	/*===========================================*/
	/*=========        APP Start        =========*/
	StartProgram_AhmedBahaa();					 // MY LCD Start Program
	SelectUserName();							 // Select User
	LCD_voidClearLine(0);
	LCD_voidClearLine(1);
	LCD_voidGoTo_XY (0,0);
	LCD_voidWriteString ("Enter Password :");
	LCD_voidGoTo_XY (1,13);
	LCD_voidWriteString ("[1]");
	while (1)
	{
		for ( u8 i=0 ; i < 3 ; i++ )
		{
			PASSWORD = GetPassword();
			if( PASSWORD == EEPROM_PASSWORD )
			{
				USART_voidSendData('Z');
				LCD_voidClearLine(0);
				LCD_voidClearLine(1);
				OpenDoor();
				LCD_voidGoTo_XY (0,1);
				LCD_voidWriteString ("Door is OPened");
				LCD_voidGoTo_XY (1,3);
				LCD_voidWriteString ("Welcome..");
				_delay_ms(1000);

				while(1)
				{
					if ( Exit_EditPassFlag == 0 )
					{
						LCD_voidClearLine(0);
						LCD_voidClearLine(1);
						LCD_voidGoTo_XY (0,0);
						LCD_voidWriteString ("Session Expire!!");
						_delay_ms(700);
						LCD_voidClearLine(0);
						LCD_voidClearLine(1);
						LCD_voidGoTo_XY (0,0);
						LCD_voidWriteString ("Enter Password :");
						LCD_voidGoTo_XY (1,13);
						LCD_voidWriteString ("[1]");
						i = -1 ;
						Exit_EditPassFlag = 1 ;
						switch(User)
						{
							case 1 :	 	EEPROM_PASSWORD = EEPROM_voidReadDataByte(1);	break;
							case 2 : 		EEPROM_PASSWORD = EEPROM_voidReadDataByte(2);	break;
							case 3 : 		EEPROM_PASSWORD = EEPROM_voidReadDataByte(3);	break;
							case 4 : 		EEPROM_PASSWORD = EEPROM_voidReadDataByte(4);	break;
							default  :														break;
						}
						break ;
					}
					LCD_voidGoTo_XY (0,0);
					LCD_voidWriteString ("1-Manual  2-Auto");
					LCD_voidGoTo_XY (1,0);
					LCD_voidWriteString ("3-Edit Password");
					ModeKey = KPAD_u8GetPressedKey ();
					if ( ModeKey != 0xff  )
					{
						if( ModeKey == '1' )
						{	SmartHome_ManualMode();		}

						else if ( ModeKey == '2' )
						{	SmartHome_AutoMode();		}
						else if ( ModeKey == '3' )
						{	EditPassword();	 		    }
					}
				}
			}
			else
			{
				if (i==2)
				{
					LCD_voidClearLine(0);
					LCD_voidClearLine(1);
					LCD_voidGoTo_XY (0,3);
					LCD_voidWriteString ("7aramy !!");
					LCD_voidGoTo_XY (1,0);
					LCD_voidWriteString ("Restart System..");
					USART_voidSendData('N');
					DIO_voidSetPinValue(PORTD,PIN6,HIGH);		// Buzzer ON
					CloseDoor();
					break;
				}
				else
				{
					LCD_voidClearLine(0);
					LCD_voidClearLine(1);
					LCD_voidGoTo_XY (0,0);
					LCD_voidWriteString ("Try again..");
					LCD_voidGoTo_XY (1,13);
					LCD_voidWriteString ("[");
					LCD_voidWrite_u32Number(i+2);
					LCD_voidWriteString ("]");
				}
			}
		}
	}
}
/*=============================================================================*/
void StartProgram_AhmedBahaa (void)
{
	LCD_voidGoTo_XY (0,0);
	LCD_voidWriteString ("Ahmed Bahaa Nasr");
	LCD_voidGoTo_XY (1,3);
	LCD_voidWriteString ("ES Engineer");
	_delay_ms(700);
	LCD_voidClearLine(0);
	LCD_voidClearLine(1);
	LCD_voidGoTo_XY (0,1);
	LCD_voidWriteString (" Welcome To MY");
	LCD_voidGoTo_XY (1,0);
	LCD_voidWriteString ("  Smart Home :) ");
	_delay_ms(600);
}
/*=============================================================================*/
void SelectUserName (void)
{
	u8 UserKey = 0 ;
	LCD_voidClearLine(0);
	LCD_voidClearLine(1);
	LCD_voidGoTo_XY (0,0);
	LCD_voidWriteString ("(1)Ahmed (2)Wafa");
	LCD_voidGoTo_XY (1,0);
	LCD_voidWriteString ("(3)Islam (4)Lolo");
	while(1)
	{
		UserKey = KPAD_u8GetPressedKey ();
		if ( UserKey != 0xff  )
		{
			switch(UserKey)
			{
				case '1' :	User = 1 ; 	EEPROM_PASSWORD = EEPROM_voidReadDataByte(1);	break;
				case '2' : 	User = 2 ;	EEPROM_PASSWORD = EEPROM_voidReadDataByte(2);	break;
				case '3' : 	User = 3 ;	EEPROM_PASSWORD = EEPROM_voidReadDataByte(3);	break;
				case '4' : 	User = 4 ;	EEPROM_PASSWORD = EEPROM_voidReadDataByte(4);	break;
				default  :														break;
			}
		}
		if( EEPROM_PASSWORD != 0 )
			break;
	}
}
/*=============================================================================*/
u16 GetPassword (void)
{
	LCD_voidGoTo_XY (1,0);
	u16 Password = 0 ;
	u16 Copy_u8Temp = 0 ;
	u8 Local_u8PressedKey ;
	while(1)
	{
		Local_u8PressedKey = KPAD_u8GetPressedKey ();
		if ( Local_u8PressedKey != 0xff  )
		{
			if( Local_u8PressedKey >= '0' && Local_u8PressedKey <= '9' )
			{
				LCD_voidWriteChar('*');
				Copy_u8Temp = Copy_u8Temp*10 + (Local_u8PressedKey - '0') ;
				Password = Copy_u8Temp ;
			}
			else if ( Local_u8PressedKey == '=' )
			{
				break ;
			}
		}
	}
	return Password ;
}
/*=============================================================================*/
void EditPassword (void)
{
	u16 NewPassword_1 = 0 ;
	u16 NewPassword_2 = 0 ;
	u8 Counter = 0 ;
	LCD_voidClearLine(0);
	LCD_voidClearLine(1);
	LCD_voidGoTo_XY (0,0);
	LCD_voidWriteString ("New Password : ");
	NewPassword_1 = GetPassword();
	LCD_voidClearLine(0);
	LCD_voidClearLine(1);
	LCD_voidGoTo_XY (0,0);
	LCD_voidWriteString ("Confirm New Pass ");
	LCD_voidGoTo_XY (1,13);
	LCD_voidWriteString ("[1]");
	NewPassword_2 = GetPassword();
	Counter = 0 ;
	ModeKey = 0 ;
	while( Counter < 3)
	{
		if( NewPassword_2 == NewPassword_1 )
		{
			EEPROM_voidSendDataByte(User,NewPassword_2);
			LCD_voidClearLine(0);
			LCD_voidClearLine(1);
			LCD_voidGoTo_XY (0,0);
			LCD_voidWriteString (" Done Your Pass");
			LCD_voidGoTo_XY (1,0);
			LCD_voidWriteString (" Is Updated..");
			Counter = 0 ;
			Exit_EditPassFlag = 0 ;
			_delay_ms(700);
			break;
		}
		else
		{
			if(Counter == 2)
			{
				LCD_voidClearLine(0);
				LCD_voidClearLine(1);
				LCD_voidGoTo_XY (0,0);
				LCD_voidWriteString ("Pass NOT Update");
				LCD_voidGoTo_XY (1,0);
				LCD_voidWriteString ("No More Tries");
				_delay_ms(600);
				Counter ++ ;
			}
			else
			{
				LCD_voidClearLine(0);
				LCD_voidClearLine(1);
				LCD_voidGoTo_XY (0,0);
				LCD_voidWriteString ("Pass NOT Match");
				_delay_ms(350);
				LCD_voidGoTo_XY (0,0);
				LCD_voidWriteString ("New Pass Again");
				LCD_voidGoTo_XY (1,13);
				LCD_voidWriteString ("[");
				LCD_voidWrite_u32Number(Counter+2);
				LCD_voidWriteString ("]");
				NewPassword_2 = GetPassword();
				Counter ++ ;
			}
		}
	}
}
/*=============================================================================*/
void SmartHome_ManualMode (void)
{
	u8 ActuatorKey = 0 ;
	USART_voidSendData('M');
	LCD_voidClearLine(0);
	LCD_voidClearLine(1);
	while(1)
	{
		LCD_voidGoTo_XY (0,0);
		LCD_voidWriteString ("(1)TV   (2)Light ");
		LCD_voidGoTo_XY (1,0);
		LCD_voidWriteString ("(3)Fan  (4)Pump");
		ActuatorKey = KPAD_u8GetPressedKey ();
		if ( ActuatorKey != 0xff  )
		{
			if ( ActuatorKey == '1' )
			{ Control_TV(); }
			else if ( ActuatorKey == '2' )
			{ Control_Light(); }
			else if ( ActuatorKey == '3' )
			{ Control_Fan(); }
			else if ( ActuatorKey == '4' )
			{ Control_Pumb(); }
			else
			{	USART_voidSendData('#'); ModeKey = 0 ;	break;	}
		}
	}
}
/*=============================================================================*/
void SmartHome_AutoMode (void)
{
	u8 ExitAutoKey = 0 ;
	USART_voidSendData('A');
	LCD_voidClearLine(0);
	LCD_voidClearLine(1);
	LCD_voidGoTo_XY (0,0);
	LCD_voidWriteString (" Your Home is");
	LCD_voidGoTo_XY (1,0);
	LCD_voidWriteString ("Smart Automatic");
	while(1)
	{
		ExitAutoKey = KPAD_u8GetPressedKey ();
		if ( ExitAutoKey != 0xff  )
		{
			if ( ExitAutoKey == '#' )
			{
				USART_voidSendData('#');
				LCD_voidClearLine(0);
				LCD_voidClearLine(1);
				ModeKey = 0 ;
				break;
			}
		}
	}
}
/*=============================================================================*/
void Control_TV (void)
{
	u8 TVKey = 0 ;
	USART_voidSendData('T');
	LCD_voidClearLine(0);
	LCD_voidClearLine(1);
	LCD_voidGoTo_XY (0,0);
	LCD_voidWriteString ("(1)TV: ON ");
	LCD_voidGoTo_XY (1,0);
	LCD_voidWriteString ("(0)TV: OFF");
	while(1)
	{
		TVKey = KPAD_u8GetPressedKey ();
		if ( TVKey != 0xff  )
		{
			if ( TVKey == '1' )
			{
				USART_voidSendData('1');
				LCD_voidClearLine(0);
				LCD_voidClearLine(1);
				break;
			}
			else if ( TVKey == '0' )
			{
				USART_voidSendData('0');
				LCD_voidClearLine(0);
				LCD_voidClearLine(1);
				break;
			}
		}
	}
}
/*=============================================================================*/
void Control_Light (void)
{
	u8 LightKey = 0 ;
	USART_voidSendData('L');
	LCD_voidClearLine(0);
	LCD_voidClearLine(1);
	LCD_voidGoTo_XY (0,0);
	LCD_voidWriteString ("(1)Light: ON ");
	LCD_voidGoTo_XY (1,0);
	LCD_voidWriteString ("(0)Light: OFF");
	while(1)
	{
		LightKey = KPAD_u8GetPressedKey ();
		if ( LightKey != 0xff  )
		{
			if ( LightKey == '1' )
			{
				USART_voidSendData('1');
				LCD_voidClearLine(0);
				LCD_voidClearLine(1);
				break;
			}
			else if ( LightKey == '0' )
			{
				USART_voidSendData('0');
				LCD_voidClearLine(0);
				LCD_voidClearLine(1);
				break;
			}
		}
	}
}
/*=============================================================================*/
void Control_Fan (void)
{
	u8 FanKey = 0 ;
	USART_voidSendData('F');
	LCD_voidClearLine(0);
	LCD_voidClearLine(1);
	LCD_voidGoTo_XY (0,0);
	LCD_voidWriteString ("(1)Fan: ON ");
	LCD_voidGoTo_XY (1,0);
	LCD_voidWriteString ("(0)Fan: OFF");
	while(1)
	{
		FanKey = KPAD_u8GetPressedKey ();
		if ( FanKey != 0xff  )
		{
			if ( FanKey == '1' )
			{
				USART_voidSendData('1');
				LCD_voidClearLine(0);
				LCD_voidClearLine(1);
				break;
			}
			else if ( FanKey == '0' )
			{
				USART_voidSendData('0');
				LCD_voidClearLine(0);
				LCD_voidClearLine(1);
				break;
			}
		}
	}
}
/*=============================================================================*/
void Control_Pumb (void)
{
	u8 PumpKey = 0 ;
	USART_voidSendData('P');
	LCD_voidClearLine(0);
	LCD_voidClearLine(1);
	LCD_voidGoTo_XY (0,0);
	LCD_voidWriteString ("(1)Pump: ON ");
	LCD_voidGoTo_XY (1,0);
	LCD_voidWriteString ("(0)Pump: OFF");
	while(1)
	{
		PumpKey = KPAD_u8GetPressedKey ();
		if ( PumpKey != 0xff  )
		{
			if ( PumpKey == '1' )
			{
				USART_voidSendData('1');
				LCD_voidClearLine(0);
				LCD_voidClearLine(1);
				break;
			}
			else if ( PumpKey == '0' )
			{
				USART_voidSendData('0');
				LCD_voidClearLine(0);
				LCD_voidClearLine(1);
				break;
			}
		}
	}
}
/*=============================================================================*/
void OpenDoor (void)
{
		SERVO_voidRotateSpecificAngle_OC1A ( 180 );
}
/*=============================================================================*/
void CloseDoor (void)
{
		SERVO_voidRotateSpecificAngle_OC1A ( 0 );
}
/*=============================================================================*/
