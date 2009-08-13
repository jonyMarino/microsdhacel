#include "SalidaRetenida_protected.h"
#include "stddef.h"
#include "funciones.h"


const struct AdaptacionSalidaClass SalidaRetenida={
  CLASS_INITIALIZATION(Class,SalidaRetenida,Object,SalidaRetenida_defConstructor,Object_dtor,Object_differ,Object_puto),
  SalidaRetenida_calcularDuty,
  SalidaRetenida_getTipoSalidaAdaptador,
  SalidaRetenida_setTipoSalidaAdaptador
};

void SalidaRetenida_constructor(void * _self,struct AdaptSalidaConf *configuracion,struct ISalida * salida){
  struct SalidaRetenida * self = (struct SalidaRetenida *)_self;
  self->retenida = FALSE;
  AdaptacionSalida_constructor(_self,configuracion,salida);
  AdaptacionSalida_setTipoSalidaAdaptador(_self,SALIDA_ONOFF);
  
}

void SalidaRetenida_defConstructor(void * _self,va_list * args){
  SalidaRetenida_constructor(_self,va_arg(*args,struct AdaptSalidaConf *),va_arg(*args,struct ISalida *));  
}

int SalidaRetenida_calcularDuty(void * _self,int valorDeControl){    
      struct SalidaRetenida * self = (struct SalidaRetenida *)_self;
      if(self->retenida == FALSE){      
        int duty;          
        int ha = AdaptacionSalida_getHisteresis(self);
        
        duty = duty_onoff(valorDeControl, 	//variable
                            ha 	            //histeresis
                            );	           
        
        if(duty==1000)
  		    self->retenida = TRUE;          
        return duty;                    
      }
      return 1000;
}

TipoSalida SalidaRetenida_getTipoSalidaAdaptador(void * _self){
  return SALIDA_ONOFF;
}

/**/
byte SalidaRetenida_setTipoSalidaAdaptador(void * _self, TipoSalida tipoSalida){
  return 0;
}

void SalidaRetenida_liberar(void * _self){
  struct SalidaRetenida * self = (struct SalidaRetenida *)_self;
  self->retenida = FALSE;
}

/**/
bool SalidaRetenida_getRetenida(void * _self){
  struct SalidaRetenida * self = (struct SalidaRetenida *)_self;
  return self->retenida;  
}

/**/
void SalidaRetenida_setRetenida(void * _self,bool retener){
  struct SalidaRetenida * self = (struct SalidaRetenida *)_self;
  self->retenida = retener;  
}

