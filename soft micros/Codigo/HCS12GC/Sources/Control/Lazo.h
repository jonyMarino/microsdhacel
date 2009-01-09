#ifndef _LAZO_H
#define _LAZO_H


#include "Sensor.h"
#include "Salida.h"
#include "Method.h"

struct Lazo{
  void * vTable;
  struct Method nuevaMedicion;
};

//%#
void Lazo_constructor(void * _self,struct Sensor * sensor);

void * Lazo_destructor(void * _self);

//%+
void onNuevaMedicion(void * _self);

/**Debe retornar el mismo sensor que se paso al contructor
** no se lo guarda directamente para optimizar el uso de ram. 
*/
struct Sensor * getSensor(void * _self );

struct ISalida * getSalida(void * _self );

//%#
//Structura de la metaclase
struct LazoClass{
  struct Class super;
  void(*onNuevaMedicion)(void * _self);
  struct Sensor * (*getSensor)(void * _self );
  struct ISalida * (*getSalida)(void * _self );
};

extern const struct Class LazoClass;
extern const struct LazoClass Lazo;

#define LAZO_CLASS_INITIALIZATION(description,name,super,contructor,destructor,differ,puto,onNuevaMedicion,getSensor,getSalida) \
  CLASS_INITIALIZATION(description,name,super,contructor,destructor,differ,puto),  \
  onNuevaMedicion,  \
  getSensor,  \
  getSalida

#endif
