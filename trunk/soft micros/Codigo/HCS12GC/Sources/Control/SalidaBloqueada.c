#include "SalidaBloqueada.h"
#include "stddef.h"
#include "funciones.h"

void SalidaBloqueada_defConstructor(void * _self,va_list * args);
TipoSalida SalidaBloqueada_getTipoSalidaAdaptador(void * _self);
int SalidaBloqueada_calcularDuty(void * _self,int valorDeControl);
byte SalidaBloqueada_setTipoSalidaAdaptador(void * _self, TipoSalida tipoSalida);

const struct AdaptacionSalidaClass SalidaBloqueada={
   CLASS_INITIALIZATION(Class,SalidaBloqueada,Object,SalidaBloqueada_defConstructor,Object_dtor,Object_differ,Object_puto),
  SalidaBloqueada_calcularDuty,
  SalidaBloqueada_getTipoSalidaAdaptador,
  SalidaBloqueada_setTipoSalidaAdaptador
};


void SalidaBloqueada_constructor(void * _self,struct AdaptSalidaConf *configuracion,struct ISalida * salida){
  struct SalidaBloqueada * self = (struct SalidaBloqueada *)_self;
  self->bloqueada = TRUE;
  AdaptacionSalida_constructor(_self,configuracion,salida);
  AdaptacionSalida_setTipoSalidaAdaptador(_self,SALIDA_ONOFF);
  
}

void SalidaBloqueada_defConstructor(void * _self,va_list * args){
  SalidaBloqueada_constructor(_self,va_arg(*args,struct AdaptSalidaConf *),va_arg(*args,struct ISalida *));  
}

int SalidaBloqueada_calcularDuty(void * _self,int valorDeControl){
      struct SalidaBloqueada * self = (struct SalidaBloqueada *)_self;
      if( !getConectada( AdaptacionSalida_getSalida(self) ) )
        return 0;
      else{      
        int duty;          
        int ha = AdaptacionSalida_getHisteresis(self);
        
        duty = duty_onoff(valorDeControl, 	      //variable
                            ha 	          //histeresis
                            );	            //valor del duty  
        
        
        
        if(self->bloqueada == TRUE){
          
          if(duty==1000 ||    
          duty ==-1)  // -1 = dentro de la banda
  		      self->bloqueada = FALSE; 
          else 
            duty=1000;
        }
        
        if(duty ==-1)
            return -1;
        duty = 1000 - duty; //invierto la salida
        
        return duty;                    
      }
}

TipoSalida SalidaBloqueada_getTipoSalidaAdaptador(void * _self){
  return SALIDA_ONOFF;
}

/**/
byte SalidaBloqueada_setTipoSalidaAdaptador(void * _self, TipoSalida tipoSalida){
  return 0;
}

