#include "SalidaBloqueada.h"
#include "stddef.h"
#include "funciones.h"

void SalidaBloqueada_defConstructor(void * _self,va_list * args);
TipoSalida SalidaBloqueada_getTipoSalidaAdaptador(void * _self);
int SalidaBloqueada_calcularDuty(struct SalidaBanda * self,int valorDeControl);
byte SalidaBloqueada_setTipoSalidaAdaptador(void * _self, TipoSalida tipoSalida);

const struct TAdaptacionSalidaClass SalidaBloqueadaClass={
    &Class,
  "",
  &Object,
  sizeof(struct SalidaBloqueada),
  SalidaBloqueada_defConstructor,
  NULL,
    NULL, // differ
  NULL, // puto
  SalidaBloqueada_calcularDuty,
  SalidaBloqueada_getTipoSalidaAdaptador,
  SalidaBloqueada_setTipoSalidaAdaptador
};


void SalidaBloqueada_constructor(void * _self,struct AdaptSalidaConf *configuracion,struct ISalida * salida){
  struct SalidaBloqueada * self = _self;
  self->bloqueada = TRUE;
  AdaptacionSalida_constructor(_self,configuracion,salida);
  AdaptacionSalida_setTipoSalidaAdaptador(_self,SALIDA_ONOFF);
  
}

void SalidaBloqueada_defConstructor(void * _self,va_list * args){
  SalidaBloqueada_constructor(_self,va_arg(*args,void*),va_arg(*args,void*));  
}

int SalidaBloqueada_calcularDuty(struct SalidaBloqueada * self,int valorDeControl){
      
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
}

