#ifndef _RETRANSMISION_H
#define _RETRANSMISION_H

#include "Lazo.h"
#include "RetransmisionConf.h"

struct Retransmision{
  struct Lazo super;
//%-  
  struct RetransmisionConf * configuracion;
  struct ISalida* salida;
  struct Sensor* sensor;
};


extern const struct TLazoClass RetransmisionClass;

void Retransmision_constructor(void * _self,struct RetransmisionConf * configuracion,struct ISalida* salida,struct Sensor* sensor);
struct ISalida* Retransmision_getSalida(void * _self);
struct Sensor* Retransmision_getSensor(void * _self);

#endif
