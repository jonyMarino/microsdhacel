#include "ValorControl.h"


void ValorControl_constructor(void * _self, 
                              struct ValorControlConf * configuracion,
                              struct Sensor * sensor
){
  struct ValorControl * self = _self;
  
  self->configuracion = configuracion;
  self->sensor = sensor;                                
                              
}

void ValorControl_defConstructor(void * _self,va_list * args){
  ValorControl_constructor(_self,va_arg(*args,void*),va_arg(*args,void*));  
}


int getValorControl(void * _self){
  struct ValorControlClass ** vTable= _self;
  
  return (** vTable).getValorControl(_self);  

}
