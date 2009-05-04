
/* MODULE TmDt1. */

#include "PE_Error.h"
#include "TmDt1_protected.h"
#include "stddef.h"

#pragma CODE_SEG TmDt1_CODE                     
#pragma CONST_SEG DEFAULT

void TmDt1_DefConstructor(void * self,va_list * args);


const struct FechaTiempoClass TmDt1={
  TMDT1_CLASS_INITIALIZATION(FechaTiempoClass,
                             TmDt1,
                             FechaTiempo,
                             TmDt1_DefConstructor,
                             Object_dtor,
                             Object_differ,
                             Object_puto,
                             TmDt1_GetTime,
                             TmDt1_setTiempoValidado,
                             TmDt1_GetDate,
                             TmDt1_setFechaValidada)
};


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
  err=setFecha(self,Year,Month,Day);  /* Initial date */
  if(err)    //cambiar : error
    (void)setFecha(self,2008,1,1);  /* Initial date */  
  err=setTiempo(self,Hour,Min,secs);        /* Initialize time */
  if(err)    //cambiar : error
    (void)setTiempo(self,0,0,0);        /* Initialize time */  
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
  super_ctor(&TmDt1,self,args);
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
byte TmDt1_setTiempoValidado(void * _self,byte Hour,byte Min,byte secs)
{
  struct TmDt1 * self = _self;
  
  self->TotalHthL = 3600 * (dword)Hour + 60 * (dword)Min + secs; /* Load given time re-calculated to 10ms ticks into software tick counter */

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
byte TmDt1_setFechaValidada(void * self,word Year,byte Month,byte Day)
{
  struct TmDt1 * _t = self;

  _t->CntDay = Day;                     /* Set day counter to the given value */
  _t->CntMonth = Month;                 /* Set month counter to the given value */
  _t->CntYear = Year;                   /* Set year counter to the given value */
  return ERR_OK;                        /* OK */
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

    if (_t->CntDay > FechaTiempo_getMaximoDiaDelMes(_t->CntYear,_t->CntMonth)) {      /* Day counter overflow? */
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

