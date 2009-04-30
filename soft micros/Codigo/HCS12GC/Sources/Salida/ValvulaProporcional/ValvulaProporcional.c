
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


/*void ValvulaProporcional_Construct(void * _self,ConfValvulaProporcional * conf,byte * salida,int bit,byte * salida,int bit){
  struct ValvulaProporcional* self = _self;
  Salida_constructor(self);
  self->conf=conf;
  //self->salida = salida;
  //self->mask=1<<bit;
  newAlloced(&self->timer,&MethodTimer,20,ValvulaProporcional_onCheckear,self);
  //Timer_Stop(&self->timer);
    
}
*/
void ValvulaProporcional_defConstruct (void * _self, va_list * args){
  //ValvulaProporcional_Construct(_self,va_arg(*args,ConfValvulaProporcional*),va_arg(*args,byte*),va_arg(*args,int),va_arg(*args,byte),va_arg(*args,int));
  struct ValvulaProporcional* self = _self;  
  ConfValvulaProporcional * conf=va_arg(*args,ConfValvulaProporcional*); 
  Salida_constructor(self);
  self->conf=conf;
  newAlloced(&self->timer,&MethodTimer,20,ValvulaProporcional_onCheckear,self);
}

void  ValvulaProporcional_onCheckear(void *_self,int potencia,int bandaProporcional,word medicion,word setpoint){  
//cada 20ms es llamado 
  struct ValvulaProporcional* self = _self;
  char mascara;
  dword tiemAperTemp_mseg;
  //dword contTiempo;
    
  if(medicion>(setpoint+(bandaProporcional/2))) {  //esta por encima de la banda proporcional ?
    mascara = (PTT & 0xBF) | 0x80;
    setReg8Bits(PTT, mascara); // pongo en 1 la salida 7 y en cero la salida 6 del puerto PTT (apertura)
  }
 else if(medicion<(setpoint-(bandaProporcional/2))) { //esta por debajo de la banda proporcional ?
    mascara = (PTT & 0x7F) | 0x40;  
    setReg8Bits(PTT, mascara); // pongo en 1 la salida 6 y en cero la salida 7 del puerto PTT (cierre)
 } else{    // esta en la banda proporcional
     
     tiemAperTemp_mseg = (self->conf->tiempoAbierto)*potencia;
    // contTiempo = tiemAperTemp_mseg/20;
     if(tiemAperTemp_mseg != 0) {  //al bajar la potencia el Tiempo disminuye
        mascara = (PTT & 0xBF) | 0x80;
        setReg8Bits(PTT, mascara); // pongo en 1 la salida 7 y en cero la salida 6 del puerto PTT (apertura)  
        //contTiempo--;
     }else{
        mascara = (PTT & 0x7F) | 0x40;  
        setReg8Bits(PTT, mascara); // pongo en 1 la salida 6 y en cero la salida 7 del puerto PTT (cierre)
     }
 }
 

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
   struct ValvulaProporcional* self = _self;
   self->conf->tipoSalida = tipoSalida;
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