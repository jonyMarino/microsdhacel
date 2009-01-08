/* MODULE: SalidaEvents.c*/

#include "SalidaEvents.h"
#include "O2.h"
#include "O4.h"
#include "O6.h"
#include "O7.h"

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
  switch(numSalida){
  case 0:
    O2_PutVal(Value);
    break;
  case 1:
    O4_PutVal(Value);
    break;
  case 2:
    O6_PutVal(Value);
    break;
  case 3:
    O7_PutVal(Value);    
  }
  PutValLed(Value,numSalida);  
}