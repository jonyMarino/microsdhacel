#include "IBaseTiempo.h" 

const struct IBaseTiempoClass IBaseTiempo;

bool isConfigurado(void* _self){
  struct IBaseTiempoClass * class = classOf(_self);
  return class->isConfigurado(_self);   
}