#ifndef _FECHA_TIEMPO_PROTECTED_H
#define _FECHA_TIEMPO_PROTECTED_H

#include "FechaTiempo.h"

#pragma CODE_SEG FechaTiempo_CODE

byte super_setTiempoValidado(const void*class,void * self,byte hour,byte min,byte secs);
byte super_setFechaValidada(const void*class,void * self,word year,byte month,byte day);
void super_getTime(const void*class,void * self,TIMEREC *time);
void super_getDate(const void*class,void * self,DATEREC *date);

#pragma CODE_SEG DEFAULT

#endif