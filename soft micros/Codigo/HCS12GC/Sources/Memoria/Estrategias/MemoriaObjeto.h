#ifndef _MEMORIA_OBJETO_H
#define _MEMORIA_OBJETO_H

#include "Class.h"
#include "PE_types.h"

struct MemoriaObjeto{
  void * obj; //puntero al objeto alocado con la maxima cantidad de memoria que puede tener
  bool usado;
};

void MemoriaObjeto_constructor(void * _self,struct Tclass * clases[]);

void * MemoriaObjeto_new(void * _self,struct Tclass * clase, ...);

void MemoriaObjeto_delete(void * _self);


#endif