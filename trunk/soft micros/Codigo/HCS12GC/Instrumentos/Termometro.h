#ifndef _TERMOMETRO_H
#define _TERMOMETRO_H

#include "Object.h"
#include "Mydefines.h"
#include "ClassADC.h"
#include "SensorTPT_Class.h"
#include "ManejadorMemoria.h"
#include "PlataformaEmbedded.h"

struct Termometro{
  struct PlataformaEmbedded super;
  struct TSensor_TermoPT sensor[CANTIDAD_CANALES];
  struct TAdc  AD1[CANTIDAD_CANALES];
  struct ManejadorDePROM * flash;  
};

extern const struct PlataformaEmbeddedClass Termometro;
  
void Termometro_constructor(void * self,void * conf,struct ManejadorDePROM * flash); 

void Termometro_mainLoop(void * self);


#define _getSensor(self,num)  (&((struct Termometro *)self)->sensor[num])

#endif 