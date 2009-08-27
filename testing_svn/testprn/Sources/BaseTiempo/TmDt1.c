
/* MODULE TmDt1. */

#include "PE_Error.h"
#include "TmDt1.h"
#include "stddef.h"

#pragma CODE_SEG TmDt1_CODE                     
#pragma CONST_SEG DEFAULT

void TmDt1_DefConstructor(void * self,va_list * args);

const struct Class TmDt1Class;

const struct TmDt1Class TmDt1={
  TMDT1_CLASS_INITIALIZATION(TmDt1Class,
                             TmDt1,
                             Object,
                             TmDt1_DefConstructor,
                             Object_dtor,
                             Object_differ,
                             Object_puto,
                             TmDt1_GetTime,
                             TmDt1_SetTime,
                             TmDt1_GetDate,
                             TmDt1_SetDate)
};




/*

*/
void getTime(void * self,TIMEREC *time){
  struct TmDt1Class * class = classOf(self);
  class->getTime(self,time);
}

byte setTime(void * self,byte hour,byte min,byte secs){
  struct TmDt1Class * class = classOf(self);
  return class->setTime(self,hour,min,secs);
}

byte super_setTime(const struct TmDt1Class*class,void * self,byte hour,byte min,byte segs){
  const struct TmDt1Class* super_class=super(class);
  return super_class->setTime(self,hour,min,segs);
}

void getDate(void * self,DATEREC *date){
  struct TmDt1Class * class = classOf(self);
  class->getDate(self,date);
}

byte setDate(void * self,word year,byte month,byte day){
  struct TmDt1Class * class = classOf(self);
  class->setDate(self,year,month,day);
}

byte super_setDate(const struct TmDt1Class*class,void * self,word year,byte month,byte day){
  const struct TmDt1Class* super_class=super(class);
  return super_class->setDate(self,year,month,day);
}



/* Table of month length (in days) */
static const byte ULY[12] = {31,28,31,30,31,30,31,31,30,31,30,31}; /* Un-leap-year */
static const byte  LY[12] = {31,29,31,30,31,30,31,31,30,31,30,31}; /* Leap-year */

/*
** ===================================================================
**     Method      :  TmDt1_Constructor (bean TimeDate)
**
**     Description :
**         This method is internal. It is used by Processor Expert
**         only.
** ===================================================================
*/
void TmDt1_Constructor(void * self,word Year,byte Month,byte Day,byte Hour,byte Min,byte secs)
{
  byte err;
  err=TmDt1_SetDate(self,Year,Month,Day);  /* Initial date */
  if(err)    //cambiar : error
    (void)TmDt1_SetDate(self,2008,1,1);  /* Initial date */  
  err=TmDt1_SetTime(self,Hour,Min,secs);        /* Initialize time */
  if(err)    //cambiar : error
    (void)TmDt1_SetTime(self,0,0,0);        /* Initialize time */  
}
/*
** ===================================================================
**     Method      :  TmDt1_DefConstructor (bean TimeDate)
**
**     Description :
**         This method is internal. It is used by Processor Expert
**         only.
** ===================================================================
*/
void TmDt1_DefConstructor(void * self,va_list * args){
  TmDt1_Constructor(self,va_arg(*args,word),va_arg(*args,int),va_arg(*args,int),va_arg(*args,int),va_arg(*args,int),va_arg(*args,int));  
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
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_RANGE - Parameter out of range
** ===================================================================
*/
byte TmDt1_SetTime(void * self,byte Hour,byte Min,byte secs)
{
  struct TmDt1 * _t = self;
  if ((Min > 59) || (Hour > 23)) /* Test correctnes of given time */
    return ERR_RANGE;                  /* If not correct then error */
  _t->TotalHthL = 3600 * (dword)Hour + 60 * (dword)Min + secs; /* Load given time re-calculated to 10ms ticks into software tick counter */

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
void TmDt1_GetTime(void * self,TIMEREC *Time)
{
  struct TmDt1 * _t = self;
  dword Var1;                          /* Working temporary copy of software tick counter */
  word Var2;                           /* Working temporary variable */

  Var1 = _t->TotalHthL;                    /* Loading actual number of seconds */
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
byte TmDt1_SetDate(void * self,word Year,byte Month,byte Day)
{
  struct TmDt1 * _t = self;
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
  if (ptr[Month] < Day)                /* Does the obtained number of days exceed number of days in the appropriate month & year? */
    return ERR_RANGE;                  /* If yes (incorrect date inserted) then error */
  else
    _t->CntDay = Day;                         /* Set day counter to the given value */
    _t->CntMonth = Month;                       /* Set month counter to the given value */
    _t->CntYear = Year;                        /* Set year counter to the given value */
  return ERR_OK;                       /* OK */
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
void TmDt1_GetDate(void * self,DATEREC *Date)
{
  struct TmDt1 * _t = self;
  
  Date->Year = _t->CntYear;                /* Year */
  Date->Month = _t->CntMonth;              /* Month */
  Date->Day = _t->CntDay;                  /* Day */                       /* OK */
}

/*
** ===================================================================
**     Function      :  TmDt1_GetMaxday 
**
**     Description :
**         Retorna la maxima cantidad de dias para el mes de ese anio
**     Parameters  :
**         Year            - anio
**         Month           - Mes
**     Returns     :
**         maxima cantidad de dias ara el mes de ese anio
**         0							 - Error
** ===================================================================
*/

byte  TmDt1_GetMaxday(word Year,byte Month){
  const byte *ptr;                     /* Pointer to ULY/LY table */

  if (Month>12 || Month<0)
    return 0;
  if (Year & 3)                          /* Is given year un-leap-one? */
    ptr = ULY;                         /* Set pointer to un-leap-year day table */
  else                                 /* Is given year leap-one? */
    ptr = LY;                          /* Set pointer to leap-year day table */
 return ptr[Month-1];
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
     
void TmDt1_Inc(void * self,dword secs)
{
  struct TmDt1 * _t = self;
  const byte *ptr;                     /* Pointer ULY/LY table */
  dword TotalHthH=0;
  
  _t->TotalHthL += secs%86400;              /* Write new value of the software timer counter */
  if(_t->TotalHthL>=86400){
    _t->TotalHthL-=86400;
    TotalHthH++;  
  }
  TotalHthH += secs/86400;							 //dias
  while(TotalHthH){
    TotalHthH--;                       /* If yes then reset it by subtracting exactly 24 hours */
    _t->CntDay++;                          /* Increment day counter */
    if (_t->CntYear & 3)                   /* Is this year un-leap-one? */
      ptr = ULY;                       /* Set pointer to un-leap-year day table */
    else                               /* Is this year leap-one? */
      ptr = LY;                        /* Set pointer to leap-year day table */
    ptr--;                             /* Decrement the pointer */
    if (_t->CntDay > ptr[_t->CntMonth]) {      /* Day counter overflow? */
      _t->CntDay = 1;                      /* Set day counter on 1 */
      _t->CntMonth++;                      /* Increment month counter */
      if (_t->CntMonth > 12) {             /* Month counter overflow? */
        _t->CntMonth = 1;                  /* Set month counter on 1 */
        _t->CntYear++;                     /* Increment year counter */
      }
    }
  }
}
                    
/* END TmDt1. */

