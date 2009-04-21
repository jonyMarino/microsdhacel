
#include "ValvulaProporcional.h"


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



void * ValvulaProporcional_defConstruct (void * _self, va_list * app){
   super_ctor(&ValvulaProporcional,_self,app);
    va_arg(*args,ConfVal*);
    va_arg(*args,byte*);
    va_arg(*args,int);
    va_arg(*args,byte*);
    va_arg(*args,int);
}

int  ValvulaProporcional_getPotencia(void *_self){
}

void ValvulaProporcional_setPotencia(void *_self,int potencia){

  Salida_setPotencia();
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

