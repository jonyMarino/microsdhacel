/*  MODULE: SalidaClass.c*/
#include "Salida.h"
#include "Salida_protected.h"


const struct ISalidaClass Salida;/*={
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
}        */

void Salida_constructor(void * self){
  struct Salida * salida=self;
  
  salida->conectado=FALSE;
  salida->duty=0;   
  
}


void setPotenciaSalida(void* self,int duty){
  struct ISalida * salida=self;
  
  if(!getConectada(salida) || duty<0 || duty>1000)  
    return; //error
    
  setPotencia(self,duty);
}

void setConectada(void* self,bool conectar){
  struct ISalidaClass ** vTable=self;
  (**vTable).setConectada(self,conectar);  
}

bool getConectada(void * self){
  struct ISalidaClass ** vTable=self;
  return (**vTable).getConectada(self);  
}

void Salida_setConectada(void* self,bool conectar){
  struct Salida * salida=self;
  
   if(salida->conectado && !conectar)
    setPotencia(self,0); 
   
   salida->conectado=conectar;
}

bool Salida_getConectada(void * self){
  struct Salida * salida=self;
  return salida->conectado;
}

void Salida_setPotencia(void* _self,uint duty){
  struct ISalidaClass ** vTable=_self;
  struct Salida * self=_self;
  
  if(_getTipoSalida(self)==SALIDA_PROPORCIONAL) 
    self->duty = duty; 
  else{
    if(duty)
      self->duty = 1000;
    else
      self->duty = 0;
  }  
}

void setPotencia(void* _self,uint duty){
  struct ISalidaClass ** _class=_self;
  struct ISalida * salida=_self;
  
  (*((*_class)->setPotencia))(_self,duty);  
    
}


void super_setPotencia(void * _class,void* _self,uint duty){
  struct ISalidaClass ** superclass=super(_class);
  
  (*((*superclass)->setPotencia))(_self,duty);  
    
}

uint getPotencia(void* _self){
  struct ISalidaClass ** class=_self;
  
  return (*((*class)->getPotencia))(_self);    
}

TipoSalida getTipoSalida(void* _self){
  struct ISalidaClass ** class=_self;
  return (**class).getTipoSalida(_self);    
}


void setTipoSalida(void* _self,TipoSalida onoff){
  struct ISalidaClass ** vTable=_self;
  (**vTable).setTipoSalida(_self,onoff);    
}


uint Salida_getPotencia(void* self){
  struct Salida * salida=self;
  
  return salida->duty;  
}