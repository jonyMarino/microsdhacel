#include <limits.h>

#include "Integrador.h"
#include "Display.h"
#include "SensorTPT_Class.h"  //cambiar : generico

void Integrador_defConstructor(void * _self,va_list * args);
int Integrador_getVal(void * _self);
void Integrador_print(void* _self,uchar numDisplay);
void Integrador_setValorInicial(void * _self);
void Integrador_onNuevaMedicion(void * _self);

extern const struct GetterClass Integrador={
  GETTER_CLASS_INITIALIZATION(GetterClass,
                              Integrador,
                              Getter,
                              Integrador_defConstructor,
                              Object_dtor,
                              Object_differ,
                              Object_puto,
                              Integrador_getVal,
                              Integrador_print)  
};


void Integrador_constructor(void * _self,void * sensor){
  struct Integrador * self = _self;
  self->acumulador = 0;
  self->constanteDeIntegracion = 1;
  self->sensor = sensor;
  self->limiteSuperior = INT_MAX;
  self->limiteInferior = INT_MIN;
  self->state = OK;
  newAlloced(&self->onNuevaMedicion,&Method,Integrador_setValorInicial,_self);
  Sensor_addNuevaMedicionListener(sensor,&self->onNuevaMedicion);
}

void Integrador_defConstructor(void * _self,va_list * args){
  super_ctor(&Integrador,_self,args);
  Integrador_constructor(_self,va_arg(*args,void*));
}

void Integrador_setValorInicial(void * _self){
  struct Integrador * self = _self;
  self->valorPrevio = _Getter_getVal(self->sensor);
  Method_setMethod(&self->onNuevaMedicion,Integrador_onNuevaMedicion);
}

void Integrador_onNuevaMedicion(void * _self){
  struct Integrador * self = _self;  
  int nuevoValor = _Getter_getVal(self->sensor);
  long valorAcumulado = self->acumulador + (long)(nuevoValor + self->valorPrevio) * _Sensor_getMeasurePeriod(self->sensor) /2; 
  int integral = valorAcumulado / ((long)self->constanteDeIntegracion * 1000);
  if( integral > self->limiteSuperior)
    self->state = OF;
  else if( integral < self->limiteInferior)
    self->state = UF;
  else{
    self->state = OK;
    self->acumulador = valorAcumulado;  
  }
  
  self->valorPrevio = nuevoValor;
}

int Integrador_getVal(void * _self){
  struct Integrador * self = _self;
  switch(self->state){
    case UF:
      return self->limiteInferior;
    case OF:
      return self->limiteSuperior;
    case OK:
      return self->acumulador / ((long)self->constanteDeIntegracion * 1000) ;
  }
}

void Integrador_print(void* _self,uchar numDisplay){
  struct Integrador * self = _self;
  Pasar_Numero(Integrador_getVal(_self),numDisplay,SenTPT_getDecimales(self->sensor));
}


int Integrador_getLimiteSuperior(void * _self){
  struct Integrador * self = _self;
  
  return self->limiteSuperior;
}


void Integrador_setLimiteSuperior(void * _self, int valor){
  struct Integrador * self = _self;
  self->limiteSuperior = valor;  
}


int Integrador_getLimiteInferior(void * _self){
  struct Integrador * self = _self;
  return self->limiteInferior;
}

void Integrador_setLimiteInferior(void * _self, int valor){
  struct Integrador * self = _self;
  self->limiteInferior = valor;  
}

void Integrador_resetAcumulador(void * _self){
  struct Integrador * self = _self;
  self->acumulador = 0;
  Method_setMethod(&self->onNuevaMedicion,Integrador_setValorInicial);
}

int Integrador_getConstanteIntegracion(void * _self){
  struct Integrador * self = _self;
  return self->constanteDeIntegracion;
}

void Integrador_setConstanteIntegracion(void * _self,int valor){
  struct Integrador * self = _self;
  self->constanteDeIntegracion = valor;
  Integrador_resetAcumulador(_self);
} 
