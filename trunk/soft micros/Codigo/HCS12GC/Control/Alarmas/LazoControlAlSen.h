#ifndef _LAZO_CONTROL_AL_SEN_H
#define _LAZO_CONTROL_AL_SEN_H


#include "LazoControlAlarma.h" 
#include "CntrProporcionalInv.h"
#include "SalidaBloqueada.h"
#include "SalidaBanda.h"
#include "SalidaRetenidaBajo.h"
#include "ConfLazoCntrlAlSen.h"
#include "SalidaInvertida.h"

struct LazoControlAlSen{
  struct LazoControl super;
  struct ConfLazoCntrlAlSen * configuracion;
  struct CntrProporcionalInv control;   
  union{
    struct SalidaBloqueada salidaBloqueada;
    struct SalidaBanda salidaBanda;
    struct SalidaRetenida salidaRetenida;
    struct SalidaRetenidaBajo salidaRetenidaBajo;
  }adaptadorSalida;
  
  struct SalidaInvertida salidaInvertida;
};

extern const struct LazoClass LazoControlAlSen;


TAdaptador  LazoControlAlSen_getAdaptadorSalida(void*_self);
byte LazoControlAlSen_setAdaptadorSalida(void*_self,TAdaptador adaptSalida);

int   LazoControlAlSen_getValor(void*_self);
byte  LazoControlAlSen_setValor(void*_self,int valor);

int   LazoControlAlSen_getHisteresis(void*_self);
byte  LazoControlAlSen_setHisteresis(void*_self,int histeresis);

#endif