#ifndef _SALIDA_PROTECTED_H
#define _SALIDA_PROTECTED_H

#include "Salida.h"
#include "PE_Types.h"
#include "stdtypes.h" 

bool Salida_getConectada(void * self);

void Salida_setConectada(void* self,bool conectar);

void setPotencia(void* self,uint duty);


#endif