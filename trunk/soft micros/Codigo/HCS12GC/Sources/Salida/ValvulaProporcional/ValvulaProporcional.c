
#include "ValvulaProporcional.h"
#include "Salida.h"
#include "Salida_protected.h"
#include "stdarg.h"

void * ValvulaProporcional_defConstruct (void * _self, va_list * args);
int  ValvulaProporcional_getPotencia(void *_self);
void ValvulaProporcional_setPotencia(void *_self,int potencia);
TipoSalida ValvulaProporcional_getTipoSalida(void *_self);
void ValvulaProporcional_setTipoSalida(void *_self,TipoSalida tipoSalida);
void set_tiempoAbierto(int value);
void set_bandaMuerta(int value);
  
 const struct ISalidaClass ValvulaProporcional={
  ISALIDA_CLASS_INITIALIZATION(ISalidaClass,
                            ValvulaProporcional,
                            Salida,
                            ValvulaProporcional_defConstruct,
                            Object_dtor,
                            Object_differ,
                            Object_puto,
                            ValvulaProporcional_getPotencia,
                            ValvulaProporcional_setPotencia,
                            ValvulaProporcional_getTipoSalida,
                            ValvulaProporcional_setTipoSalida,
                            Salida_getConectada,
                            Salida_setConectada
                            )
};


void ValvulaProporcional_Construct(struct ValvulaProporcional* self,ConfValvulaProporcional * conf,byte * salida,int bit){
  Salida_constructor(self);
  self->conf=conf;
  //self->salida = salida;
  //self->mask=1<<bit;
  //newAlloced(&self->timer,&MethodTimer,(ulong)periodos[PWM_getPeriodo(self)],PWMSoft_onCambio,self);
  //Timer_Stop(&self->timer);
    
}

void * ValvulaProporcional_defConstruct (void * _self, va_list * args){
  ValvulaProporcional_Construct(_self,va_arg(*args,void*),va_arg(*args,byte*),va_arg(*args,int));


}

int  ValvulaProporcional_getPotencia(void *_self){
}



void ValvulaProporcional_setPotencia(void *_self,int potencia){

  Salida_setPotencia(_self,potencia);
}


TipoSalida ValvulaProporcional_getTipoSalida(void *_self){

  return SALIDA_PROPORCIONAL;

}

void ValvulaProporcional_setTipoSalida(void *_self,TipoSalida tipoSalida){

  

}

void set_tiempoAbierto(int value) {
 // tiempoAbierto = value;
}

void set_bandaMuerta(int value) {
 // bandaMuerta = value;
}

