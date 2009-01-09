#ifndef _LAZO_CONTROL_ALARMA_H
#define _LAZO_CONTROL_ALARMA_H

#include "LazoControl.h"

typedef enum{
  SALIDA_EXCESO,      
  SALIDA_DEFECTO,
  SALIDA_RETENIDA,
  SALIDA_DEFECTO_RETENIDA,
  SALIDA_DEFECTO_BLOQUEADA   
}TAdaptador;

#define ADAPTADOR_MAX_VALOR 4

#endif