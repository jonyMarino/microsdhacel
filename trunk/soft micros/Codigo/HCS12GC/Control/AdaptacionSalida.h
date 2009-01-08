#ifndef _ADAPTACION_SALIDA_H
#define _ADAPTACION_SALIDA_H


#include "Object.h"
#include "Salida.h"
#include "AdaptSalidaConf.h"

//Transforma de un valor de control a un valor para la salida
struct AdaptacionSalida{ 
  struct Object super;
//%-
  struct ISalida * salida;   
  struct AdaptSalidaConf * configuracion; 
};

void AdaptacionSalida_constructor(void* _self,struct AdaptSalidaConf * configuracion,struct ISalida * salida);
void AdaptacionSalida_defConstructor(void * _self,va_list * args);

void AdaptacionSalida_setPotenciaSalida(void* _self,int valorDeControl);

#define AdaptacionSalida_getSalida(self) ((struct AdaptacionSalida*)self)->salida

#define AdaptacionSalida_getHisteresis(self)  \
  AdaptSalidaConf_getHisteresis(((struct AdaptacionSalida*)self)->configuracion)

#define AdaptacionSalida_setHisteresis(self,valor)  \
  AdaptSalidaConf_setHisteresis(((struct AdaptacionSalida*)self)->configuracion,valor)

/**/ 
int getHisteresis(void * _self);
byte setHisteresis(void * _self, int histeresis);

/**/
TipoSalida getTipoSalidaAdaptador(void * _self);
byte setTipoSalidaAdaptador(void * _self, TipoSalida tipoSalida);

/**/
TipoSalida AdaptacionSalida_getTipoSalidaAdaptador(void * _self);
/**/
byte AdaptacionSalida_setTipoSalidaAdaptador(void * _self, TipoSalida tipoSalida);

/*  PROTEGIDO (SOLO PARA LAS CLASES DESCENDIENTES) */
struct AdaptacionSalidaClass{
  struct Class super;
  int(*calcularPotencia)(void*,int);
  TipoSalida (*getTipoSalidaAdaptador)(void * _self);
  byte (*setTipoSalidaAdaptador)(void * _self, TipoSalida tipoSalida);
};

extern const struct Class AdaptacionSalidaClass;

#define ADAPTACION_SALIDA_CLASS_INITIALIZATION(description,name,super,contructor,destructor,differ,puto,calcularPotencia,getTipoSalidaAdaptador,setTipoSalidaAdaptador)\
  CLASS_INITIALIZATION(description,name,super,contructor,destructor,differ,puto),\
  calcularPotencia, \
  getTipoSalidaAdaptador, \
  setTipoSalidaAdaptador
  
#endif
