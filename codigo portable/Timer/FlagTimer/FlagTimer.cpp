/*MODULE FlagTimer*/


#include <stdarg.h>
#include <stdlib.h>

#include "stddef.h"
#include "stdtypes.h"
#include "FlagTimer.hpp"

 
#pragma CONST_SEG DEFAULT


FlagTimer::FlagTimer(ulong tiempo):Timer(tiempo),flag(FALSE){ 
}
/*
** ===================================================================
**     Method      :  FTimer_OnTime 
**    Description : funcion a llamar cuando se llega al tiempo
** ===================================================================
*/
void FlagTimer::onTime(){
  flag = TRUE;  
}
/*
** ===================================================================
**     Method      :  TimerFlag_reset 
**    Description : 
** ===================================================================
*/
void FlagTimer::reset(){
  flag = FALSE;  
}

