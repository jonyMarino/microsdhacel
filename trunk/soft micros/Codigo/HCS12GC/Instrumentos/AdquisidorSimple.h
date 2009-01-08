#ifndef _ADQUISIDOR_SIMPLE_H
#define _ADQUISIDOR_SIMPLE_H 

#include "Termometro.h"
#include "Adquisidor.h"
#include "MessagesOut.h"
#include "RlxMTimer.h"

struct AdquisidorSimple{ 
  struct Termometro termometro;
  struct Adquisidor adquisidor;
  struct MessageOut mensajes;
  struct RlxMTimer timer;
  Message textosMensajes;
  char mensaje[40]; 
};

extern const struct PlataformaEmbeddedClass AdquisidorSimple;

void AdquisidorSimple_mainLoop(void * self);

#define _getAdquisidor(self) (&((struct AdquisidorSimple *)self)->adquisidor)
#endif