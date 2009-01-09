#ifndef _LAZOALARMACONTROL_H
#define _LAZOALARMACONTROL_H


#include "LazoControlAlarma.h"
#include "CntrProporcionalInv.h"
#include "SalidaRetenida.h"
#include "SalidaRetenidaBajo.h"
#include "SalidaBanda.h"
#include "CntrRelativo.h"
#include "CntrBanda.h"
#include "SalidaInvertida.h"
#include "SalidaBloqueada.h"

struct LazoAlarmaControl {
  struct LazoControl super;
//%-
  struct ConfLazoCntrAlCntr * configuracion;
  struct Control * lazoControl;
  
  union{
    struct ValorControl valorControl;    
    struct CntrRelativo cntrRelativo;  
    struct CntrProporcionalInv cntrProporcionalInv; 
    struct CntrBanda cntrBanda;
  }control;
  
  union{
    struct SalidaBloqueada salidaBloqueada;
    struct SalidaBanda salidaBanda;
    struct SalidaRetenida salidaRetenida;
    struct SalidaRetenidaBajo salidaRetenidaBajo;
  }adaptadorSalida;
  
  struct SalidaInvertida salidaInvertida;
  struct Method onPeridoControlCambio;
};

extern const struct LazoClass LazoAlarmaControl;

typedef enum{
  CONTROL_PROPORCIONAL,
  CONTROL_RELATIVO,
  CONTROL_BANDA  
}TControlAlarma;

TControlAlarma  LazoAlarmaControl_getControl(void*_self);
byte LazoAlarmaControl_setControl(void*_self,TControlAlarma control);

TAdaptador  LazoAlarmaControl_getAdaptadorSalida(void*_self);
byte LazoAlarmaControl_setAdaptadorSalida(void*_self,TAdaptador adaptSalida);

int   LazoAlarmaControl_getValor(void*_self);
byte  LazoAlarmaControl_setValor(void*_self,int valor);

int   LazoAlarmaControl_getHisteresis(void*_self);
byte  LazoAlarmaControl_setHisteresis(void*_self,int histeresis);

#endif
