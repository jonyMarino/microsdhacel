#ifndef _SALIDA_H
#define _SALIDA_H

#include "Object.h"
#include "stdtypes.h"
#include "PE_Types.h"

typedef enum{
  SALIDA_ONOFF,
  SALIDA_PROPORCIONAL
}TipoSalida;

struct ISalidaClass{
  const struct Class super;
  uint(*getPotencia)(void*);
  void(*setPotencia)(void*,uint);
  TipoSalida(*getTipoSalida)(void*);				//OnOff TRUE/FALSE
  void(*setTipoSalida)(void*,TipoSalida);				//OnOff TRUE/FALSE
  bool (*getConectada)(void *);
  void (*setConectada)(void *,bool);
};

extern const struct Class ISalidaClass;

#define ISALIDA_CLASS_INITIALIZATION(description,name,super,contructor,destructor,differ,puto,getPotencia,setPotencia,getTipoSalida,setTipoSalida,getConectada,setConectada)\
  CLASS_INITIALIZATION(description,name,super,contructor,destructor,differ,puto),\
  getPotencia,    \
  setPotencia,    \
  getTipoSalida,  \
  setTipoSalida,  \
  getConectada,   \
  setConectada


struct ISalida{        //interfaz salida
  struct Object super;  
};

struct Salida{
  struct ISalida super;
  uint duty;
  bool conectado;
};

extern const struct ISalidaClass Salida; 

#define _getPotencia(salida) \
            ((*(struct ISalidaClass **)salida)->getPotencia)(salida)

#define _setTipoSalida(salida,onoff) \
            ((*(struct ISalidaClass **)salida)->setTipoSalida)(salida,onoff)

#define _getTipoSalida(salida) \
            ((*(struct ISalidaClass **)salida)->getTipoSalida)(salida)

/*Constructor*/
void Salida_constructor(void * self);

/* Potencia*/
void Salida_setPotencia(void* self,uint duty);
uint Salida_getPotencia(void* self);
void setPotenciaSalida(void* self,int duty);
uint getPotencia(void* self);

/*Tipo Salida*/
TipoSalida getTipoSalida(void* _self);
void setTipoSalida(void* _self,TipoSalida tipoSalida);

/* Conexion */
bool getConectada(void*);
void setConectada(void*,bool);




#endif