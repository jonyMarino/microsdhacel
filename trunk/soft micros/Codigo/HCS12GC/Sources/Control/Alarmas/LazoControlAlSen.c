#include "LazoControlAlSen.h"
#include "LazoControl_protected.h"
#include "SalidaRetenida.h"


void LazoControlAlSen_defConstructor(void * _self,va_list * args);
void * LazoControlAlSen_destructor(void * _self);
struct ISalida*LazoControlAlSen_getSalida(void * _self);

const struct LazoClass LazoControlAlSen={
  &Class,
  "",
  &Object,
  sizeof(struct LazoControlAlSen),
  LazoControlAlSen_defConstructor,
  LazoControlAlSen_destructor,
  NULL,
  NULL,
  LazoControl_onNuevaMedicion,
  LazoControl_getSensor,
  LazoControlAlSen_getSalida
};

static void factoryAdaptSalida(struct LazoControlAlSen * self, TAdaptador adaptSalida);

/**/
void LazoControlAlSen_constructor(void * _self, 
                             struct ConfLazoCntrlAlSen * configuracion,
                             struct ISalida * salida,
                             struct Sensor * sensor 
                             
){
  struct LazoControlAlSen * self = _self;
  
  newAlloced(&self->control,&CntrProporcionalInvClass,&configuracion->confControl,sensor);
  newAlloced(&self->salidaInvertida,&SalidaInvertida,salida);
  self->configuracion = configuracion;
  factoryAdaptSalida(_self, _ConfLazoCntrlAlSen_getAdaptadorSalida(configuracion) );
  //cuidado! el constructor se llama al final a proposito
  LazoControl_constructor(_self,&self->control,self->adaptadorSalida);
  
}

/**/
void LazoControlAlSen_defConstructor(void * _self,va_list * args){
  LazoControlAlSen_constructor(_self,va_arg(*args,void*),va_arg(*args,void*),va_arg(*args,void*));  
}

/**/
void factoryAdaptSalida(struct LazoControlAlSen * self, TAdaptador adaptSalida){
  switch(adaptSalida){
    case SALIDA_RETENIDA:
        SalidaInvertida_setInvertida(&self->salidaInvertida,FALSE);
        newAlloced(self->adaptadorSalida,&SalidaRetenidaClass, _ConfLazoCntrlAlSen_getConfAdaptador(self->configuracion),&self->salidaInvertida);        
        break;
    case SALIDA_DEFECTO_RETENIDA:
        SalidaInvertida_setInvertida(&self->salidaInvertida,TRUE);
        newAlloced(self->adaptadorSalida,&SalidaRetenidaBajo, _ConfLazoCntrlAlSen_getConfAdaptador(self->configuracion),&self->salidaInvertida);        
        break;
    case SALIDA_DEFECTO_BLOQUEADA:
        SalidaInvertida_setInvertida(&self->salidaInvertida,FALSE);
        newAlloced(self->adaptadorSalida,&SalidaBloqueadaClass, _ConfLazoCntrlAlSen_getConfAdaptador(self->configuracion),&self->salidaInvertida);        
        break;
    case SALIDA_DEFECTO:         
        SalidaInvertida_setInvertida(&self->salidaInvertida,TRUE);       
        newAlloced(self->adaptadorSalida,&SalidaBanda, _ConfLazoCntrlAlSen_getConfAdaptador(self->configuracion),&self->salidaInvertida);        
      break;
    case SALIDA_EXCESO:
    default:  //error
        SalidaInvertida_setInvertida(&self->salidaInvertida,FALSE);
        newAlloced(self->adaptadorSalida,&SalidaBanda, _ConfLazoCntrlAlSen_getConfAdaptador(self->configuracion),&self->salidaInvertida);
      break;      
  }
}


/**/
void * LazoControlAlSen_destructor(void * _self){
  struct LazoControlAlSen * self = _self;
  deleteAlloced(self->adaptadorSalida);
  deleteAlloced(&self->control);
  return Lazo_destructor(_self);  //cambiar : el descriptor de clase debe tener info de cual es la clase siguiente para llamar a su destructor  
}

TAdaptador  LazoControlAlSen_getAdaptadorSalida(void*_self){
  struct LazoControlAlSen * self = _self;
  return _ConfLazoCntrlAlSen_getAdaptadorSalida(self->configuracion);
}

byte LazoControlAlSen_setAdaptadorSalida(void*_self,TAdaptador adaptSalida){
  struct LazoControlAlSen * self = _self;
  byte err = _ConfLazoCntrlAlSen_setAdaptadorSalida(self->configuracion,adaptSalida);
  if(!err){
    deleteAlloced(self->adaptadorSalida);    //thread unsafe con LazoControl_onNuevaMedicion
    factoryAdaptSalida(self,adaptSalida);    
  }
}

int   LazoControlAlSen_getValor(void*_self){
  struct LazoControlAlSen * self = _self;
  return ValorControl_getValorControlador(&self->control);
}

byte  LazoControlAlSen_setValor(void*_self,int valor){
  struct LazoControlAlSen * self = _self;
  return ValorControl_setValorControlador(&self->control,valor);
}

int   LazoControlAlSen_getHisteresis(void*_self){
  struct LazoControlAlSen * self = _self;
  return getHisteresis(self->adaptadorSalida);
}

byte  LazoControlAlSen_setHisteresis(void*_self,int histeresis){
  struct LazoControlAlSen * self = _self;
  return setHisteresis(self->adaptadorSalida,histeresis);
}

struct ISalida*LazoControlAlSen_getSalida(void * _self){
  struct LazoControlAlSen * self = _self;
  return DecoradorSalida_getDecorado(&self->salidaInvertida);
}
