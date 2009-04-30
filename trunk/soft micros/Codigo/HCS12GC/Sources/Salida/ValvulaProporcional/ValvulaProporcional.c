
#include "ValvulaProporcional.h"
#include "Salida.h"
#include "Salida_protected.h"
#include "stdarg.h"
#include "Timer.h"
#include "PE_Types.h"
#include "Errores.h"
#include "PE_Error.h"
#include "Mydefines.h"
#include "IO_MAP.h"
#include "ManejadorMemoria.h"

#define  MAX_TIEMPOABIERTO 65500
#define  MAX_BANDAMUERTA   65500

extern struct FlashBkpEnFlash flash;

void ValvulaProporcional_defConstruct (void * _self, va_list * args);
uint ValvulaProporcional_getPotencia(void *_self);
void ValvulaProporcional_setPotencia(void *_self,int potencia);
TipoSalida ValvulaProporcional_getTipoSalida(void *_self);
void ValvulaProporcional_setTipoSalida(void *_self,TipoSalida tipoSalida);
TError set_tiempoAbierto(void *_self,int value);
TError set_bandaMuerta(void *_self,int value);
void  ValvulaProporcional_onCheckear(void *_self,int potencia);
int get_tiempoAbierto(void *_self);
int get_LimSup_tiempoAbierto(void);
int get_bandaMuerta(void *_self);
int get_LimSup_bandaMuerta(void);
  
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


void ValvulaProporcional_constructor(void * _self,ConfValvulaProporcional * conf,byte * puertoApertura,int bitApertura,byte * puertoCierre,int bitCierre){
  struct ValvulaProporcional* self = _self;
  Salida_constructor(self);
  self->conf=conf;
  self->puertoApertura =  puertoApertura;
  self->puertoCierre =  puertoCierre ;
  self->mascaraApertura = 1<<bitApertura;
  self->mascaraCierre = 1<<bitCierre;
  newAlloced(&self->timer,&MethodTimer,20,ValvulaProporcional_onCheckear,self);

    
}

void ValvulaProporcional_defConstruct(void * _self, va_list * args){
  super_ctor(&ValvulaProporcional,_self,args);
  ValvulaProporcional_constructor(_self,va_arg(*args,ConfValvulaProporcional*),va_arg(*args,byte*),va_arg(*args,int),va_arg(*args,byte*),va_arg(*args,int));
}

static void cerrar(void * _self){
  //TO_DO
}

static void abrir(void * _self){
  //TO_DO
}

static void detener(void * _self){
  //TO_DO
}

void  ValvulaProporcional_onCheckear(void *_self){  
//cada 20ms es llamado 
  struct ValvulaProporcional* self = _self;
  int potencia = Salida_getPotencia(_self);

}
uint  ValvulaProporcional_getPotencia(void *_self){
  
  return getPotencia(_self);

}



void ValvulaProporcional_setPotencia(void *_self,int potencia){

  Salida_setPotencia(_self,potencia);


}


TipoSalida ValvulaProporcional_getTipoSalida(void *_self){

  return SALIDA_PROPORCIONAL;

}

void ValvulaProporcional_setTipoSalida(void *_self,TipoSalida tipoSalida){
   return;
}

int get_tiempoAbierto(void *_self) {
  struct ValvulaProporcional* self = _self;
  
  return _MANEJADOR_MEMORIA_GET_BYTE(&flash,&self->conf->tiempoAbierto);
 
}
     
TError set_tiempoAbierto(void *_self,int value) {
  
  struct ValvulaProporcional* self = _self;
  
  return _MANEJADOR_MEMORIA_SET_BYTE(&flash,&self->conf->tiempoAbierto,(uchar)value);
  
}

int get_LimSup_tiempoAbierto(void){
  return MAX_TIEMPOABIERTO;
}


TError set_bandaMuerta(void *_self,int value) {

struct ValvulaProporcional* self = _self;
  
return _MANEJADOR_MEMORIA_SET_BYTE(&flash,&self->conf->bandaMuerta,(uchar)value); 

}


int get_bandaMuerta(void *_self) {
  struct ValvulaProporcional* self = _self;
  
  return _MANEJADOR_MEMORIA_GET_BYTE(&flash,&self->conf->bandaMuerta);
 
}

int get_LimSup_bandaMuerta(void){
  return MAX_BANDAMUERTA;
}