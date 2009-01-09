#include "Retransmision_protected.h"
#include "IPWM.h"
#include "RetransmisionPWM.h"

#pragma DATA_SEG RetransmisionPWM_DATA                                            
#pragma CODE_SEG RetransmisionPWM_CODE 
#pragma CONST_SEG DEFAULT
  

void RetransmisionPWM_defConstructor(void * _self,va_list * args);

const struct LazoClass RetransmisionPWMClass={
  &Class,
  "",
  &Object,
  sizeof(struct Retransmision),
  RetransmisionPWM_defConstructor,
  Lazo_destructor,
    NULL, // differ
  NULL, // puto
  Retransmision_onNuevaMedicion,
  Retransmision_getSensor,
  Retransmision_getSalida
};


void RetransmisionPWM_constructor(void * _self,
                                  struct RetransmisionConf * configuracion,
                                  //cambiar
                                  #ifdef NDEBUG
                                  struct PWM* salida,
                                  #else
                                  struct ISalida* salida,
                                  #endif
                                  
                                  struct Sensor* sensor
){
  Retransmision_constructor(_self,configuracion,salida,sensor); 
  
  //cambiar a lo que esta comentado:
  //if( instanceOf(salida, PWM) )
  //  setPeriodo( (struct PWM*)salida,PWM_Anl);     
  #ifdef NDEBUG
    setPeriodo( (struct PWM*)salida,PWM_Anl);
  #endif  
}


void RetransmisionPWM_defConstructor(void * _self,va_list * args){
  RetransmisionPWM_constructor(_self,va_arg(*args,void*),va_arg(*args,void*),va_arg(*args,void*));  
}
