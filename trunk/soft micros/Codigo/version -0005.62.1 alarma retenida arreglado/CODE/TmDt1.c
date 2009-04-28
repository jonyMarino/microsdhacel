
/* MODULE TmDt1. */

#include "Events.h"
#include "PE_Error.h"
#include "TmDt1.h"
#include "Mydefines.h"

#ifdef adquisidor

#pragma CODE_SEG TmDt1_CODE                     
#pragma CONST_SEG DEFAULT

bool Date_EnUser;                    /* Enable/Disable device by user */
static byte CntDay;                    /* Day counter */
static byte CntMonth;                  /* Month counter */
static word CntYear;                   /* Year Counter */
static dword TotalHthL;
static dword TotalHthH;                /* Software tick counter (1 tick = 10ms) */
static dword AlarmHth;                 /* Alarm time (compared with software tick counter) */
static bool AlarmFlg;                  /* Alarm flag */
static word intervalo;                     /* Temporary variable */
/* Table of month length (in days) */
static const byte ULY[12] = {31,28,31,30,31,30,31,31,30,31,30,31}; /* Un-leap-year */
static const byte  LY[12] = {31,29,31,30,31,30,31,31,30,31,30,31}; /* Leap-year */

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
void TmDt1_Enable(bool Endi)
{
    Date_EnUser = Endi;                     /* If yes then set the flag "device enabled" */
		
}

void TmDt1_EnDiAlarm(bool Endi)
{
 AlarmFlg=Endi;
 AlarmHth = TotalHthH + intervalo;                /* Copy content of temporary variable into Alarm time variable */ 
 if (Endi) Escribir_Header();
}

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
byte TmDt1_SetTime(byte Hour,byte Min)
{
  bool TmrRun;                         /* Temporary flag enable/disable */

  if ((Min > 59) || (Hour > 23)) /* Test correctnes of given time */
    return ERR_RANGE;                  /* If not correct then error */
  TmrRun = Date_EnUser;                     /* Store actual device state */
  if (Date_EnUser) {                        /* Is the device enabled by user? */
    Date_EnUser = FALSE;                    /* If yes then set the flag "device disabled" */
  }
  TotalHthH = 360000 * (dword)Hour + 6000 * (dword)Min; /* Load given time re-calculated to 10ms ticks into software tick counter */
  TotalHthL = 0;
  if (TmrRun) {                        /* Was the device disabled? */
    Date_EnUser = TRUE;                     /* If yes set flag "device enabled" */
  }
  return ERR_OK;                       /* OK */

}

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
void TmDt1_GetTime(TIMEREC *Time)
{
  dword Var1;                          /* Working temporary copy of software tick counter */
  word Var2;                           /* Working temporary variable */

  Var1 = TotalHthH;                    /* Loading actual number of tens of ms */
  Time->Sec100 = Var1 % 100;           /* Modulo 100 gives appropriate number of hundreds of seconds */
  Var1 = Var1 / 100;                   /* Quotient gives total number of seconds then */
  Time->Sec = Var1 % 60;               /* Modulo 60 gives appropriate number of seconds */
  Var2 = (word) (Var1 / 60);           /* Quotient gives total number of minutes then */
  Time->Min = Var2 % 60;               /* Modulo 60 gives appropriate number of minutes */
  Time->Hour = (byte) (Var2 / 60);     /* Quotient gives total number of hours then */
}

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
byte TmDt1_SetDate(word Year,byte Month,byte Day)
{
  word tY = 1998;                      /* Year counter, starting with 1998 */
  byte tM = 1;                         /* Month counter, starting with January */
  byte tD = 1;                         /* Day counter, starting with 1 */
  byte tW = 4;                         /* Sun - Sat counter, starting with Thu */
  const byte *ptr;                     /* Pointer to ULY/LY table */

  if ((Year < 1998) || (Year > 2099) || (Month > 12) || (Month == 0) || (Day > 31) || (Day == 0)) /* Test correctness of given parameters */
    return ERR_RANGE;                  /* If not correct then error */
  if (tY & 3)                          /* Is given year un-leap-one? */
    ptr = ULY;                         /* Set pointer to un-leap-year day table */
  else                                 /* Is given year leap-one? */
    ptr = LY;                          /* Set pointer to leap-year day table */
  ptr--;                               /* Decrement pointer */
  for (;;) {
    if ((Year == tY) && (Month == tM)) { /* Is year and month equal with given parameters? */
      if (ptr[tM] < Day)               /* Does the obtained number of days exceed number of days in the appropriate month & year? */
        return ERR_RANGE;              /* If yes (incorrect date inserted) then error */
      if (tD == Day)                   /* Does the day match the given one? */
        break;                         /* If yes then date inserted correctly */
    }
    tD++;                              /* Increment day counter */
    if (tD > ptr[tM]) {                /* Day counter overflow? */
      tD = 1;                          /* Set day counter on 1 */
      tM++;                            /* Increment month counter */
      if (tM > 12) {                   /* Month counter overflow? */
        tM = 1;                        /* Set month counter on 1 */
        tY++;                          /* Increment year counter */
        if (tY & 3)                    /* Is this year un-leap-one? */
          ptr = ULY;                   /* Set pointer to un-leap-year day table */
        else                           /* Is this year leap-one? */
          ptr = LY;                    /* Set pointer to leap-year day table */
        ptr--;                         /* Decrement pointer */
      }
    }
  }
  CntDay = tD;                         /* Set day counter to the given value */
  CntMonth = tM;                       /* Set month counter to the given value */
  CntYear = tY;                        /* Set year counter to the given value */
  return ERR_OK;                       /* OK */
}

byte  TmDt1_GetMaxday(word Year,byte Month){
  const byte *ptr;                     /* Pointer to ULY/LY table */

  if (Year & 3)                          /* Is given year un-leap-one? */
    ptr = ULY;                         /* Set pointer to un-leap-year day table */
  else                                 /* Is given year leap-one? */
    ptr = LY;                          /* Set pointer to leap-year day table */
 return ptr[Month-1];
}


/*
** ===================================================================
**     Method      :  TmDt1_GetDate (bean TimeDate)
**
**     Description :
**         Return current date.
**     Parameters  :
**         NAME            - DESCRIPTION
**       * Date            - Pointer to the structure DATEREC. It
**                           contains actual year, month, and day
**                           description.
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
** ===================================================================
*/
void TmDt1_GetDate(DATEREC *Date)
{

  Date->Year = CntYear;                /* Year */
  Date->Month = CntMonth;              /* Month */
  Date->Day = CntDay;                  /* Day */                       /* OK */
}



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
void TmDt1_SetAlarm(word Sec)
{
  intervalo =  100 * (word)Sec ;                   /* Load given time re-calculated to 10ms ticks into temporary variable */
  AlarmHth = TotalHthH + intervalo;                /* Copy content of temporary variable into Alarm time variable */
}

/*
** ===================================================================
**     Method      :  TmDt1_Init (bean TimeDate)
**
**     Description :
**         This method is internal. It is used by Processor Expert
**         only.
** ===================================================================
*/
void TmDt1_Init(void)
{
  Date_EnUser = FALSE;                      /* Disable device */
  AlarmHth = ULONG_MAX;                /* Disable alarm */
  AlarmFlg = FALSE;                    /* Reset alarm flag */
  intervalo = 100;
  (void)TmDt1_SetDate(2001,1,1);       /* Initial date */
  (void)TmDt1_SetTime(0,0);        /* Initialize time */
}

/*
** ===================================================================
**     Method      :  TmDt1_Interrupt (bean TimeDate)
**
**     Description :
**         This method is internal. It is used by Processor Expert
**         only.
** ===================================================================
*/
     
void TmDt1_Inc(void)
{
  dword Val32;                         /* Temporary variable */
  const byte *ptr;                     /* Pointer ULY/LY table */

  TotalHthH += 8;                     /* Software timer counter increment by timer period (10 ms) */
  Val32 = TotalHthL + 1668508895;      /* Add timer period to the lower part of software timer counter */
  if (Val32 < TotalHthL)               /* Was there a carry from lower part into upper part of software timer counter? */
    TotalHthH++;                       /* If yes then increment upper part of the software timer counter */
  TotalHthL = Val32;                   /* Write new value of the software timer counter */
  if (TotalHthH >= 8640000) {          /* Does the counter reach 24 hours? */
    TotalHthH -= 8640000;              /* If yes then reset it by subtracting exactly 24 hours */
    AlarmHth = TotalHthH + intervalo;	 /* If yes then reset alarm by subtracting exactly 24 hours */
    CntDay++;                          /* Increment day counter */
    if (CntYear & 3)                   /* Is this year un-leap-one? */
      ptr = ULY;                       /* Set pointer to un-leap-year day table */
    else                               /* Is this year leap-one? */
      ptr = LY;                        /* Set pointer to leap-year day table */
    ptr--;                             /* Decrement the pointer */
    if (CntDay > ptr[CntMonth]) {      /* Day counter overflow? */
      CntDay = 1;                      /* Set day counter on 1 */
      CntMonth++;                      /* Increment month counter */
      if (CntMonth > 12) {             /* Month counter overflow? */
        CntMonth = 1;                  /* Set month counter on 1 */
        CntYear++;                     /* Increment year counter */
      }
    }
  }
    if (AlarmFlg) {                   /* Has the alarm already been on? */
     extern bool al1;
      if (TotalHthH >= AlarmHth) {     /* Is the condition for alarm invocation satisfied? */
        AlarmHth += intervalo;
        Grabar_Parametros();               /* Invoke user event */
        al1= !al1;
      }
    }
}
                    
#endif
/* END TmDt1. */

