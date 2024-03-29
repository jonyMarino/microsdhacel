/*MODULE: MethodTimer.c*/

#include "MethodTimer.hpp"
#include <stdlib.h>

#include "stddef.h"
#include "stdtypes.h"


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
MethodTimer::MethodTimer(ulong tiempo,const struct Method& _metodo):Timer(tiempo),metodo(_metodo){}

MethodTimer::MethodTimer(ulong tiempo,Method::pMethod _metodo,void*obj):Timer(tiempo){
  metodo.pmethod = _metodo;
  metodo.obj=obj;  
}
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

struct Method&  MethodTimer::getMetodo(){
  return metodo;
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

