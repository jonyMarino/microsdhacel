#ifndef _LAZO_CONTROL_H
#define _LAZO_CONTROL_H

#include "Lazo.h"
#include "ValorControl.h"
#include "AdaptacionSalida.h"

struct LazoControl{
  struct Lazo super;
//%- 
  struct ValorControl * valorControl; 
  struct AdaptacionSalida * adaptadorSalida;
};

extern const struct LazoClass LazoControlClass;

void LazoControl_constructor(void * _self, 
                             struct ValorControl * valorControl, 
                             struct AdaptacionSalida * adaptadorSalida);

struct Sensor * LazoControl_getSensor(void * _self );

struct ISalida * LazoControl_getSalida(void * _self );

TipoSalida LazoControl_getTipoSalida(void * _self);
byte LazoControl_setTipoSalida(void * _self,TipoSalida tipoSalida);

#define  _LazoControl_getAdaptadorSaldia(self)  ((struct LazoControl*)self)->adaptadorSalida
#endif
