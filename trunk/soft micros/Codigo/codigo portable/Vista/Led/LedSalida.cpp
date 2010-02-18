#include "LedSalida.hpp"
#include "Thread.h"

LedsSalida:: LedsSalida(const struct Array& _a,FrenteCustom & _f):frente(_f),array(_a){
  void*thread;
  pthread_create(&thread,NULL,ledsActualizar,this);
}

void*LedsSalida::ledsActualizar(void*a){
  const LedsSalida* ledSalida =(const LedsSalida*) a;
  int i;
  for(i=0; i<  Array_count(&ledSalida->array);i++){
    const LedConfig * ledConfig = (const LedConfig *)Array_get(&ledSalida->array,i);
    if(*(ledConfig->addr) & ledConfig->mask)
      (ledSalida->frente).setLed(1,ledConfig->ledNum);
    else
      ledSalida->frente.setLed(0,ledConfig->ledNum);
  }
  return NULL;

}