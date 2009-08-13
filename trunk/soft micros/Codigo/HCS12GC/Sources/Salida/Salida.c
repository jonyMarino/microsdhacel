/*  MODULE: SalidaClass.c*/
#include "Salida.h"
#include "Salida_protected.h"


const struct ISalidaClass Salida={
    ISALIDA_CLASS_INITIALIZATION(ISalidaClass,
                            Salida,
                            ISalida,
                            Object_ctor,
                            Object_dtor,
                            Object_differ,
                            Object_puto,
                            Salida_getPotencia,
                            Salida_setPotencia,
                            NULL,
                            NULL,
                            Salida_getConectada,
                            Salida_setConectada
                            )
};        

void Salida_constructor(void * self){
  struct Salida * salida= (struct Salida *)self;
  
  salida->conectado=FALSE;
  salida->duty=0;   
  
}


void setPotenciaSalida(void* self,int duty){
  struct ISalida * salida=(struct ISalida *)self;
  
  if(!getConectada(salida) || duty<0 || duty>1000)  
    return; //error
    
  setPotencia(self,duty);
}

void setConectada(void* self,bool conectar){
  struct ISalidaClass ** vTable=(struct ISalidaClass **)self;
  (**vTable).setConectada(self,conectar);  
}

bool getConectada(void * self){
  struct ISalidaClass ** vTable=(struct ISalidaClass **)self;
  return (**vTable).getConectada(self);  
}

void Salida_setConectada(void* self,bool conectar){
  struct Salida * salida=(struct Salida *)self;
  
   if(salida->conectado && !conectar)
    setPotencia(self,0); 
   
   salida->conectado=conectar;
}

bool Salida_getConectada(void * self){
  struct Salida * salida=(struct Salida *)self;
  return salida->conectado;
}

void Salida_setPotencia(void* _self,uint duty){
  struct ISalidaClass ** vTable=(struct ISalidaClass **)_self;
  struct Salida * self=(struct Salida *)_self;
  
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
  struct ISalidaClass ** _class=(struct ISalidaClass **)_self;
  struct ISalida * salida=(struct ISalida *)_self;
  
  (*((*_class)->setPotencia))(_self,duty);  
    
}


void super_setPotencia(void * _class,void* _self,uint duty){
  struct ISalidaClass ** superclass=(struct ISalidaClass **)super(_class);
  
  (*((*superclass)->setPotencia))(_self,duty);  
    
}

uint getPotencia(void* _self){
  struct ISalidaClass ** _class=(struct ISalidaClass **)_self;
  
  return (*((*_class)->getPotencia))(_self);    
}

TipoSalida getTipoSalida(void* _self){
  struct ISalidaClass ** _class=(struct ISalidaClass **)_self;
  return (**_class).getTipoSalida(_self);    
}


void setTipoSalida(void* _self,TipoSalida onoff){
  struct ISalidaClass ** vTable=(struct ISalidaClass **)_self;
  (**vTable).setTipoSalida(_self,onoff);    
}


uint Salida_getPotencia(void* self){
  struct Salida * salida=(struct Salida *)self;
  
  return salida->duty;  
}