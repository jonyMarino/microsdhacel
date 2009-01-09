/* MODULE: SalidaEvents.c*/

#include "SalidaEvents.h"
#include "display.h"

/*
** ===================================================================
**    Function    :  Salida_OnToggle 
**    Description :  Funcion de utilidad a llama cuando la salida es un 
**                   pin on-off y cambia de valor
** ===================================================================
*/
void Salida_OnToggle(uchar Value,uchar numSalida){
  /* Write your code here ... */
  PutValLed(Value,numSalida);  
}