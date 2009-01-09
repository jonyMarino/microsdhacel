#ifndef _PLATAFORMA_EMBEDDED_H
#define _PLATAFORMA_EMBEDDED_H

#include "Object.h"

struct PlataformaEmbeddedClass{
  struct Class super;
  void (*mainLoop)(void*);
};


struct PlataformaEmbedded{
  struct Object super;
};


extern const struct PlataformaEmbeddedClass PlataformaEmbedded;


void mainLoop(void * _self);
void super_mainLoop(void * _class,void * _self);


#endif