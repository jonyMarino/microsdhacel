/** ###################################################################
**     THIS BEAN MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename  : TmDt1.H
**     Project   : _7_11
**     Processor : MC9S12GC32CFU16
**     Beantype  : TimeDate
**     Version   : Bean 02.043, Driver 01.09, CPU db: 2.87.320
**     Compiler  : Metrowerks HC12 C Compiler
**     Date/Time : 07/12/2005, 08:34 a.m.
**     Abstract  :
**         This bean "TimeDate" implements real time and date.
**         The bean requires a periodic interrupt generator: timer
**         compare or reload register or timer-overflow interrupt
**         (of free running counter). User can select precision of
**         selected timer.
**         The bean supports also alarm with event OnAlarm.
**     Settings  :
**         Timer name                  : TIM (16-bit)
**
**         Counter                     : TCNT      [68]
**         Mode register               : TIOS      [64]
**         Run register                : TSCR1     [70]
**         Prescaler                   : TSCR2     [77]
**         Compare register            : TC2       [84]
**         Flip-flop register          : TCTL2     [73]
**
**         Interrupt name              : Vtimch2 
**         Interrupt enable reg.       : TIE       [76]
**         Priority                    : 1
**         User handling procedure     : TmDt1_OnAlarm
**         This event is called whenever the current time is equal
**         to alarm time
**
**         High speed mode
**             Prescaler               : divide-by-128
**             Clock                   : 195312 Hz
**           Resolution of timer
**             Xtal ticks              : 2684314
**             microseconds            : 335539
**             milliseconds            : 336
**             seconds (real)          : 0.3355392
**             Hz                      : 3
**
**         Initialization:
**              Timer                  : Disabled
**
**              Time                   : 0:0:0
**              Date                   : 1/1/2001
**     Contents  :
**         Enable   - byte TmDt1_Enable(void);
**         SetTime  - byte TmDt1_SetTime(byte Hour,byte Min,byte Sec,byte Sec100);
**         GetTime  - byte TmDt1_GetTime(TIMEREC *Time);
**         SetDate  - byte TmDt1_SetDate(word Year,byte Month,byte Day);
**         GetDate  - byte TmDt1_GetDate(DATEREC *Date);
**         GetDay   - byte TmDt1_GetDay(byte *Day);
**         SetAlarm - byte TmDt1_SetAlarm(byte Hour,byte Min,byte Sec,byte Sec100);
**
**     (c) Copyright UNIS, spol. s r.o. 1997-2004
**     UNIS, spol. s r.o.
**     Jundrovska 33
**     624 00 Brno
**     Czech Republic
**     http      : www.processorexpert.com
**     mail      : info@processorexpert.com
** ###################################################################*/

#ifndef __TmDt1
#define __TmDt1

/* MODULE TmDt1. */

#include "Cpu.h"
#include <limits.h>

#pragma CODE_SEG TmDt1_CODE                     

#ifndef __BWUserType_TIMEREC
#define __BWUserType_TIMEREC
  typedef struct { /* It contains actual number of hours, minutes, seconds and hundreths of seconds. */
    byte Hour; /* hours (0 - 23) */
    byte Min; /* minutes (0 - 59) */
    byte Sec; /* seconds (0 - 59) */
    byte Sec100; /* hundredths of seconds (0 - 99) */
  } TIMEREC;
#endif
#ifndef __BWUserType_DATEREC
#define __BWUserType_DATEREC
  typedef struct { /* It contains actual year, month, and day description. */
    word Year; /* years (1998 - 2099) */
    byte Month; /* months (1 - 12) */
    byte Day; /* days (0 - 6) */
  } DATEREC;
#endif

void TmDt1_Enable(bool Endi);
void TmDt1_EnDiAlarm(bool Endi);
/*
** ===================================================================
**     Method      :  TmDt1_Enable (bean TimeDate)
**
**     Description :
**         Enables the bean - it starts the time/date timer. Events
**         may be generated ("DisableEvent"/"EnableEvent").
**     Parameters  : None
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
** ===================================================================
*/

byte TmDt1_SetTime(byte Hour,byte Min);
/*
** ===================================================================
**     Method      :  TmDt1_SetTime (bean TimeDate)
**
**     Description :
**         Sets a new actual time.
**     Parameters  :
**         NAME            - DESCRIPTION
**         Hour            - Hours (0 - 23)
**         Min             - Minutes (0 - 59)
**         Sec             - Seconds (0 - 59)
**         Sec100          - Hundredths of seconds (0 - 99)
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_RANGE - Parameter out of range
** ===================================================================
*/

void TmDt1_GetTime(TIMEREC *Time);
/*
** ===================================================================
**     Method      :  TmDt1_GetTime (bean TimeDate)
**
**     Description :
**         Return current time.
**     Parameters  :
**         NAME            - DESCRIPTION
**       * Time            - Pointer to the structure TIMEREC. It
**                           contains actual number of hours, minutes,
**                           seconds and hundreths of seconds.
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
** ===================================================================
*/

byte TmDt1_SetDate(word Year,byte Month,byte Day);
byte  TmDt1_GetMaxday(word Year,byte Month);
/*
** ===================================================================
**     Method      :  TmDt1_SetDate (bean TimeDate)
**
**     Description :
**         Set a new actual date.
**     Parameters  :
**         NAME            - DESCRIPTION
**         Year            - Years (16-bit unsigned integer)
**         Month           - Months (8-bit unsigned integer)
**         Day             - Days (8-bit unsigned integer)
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_RANGE - Parameter out of range
** ===================================================================
*/

void TmDt1_GetDate(DATEREC *Date);

/*
** ===================================================================
**     Method      :  TmDt1_GetDay (bean TimeDate)
**
**     Description :
**         Return current day of the week.
**     Parameters  :
**         NAME            - DESCRIPTION
**       * Day             - Pointer to returned day - 8-bit
**                           unsigned number
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
** ===================================================================
*/

void TmDt1_SetAlarm(word Sec);
/*
** ===================================================================
**     Method      :  TmDt1_SetAlarm (bean TimeDate)
**
**     Description :
**         Sets a new time of alarm. (only time, not date - alarm
**         event OnAlarm is called every 24 hours). Setting time of
**         alarm out of 24 hour interval disables its function.
**     Parameters  :
**         NAME            - DESCRIPTION
**         Hour            - Hours (0 - 23)
**         Min             - Minutes (0 - 59)
**         Sec             - Seconds (0 - 59)
**         Sec100          - Hundreths of seconds (0 - 99)
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_RANGE - Parameter out of range
** ===================================================================
*/

    
void TmDt1_Inc(void);                     
/*
** ===================================================================
**     Method      :  TmDt1_Interrupt (bean TimeDate)
**
**     Description :
**         This method is internal. It is used by Processor Expert
**         only.
** ===================================================================
*/

void TmDt1_Init(void);
/*
** ===================================================================
**     Method      :  TmDt1_Init (bean TimeDate)
**
**     Description :
**         This method is internal. It is used by Processor Expert
**         only.
** ===================================================================
*/

#pragma CODE_SEG DEFAULT                                   

/* END TmDt1. */

#endif /* ifndef __TmDt1 */
/*
** ###################################################################
**
**     This file was created by UNIS Processor Expert 2.95 [03.62]
**     for the Freescale HCS12 series of microcontrollers.
**
** ###################################################################
*/