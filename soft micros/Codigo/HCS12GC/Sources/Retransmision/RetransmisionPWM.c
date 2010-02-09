#include "Retransmision_protected.h"
#include "IPWM.h"
#include "RetransmisionPWM.h"

#pragma DATA_SEG RetransmisionPWM_DATA                                            
#pragma CODE_SEG RetransmisionPWM_CODE 
#pragma CONST_SEG DEFAULT
  

void RetransmisionPWM_defConstructor(void * _self,va_list * args);

const struct LazoClass RetransmisionPWM={
  CLASS_INITIALIZATION(LazoClass,RetransmisionPWM,Retransmision,RetransmisionPWM_defConstructor,Lazo_destructor,Object_differ,Object_puto),
  Retransmision_onNuevaMedicion,
  Retransmision_getSensor,
  Retransmision_getSalida
};


void RetransmisionPWM_constructor(void * _self,
                                  struct RetransmisionConf * configuracion,
                                  struct ISalida* salida,
                                  struct Sensor* sensor
){
  Retransmision_constructor(_self,configuracion,(struct ISalida*)salida,sensor); 
  if( instanceOf(salida, (const struct Class * const)&IPWM) )
    setPeriodo( (struct PWM*)salida,PWM_Anl); 
}


void RetransmisionPWM_defConstructor(void * _self,va_list * args){
  RetransmisionPWM_constructor(_self,va_arg(*args,struct RetransmisionConf *),va_arg(*args,struct ISalida*),va_arg(*args,struct Sensor*));  
}
