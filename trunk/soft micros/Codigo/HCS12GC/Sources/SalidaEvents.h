#ifndef _SALIDA_EVENTS_H
#define _SALIDA_EVENTS_H

#include <stdtypes.h>

/*
** ===================================================================
**    Function    :  Salida_OnToggle 
**    Description :  Funcion de utilidad a llama cuando la salida es un 
**                   pin on-off y cambia de valor
** ===================================================================
*/
void Salida_OnToggle(uchar Value,uchar numSalida);

#endif