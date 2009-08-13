#include "LedsSalida.h"

#include "stddef.h"
#include "display_teclas.h"
#include "Thread.h"

void * LedsSalida_actualizar(void * self);

void LedsSalida_init(const struct LedsSalida * self){
  pthread_create(self->thread,NULL,LedsSalida_actualizar,self);  
}

void * LedsSalida_actualizar(void * _self){
  struct LedsSalida * self =(struct LedsSalida *) _self;
  int i;
  for(i=0; i< self->count;i++){
    const LedConfig * ledConfig = &self->ledsConfig[i];
    if(*(ledConfig->addr) & ledConfig->mask)
      PutValLed(1,ledConfig->ledNum);
    else
      PutValLed(0,ledConfig->ledNum);
  }
  return NULL;

}
