/*
 * main.c
 *
 *  Created on: 24/8/2023
 *      Author: Omar Saeed
 */

#include "task.h"

#define Motor_Speed    76
#define Stepper_Angle  18

void A_Timer0_Execution(void);

u8 min=0;
u8 sec=0;
u8 hour=0;

int main()
{
	u8 type=0;
	M_UART_Void_UARTInit();
	H_DCMotor_Void_DCMotorInit();
	H_Stepper_Void_StepperInit();
	M_UART_Void_UARTSetBaudRate(9600);
	M_GIE_Void_GlobalInterruptEnable();
	M_Timer_Void_TimerInit(TIMER0_CHANNEL);
	M_Timer_Void_TimerSetTime(TIMER0_CHANNEL,1000);
	M_Timer_Void_SetCallBack(TIMER0_CHANNEL,A_Timer0_Execution);
	H_LCD_Void_LCDInit();
	u8 counter=0;
	while(1)
	{
		for (counter=0;counter<8;counter++)
		{

			type = M_UART_Void_UARTRec();

		}

			while(type == 'E')
			{
				M_Timer_Void_TimerStart(TIMER0_CHANNEL);
				printTimer();
				if(sec > 59)
				{
					sec=0;
					min++;
				}
				if(min > 59)
				{
					min = min - 60;
					hour++;
				}
				Start_Motors();
			}
	}
	return 0;
}

/**********************************************************************************************************************/
/* FUNCTION OBJECTIVE -> TIMER 0 EXCUTION FUNCTION                                                                    */
/**********************************************************************************************************************/
void A_Timer0_Execution(void)
{
sec++;
}
/**********************************************************************************************************************/
/* FUNCTION OBJECTIVE ->Project Functions                                                                 */
/**********************************************************************************************************************/
void Start_Motors(void)
{
	H_DCMotor_Void_DCMotorSetSpeed(76);
	H_DCMotor_Void_DCMotorSetDirection(CW);
	H_DCMotor_Void_DCMotorStart();
	H_LCD_Void_LCDGoTo(0,0);
	H_LCD_Void_LCDWriteString((u8*)"Speed:");
	H_LCD_Void_LCDWriteNumber(76);
	H_LCD_Void_LCDWriteCharacter('%');
	H_LCD_Void_LCDWriteString((u8*)"DIR:");
	H_LCD_Void_LCDWriteCharacter('-');
	H_LCD_Void_LCDWriteNumber(18);
	H_Stepper_Void_StepperStartNEG(18);
}
void printTimer(void)
{
	H_LCD_Void_LCDGoTo(1,0);
	H_LCD_Void_LCDWriteString((u8*)"TIME:");
	H_LCD_Void_LCDGoTo(1,14);
	H_LCD_Void_LCDWriteString((u8*)"AM");
	H_LCD_Void_LCDGoTo(1,5);
	if(hour<10)
	{
	H_LCD_Void_LCDWriteCharacter('0');
	}
	H_LCD_Void_LCDWriteNumber(hour);
	H_LCD_Void_LCDWriteCharacter(':');
	if(min<10)
	{
	H_LCD_Void_LCDWriteCharacter('0');
	}
	H_LCD_Void_LCDWriteNumber(min);
	H_LCD_Void_LCDWriteCharacter(':');
	if(sec<10)
	{
	H_LCD_Void_LCDWriteCharacter('0');
	}
	H_LCD_Void_LCDWriteNumber(sec);
}
