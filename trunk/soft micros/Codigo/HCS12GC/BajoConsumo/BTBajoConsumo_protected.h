#ifndef BT_BAJO_CONSUMO_PROTECTED_H
#define BT_BAJO_CONSUMO_PROTECTED_H

#include "BTBajoConsumo.h"
#include "BaseTiempo_protected.h"

void BTBajoConsumo_defConstructor(void * self,va_list * args);

void BTBajoConsumo_GetDate(void * _self,DATEREC *date);

void BTBajoConsumo_GetTime(void * _self,TIMEREC *time);

void BTBajoConsumo_onRTI(void * _self);

ulong BTBajoConsumo_interrupcionesRTI(void * _self);

#endif