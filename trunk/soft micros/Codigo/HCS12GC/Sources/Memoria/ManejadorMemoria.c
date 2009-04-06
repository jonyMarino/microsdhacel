#include "ManejadorMemoria.h"

word super_getWord(void * _class,void* _self,word*address){
  struct ManejadorMemoriaClass *class = super(_class);
  if(_self && class->getWord)
  return class->getWord(_self,address);
}

byte super_setWord(void * _class, void* _self,word*address,word data){
  struct ManejadorMemoriaClass *class = super(_class);
  if(_self && class->setWord)
  return class->setWord(_self,address,data);
}