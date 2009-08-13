#include "Retransmision.h"
#include "Retransmision_protected.h"

#pragma DATA_SEG Retransmision_DATA                                            
#pragma CODE_SEG Retransmision_CODE 
#pragma CONST_SEG DEFAULT


const struct LazoClass Retransmision={
  CLASS_INITIALIZATION(LazoClass,Retransmision,Lazo,Retransmision_defConstructor,Lazo_destructor,Object_differ,Object_puto), 
  Retransmision_onNuevaMedicion,
  Retransmision_getSensor,
  Retransmision_getSalida
};

void Retransmision_constructor(void * _self,struct RetransmisionConf * configuracion,struct ISalida* salida,struct Sensor* sensor){
  struct Retransmision * self = (struct Retransmision *)_self;
  Lazo_constructor(_self,sensor);
  self->configuracion = configuracion;
  self->salida = salida;
  self->sensor = sensor; 
     
}

void Retransmision_defConstructor(void * _self,va_list * args){
  Retransmision_constructor(_self,va_arg(*args,struct RetransmisionConf *),va_arg(*args,struct ISalida*),va_arg(*args,struct Sensor*));  
}


struct Sensor* Retransmision_getSensor(void * _self){
  struct Retransmision * self = (struct Retransmision *)_self;
  return self->sensor;
}

struct ISalida* Retransmision_getSalida(void * _self){
  struct Retransmision * self = (struct Retransmision *)_self;
  return self->salida;           
}

void Retransmision_onNuevaMedicion(void * _self){
  struct Retransmision * self = (struct Retransmision *)_self;
  int retLow = _RetransmisionConf_getRetLow(self->configuracion);
  int retHi = _RetransmisionConf_getRetHi(self->configuracion);
  int retVal = _Getter_getVal(self->sensor);
  int duty; 
   
   long dutyTmp=((long)(retVal - retLow))*1000/( retHi- retLow ); 

   if(dutyTmp>1000)
    duty=1000;
   else if(dutyTmp<0)
    duty=0;
   else
    duty=(int)dutyTmp; 
   
   setPotenciaSalida(self->salida,duty);
}
