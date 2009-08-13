#include "ValorControl.h"


void ValorControl_constructor(void * _self, 
                              struct ValorControlConf * configuracion,
                              struct Sensor * sensor
){
  struct ValorControl * self = (struct ValorControl *)_self;
  
  self->configuracion = configuracion;
  self->sensor = sensor;                                
                              
}

void ValorControl_defConstructor(void * _self,va_list * args){
  ValorControl_constructor(_self,va_arg(*args,struct ValorControlConf *),va_arg(*args,struct Sensor *));  
}


int getValorControl(void * _self){
  struct ValorControlClass ** vTable= (struct ValorControlClass ** )_self;
  
  return (** vTable).getValorControl(_self);  

}
