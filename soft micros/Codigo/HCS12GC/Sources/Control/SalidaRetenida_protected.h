#ifndef _SALIDA_RETENIDA_PROTECTED_H
#define _SALIDA_RETENIDA_PROTECTED_H

#include "SalidaRetenida.h"

void SalidaRetenida_defConstructor(void * _self,va_list * args);
TipoSalida SalidaRetenida_getTipoSalidaAdaptador(void * _self);
int SalidaRetenida_calcularDuty(struct SalidaBanda * self,int valorDeControl);
byte SalidaRetenida_setTipoSalidaAdaptador(void * _self, TipoSalida tipoSalida);
void SalidaRetenida_setRetenida(void * _self,bool retener);


#endif