/*MODULE: MethodTimer.c*/

#include "MethodTimer.hpp"
#include <stdlib.h>

#include "stddef.h"
#include "stdtypes.h"
#include "Cpu.h"


#pragma DATA_SEG MethodTimer_DATA                                            
#pragma CODE_SEG MethodTimer_CODE 
#pragma CONST_SEG DEFAULT


/*
** ===================================================================
**     Method      :  MTimer_Construct 
**    Description : Metodo para setear los 
**                  valores de configuración del Timer
** ===================================================================
*/
MethodTimer::MethodTimer(ulong tiempo,struct Method& _metodo):Timer(tiempo),metodo(_metodo){}


/*
** ===================================================================
**     Method      :  MethodTimer_setMetodo 
**    Description : Metodo por defecto para setear los 
**                  valores de configuración del Timer
** ===================================================================
*/
void MethodTimer::setMetodo(struct Method& _metodo){
  metodo = _metodo; 
}
/*
** ===================================================================
**     Method      :  MTimer_OnTime 
**    Description : funcion a llamar cuando se llega al tiempo
** ===================================================================
*/
void MethodTimer::onTime(){
  metodo.execute();
}

#pragma CODE_SEG MethodTimer_CODE

