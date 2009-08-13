#ifndef _VALOR_CONTROL_H
#define _VALOR_CONTROL_H

#include "Sensor.h"
#include "ValorControlConf.h"

struct ValorControl{
  struct Object super;
//%-
  struct ValorControlConf * configuracion;
  struct Sensor * sensor;
};

void ValorControl_constructor(void * _self, 
                              struct ValorControlConf * configuracion,
                              struct Sensor * sensor
                              );
void ValorControl_defConstructor(void * _self,va_list * args);

int getValorControl(void * _self);



#define ValorControl_getSensor(self)  \
  ((struct ValorControl *)self)->sensor
  
#define ValorControl_getValorControlador(self)  \
  ValorControlConf_getValorControlador((((struct ValorControl *)self)->configuracion))
  
#define ValorControl_setValorControlador(self,val)  \
  ValorControlConf_setValorControlador((((struct ValorControl *)self)->configuracion),val)  

/*  PROTEGIDO (SOLO PARA LAS CLASES DESCENDIENTES) */
struct ValorControlClass{
  struct Class super;
  int(*getValorControl)(void*);
};

#define VALOR_CONTROL_CLASS_INITIALIZATION(description,name,super,contructor,destructor,differ,puto,getValorControl)\
  CLASS_INITIALIZATION(description,name,super,contructor,destructor,differ,puto),\
  getValorControl
  
#endif
