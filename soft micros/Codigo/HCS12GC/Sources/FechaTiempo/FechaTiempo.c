
/* MODULE FechaTiempo. */

#include "PE_Error.h"
#include "FechaTiempo_protected.h"
#include "stddef.h"

#pragma CODE_SEG FechaTiempo_CODE                     
#pragma CONST_SEG DEFAULT

void FechaTiempo_DefConstructor(void * self,va_list * args);

const struct Class FechaTiempoClass;

const struct FechaTiempoClass FechaTiempo={
  FECHA_TIEMPO_CLASS_INITIALIZATION(FechaTiempoClass,
                             FechaTiempo,
                             Object,
                             Object_ctor,
                             Object_dtor,
                             Object_differ,
                             Object_puto,
                             NULL,
                             NULL,
                             NULL,
                             NULL)
};




/*

*/
void super_getTime(const void*class,void * self,TIMEREC *time){
  const struct FechaTiempoClass* super_class=super(class);
  super_class->getTiempo(self,time);
}

void super_getDate(const void*class,void * self,DATEREC *date){
  const struct FechaTiempoClass* super_class=super(class);
  super_class->getFecha(self,date);
}

void getTiempo(void * self,TIMEREC *time){
  struct FechaTiempoClass * class = classOf(self);
  class->getTiempo(self,time);
}

byte setTiempoValidado(void * self,byte hour,byte min,byte secs){
  struct FechaTiempoClass * class = classOf(self);
  return class->setTiempoValidado(self,hour,min,secs);
}

byte super_setTiempoValidado(const void*class,void * self,byte hour,byte min,byte segs){
  const struct FechaTiempoClass* super_class=super(class);
  return super_class->setTiempoValidado(self,hour,min,segs);
}

void getFecha(void * self,DATEREC *date){
  struct FechaTiempoClass * class = classOf(self);
  class->getFecha(self,date);
}

byte setFechaValidada(void * self,word year,byte month,byte day){
  struct FechaTiempoClass * class = classOf(self);
  class->setFechaValidada(self,year,month,day);
}

byte super_setFechaValidada(const struct FechaTiempoClass*class,void * self,word year,byte month,byte day){
  const struct FechaTiempoClass* super_class=super(class);
  return super_class->setFechaValidada(self,year,month,day);
}



/* Table of month length (in days) */
static const byte ULY[12] = {31,28,31,30,31,30,31,31,30,31,30,31}; /* Un-leap-year */
static const byte  LY[12] = {31,29,31,30,31,30,31,31,30,31,30,31}; /* Leap-year */


/*
** ===================================================================
**     Method      :  setTime (bean TimeDate)
**
**     Description :
**         Sets a new actual time.
**     Parameters  :
**         self            - Object pointer
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
byte setTiempo(void * self,byte Hour,byte Min,byte secs)
{

  if ((Min > 59) || (Hour > 23)) /* Test correctnes of given time */
    return ERR_RANGE;                  /* If not correct then error */
  
  setTiempoValidado(self,Hour,Min,secs);
  
  return ERR_OK;                       /* OK */

}



/*
** ===================================================================
**     Method      :  setDate
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


byte setFecha(void * self,word Year,byte Month,byte Day)
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
  if (ptr[Month] < Day)                /* Does the obtained number of days exceed number of days in the appropriate month & year? */
    return ERR_RANGE;                  /* If yes (incorrect date inserted) then error */

  return setFechaValidada(self,Year,Month,Day);
}


/*
** ===================================================================
**     Function      :  FechaTiempo_getMaximoDiaDelMes 
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

byte  FechaTiempo_getMaximoDiaDelMes(word Year,byte Month){
  const byte *ptr;                     /* Pointer to ULY/LY table */

  if (Month>12 || Month<0)
    return 0;
  if (Year & 3)                          /* Is given year un-leap-one? */
    ptr = ULY;                         /* Set pointer to un-leap-year day table */
  else                                 /* Is given year leap-one? */
    ptr = LY;                          /* Set pointer to leap-year day table */
 return ptr[Month-1];
}

                    
/* END FechaTiempo. */

