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

#pragma DATA_SEG Retransmision_DATA                                            
#pragma CODE_SEG Retransmision_CODE 
#pragma CONST_SEG DEFAULT

extern const struct LazoClass Retransmision;

void Retransmision_constructor(void * _self,struct RetransmisionConf * configuracion,struct ISalida* salida,struct Sensor* sensor);
struct ISalida* Retransmision_getSalida(void * _self);
struct Sensor* Retransmision_getSensor(void * _self);


#pragma DATA_SEG DEFAULT                                            
#pragma CODE_SEG DEFAULT 
#pragma CONST_SEG DEFAULT

#endif
