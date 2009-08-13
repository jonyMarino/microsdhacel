
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
#include "RlxMTimer.h"

#define  MAX_TIEMPOABIERTO 10000
#define  MAX_BANDAMUERTA   10000
#define  FACTOR_SEGURIDAD  1

extern struct ManejadorMemoria *const pFlash;

void ValvulaProporcional_defConstruct (void * _self, va_list * args);
uint ValvulaProporcional_getPotencia(void *_self);
void ValvulaProporcional_setPotencia(void *_self,uint potencia);
TipoSalida ValvulaProporcional_getTipoSalida(void *_self);
void ValvulaProporcional_setTipoSalida(void *_self,TipoSalida tipoSalida);
TError set_tiempoAbierto(void *_self,int value);
TError set_bandaMuerta(void *_self,int value);
void  ValvulaProporcional_onCheckear(void *_self);
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
  struct ValvulaProporcional* self = (struct ValvulaProporcional*)_self;
  word tiempo=get_tiempoAbierto(self);
  Salida_constructor(self);
  self->conf=conf;
  self->puertoApertura =  puertoApertura;
  self->puertoCierre =  puertoCierre ;
  self->mascaraApertura = 1<<bitApertura;
  self->mascaraCierre = 1<<bitCierre;
  self->timeCloseInit = (tiempo + FACTOR_SEGURIDAD)*1000/20;   //calculo el tiempo de cierre inicial(en milisegundos),divido por 20 por que cada 20ms actualizo
  self->timeActual = 0;
  set_tiempoAbierto(self,10);
  newAlloced(&self->timer,&RlxMTimer,(ulong)10,ValvulaProporcional_onCheckear,self);
    
}

void ValvulaProporcional_defConstruct(void * _self, va_list * args){
  super_ctor(&ValvulaProporcional,_self,args);
  ValvulaProporcional_constructor(_self,va_arg(*args,ConfValvulaProporcional*),va_arg(*args,byte*),va_arg(*args,int),va_arg(*args,byte*),va_arg(*args,int));
}

static void cerrar(void * _self){
  struct ValvulaProporcional* self = (struct ValvulaProporcional*)_self;
  clrReg8Bits(*(self->puertoApertura),(self->mascaraApertura));                           
  setReg8Bits(*(self->puertoCierre), (self->mascaraCierre));
}

static void abrir(void * _self){
  struct ValvulaProporcional* self = (struct ValvulaProporcional*)_self;
  clrReg8Bits(*(self->puertoCierre),(self->mascaraCierre));                           
  setReg8Bits(*(self->puertoApertura),(self->mascaraApertura));
}

static void detener(void * _self){
  struct ValvulaProporcional* self = (struct ValvulaProporcional*)_self;
  clrReg8Bits(*(self->puertoCierre), (self->mascaraCierre));                           
  clrReg8Bits(*(self->puertoApertura),(self->mascaraApertura));
}

void  ValvulaProporcional_onCheckear(void *_self){  
//cada 10ms es llamada 
  struct ValvulaProporcional* self = (struct ValvulaProporcional*)_self;
  word timesOpenClose,timesMuerto;
  word potencia_vp =43; // Salida_getPotencia(&self->super);
  if((self->timeCloseInit)>0){
    (self->timeCloseInit)--;
    cerrar(self);  // inicio cerrando durante el tiempo "timeCloseInit"
    return;
  } else if(potencia_vp == 1000)
            abrir(self);
         else if(potencia_vp == 0)
            detener(self);
               else{
                 timesOpenClose=potencia_vp*(self->conf->tiempoAbierto);  //tiempo en milisegundos
                 timesMuerto=(self->conf->bandaMuerta)*1000;
                 if((timesOpenClose>(self->timeActual))) {
                  abrir(self);
                  self->timeActual = (self->timeActual + 10);
                 }
                 else if((timesOpenClose<(self->timeActual))) {
                        cerrar(self);
                        self->timeActual = (self->timeActual - 10);
                 }
                       else
                        detener(self); 
               }
               if((timesOpenClose==self->timeActual)||(timesOpenClose<(self->timeActual+timesMuerto))||(timesOpenClose>(self->timeActual-timesMuerto)))
                 detener(self); 
               
}

uint  ValvulaProporcional_getPotencia(void *_self){
  struct ValvulaProporcional* self = (struct ValvulaProporcional*)_self;
  word potenciaActual;
  potenciaActual = (self->timeActual)/(self->conf->tiempoAbierto); // ya que timeActual esta en miliseg y tiempoAbierto en seg, no multiplico por 1000
  
  return potenciaActual;

}



void ValvulaProporcional_setPotencia(void *_self,word potencia){

  Salida_setPotencia(_self,potencia);


}


TipoSalida ValvulaProporcional_getTipoSalida(void *_self){

  return SALIDA_PROPORCIONAL;

}

void ValvulaProporcional_setTipoSalida(void *_self,TipoSalida tipoSalida){
   return;
}

int get_tiempoAbierto(void *_self) {
  struct ValvulaProporcional* self = (struct ValvulaProporcional*)_self;
  
  return _MANEJADOR_MEMORIA_GET_WORD(pFlash,(word*)&self->conf->tiempoAbierto);
 
}
     
TError set_tiempoAbierto(void *_self,int value) {
  
  struct ValvulaProporcional* self = (struct ValvulaProporcional*)_self;
  
  return _MANEJADOR_MEMORIA_SET_WORD(pFlash,(word*)&self->conf->tiempoAbierto,(uchar)value);
  
}

int get_LimSup_tiempoAbierto(void){
  return MAX_TIEMPOABIERTO;
}


TError set_bandaMuerta(void *_self,int value) {

struct ValvulaProporcional* self = (struct ValvulaProporcional*)_self;
  
return _MANEJADOR_MEMORIA_SET_WORD(pFlash,(word*)&self->conf->bandaMuerta,(uchar)value); 

}


int get_bandaMuerta(void *_self) {
  struct ValvulaProporcional* self = (struct ValvulaProporcional*)_self;
  
  return _MANEJADOR_MEMORIA_GET_WORD(pFlash,(word*)&self->conf->bandaMuerta);
 
}

int get_LimSup_bandaMuerta(void){
  return MAX_BANDAMUERTA;
}