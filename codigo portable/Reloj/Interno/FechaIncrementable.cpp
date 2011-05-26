#include <stddef.h>
#include "PE_Error.h"
#include "FechaIncrementable.hpp"


FechaIncrementable::FechaIncrementable(word anio,byte mes,byte dia,byte hora,byte min,byte segs)
{
  if(isTiempoValido(hora,min,segs))    
    setTiempoValidado(hora,min,segs);  
  else 
    setTiempoValidado(0,0,0);              
  
  if(isFechaValida(anio,mes,dia))    
    setFechaValidada(anio,mes,dia);  
  else  
    setFechaValidada(2010,1,1);  
        
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
void FechaIncrementable::setTiempoValidado(byte Hour,byte Min,byte secs)
{
  totalHthL = 3600 * (dword)Hour + 60 * (dword)Min + secs; /* Load given time re-calculated to 10ms ticks into software tick counter */
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
void FechaIncrementable::getTiempo(TIMEREC *Time)
{
  dword Var1;                          /* Working temporary copy of software tick counter */
  word Var2;                           /* Working temporary variable */

  Var1 = totalHthL;                    /* Loading actual number of seconds */
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
void FechaIncrementable::setFechaValidada(word Year,byte Month,byte Day)
{


  cntDia = Day;                     /* Set day counter to the given value */
  cntMes = Month;                 /* Set month counter to the given value */
  cntAnio = Year;                   /* Set year counter to the given value */
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
void FechaIncrementable::getFecha(DATEREC *Date)
{
  
  Date->Year = cntAnio;                /* Year */
  Date->Month = cntMes;              /* Month */
  Date->Day = cntDia;                  /* Day */                       /* OK */
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
     
void FechaIncrementable::incrementar(dword secs)
{
  const byte *ptr;                     /* Pointer ULY/LY table */
  dword TotalHthH=0;
  
  totalHthL += secs%86400;              /* Write new value of the software timer counter */
  if(totalHthL>=86400){
    totalHthL-=86400;
    TotalHthH++;  
  }
  TotalHthH += secs/86400;							 //dias
  while(TotalHthH){
    TotalHthH--;                       /* If yes then reset it by subtracting exactly 24 hours */
    cntDia++;                          /* Increment day counter */

    if (cntDia > getMaximoDiaDelMes(cntAnio,cntMes)) {      /* Day counter overflow? */
      cntDia = 1;                      /* Set day counter on 1 */
      cntMes++;                      /* Increment month counter */
      if (cntMes > 12) {             /* Month counter overflow? */
        cntMes = 1;                  /* Set month counter on 1 */
        cntAnio++;                     /* Increment year counter */
      }
    }
  }
}
                    
/* END TmDt1. */

