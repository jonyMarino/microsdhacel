
#include "SalidaRetenida_protected.h"
#include "stddef.h"
#include "funciones.h"


const struct AdaptacionSalidaClass SalidaRetenida={
  &Class,
  "",
  &Object,
  sizeof(struct SalidaRetenida),
  SalidaRetenida_defConstructor,
  NULL,
  NULL, // differ
  NULL, // puto
  SalidaRetenida_calcularDuty,
  SalidaRetenida_getTipoSalidaAdaptador,
  SalidaRetenida_setTipoSalidaAdaptador
};

void SalidaRetenida_constructor(void * _self,struct AdaptSalidaConf *configuracion,struct ISalida * salida){
  struct SalidaRetenida * self = _self;
  self->retenida = FALSE;
  AdaptacionSalida_constructor(_self,configuracion,salida);
  AdaptacionSalida_setTipoSalidaAdaptador(_self,SALIDA_ONOFF);
  
}

void SalidaRetenida_defConstructor(void * _self,va_list * args){
  SalidaRetenida_constructor(_self,va_arg(*args,void*),va_arg(*args,void*));  
}

int SalidaRetenida_calcularDuty(struct SalidaRetenida * self,int valorDeControl){    
      
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
}

void SalidaRetenida_liberar(void * _self){
  struct SalidaRetenida * self = _self;
  self->retenida = FALSE;
}

/**/
bool SalidaRetenida_getRetenida(void * _self){
  struct SalidaRetenida * self = _self;
  return self->retenida;  
}

/**/
void SalidaRetenida_setRetenida(void * _self,bool retener){
  struct SalidaRetenida * self = _self;
  self->retenida = retener;  
}

