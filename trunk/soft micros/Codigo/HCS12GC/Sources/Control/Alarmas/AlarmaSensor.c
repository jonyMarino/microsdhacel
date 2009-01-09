#include "AlarmaSensor.h"
#include "SalidaBanda.h"

void AlarmaSensor_defConstructor(void * _self,va_list * args);


const struct Class AlarmaSensor={
  &Class,
  "",
  &Object,
  sizeof(struct AlarmaSensor),
  AlarmaSensor_defConstructor,
  NULL,
  NULL
};

static void crearLazo(struct AlarmaSensor *self,TTipoAlarma tipoAlarma,struct ISalida * salida,struct Sensor * sensor);


void AlarmaSensor_constructor(void * _self, 
                              struct AlarmaSenConf * configuracion,
                              struct ISalida * salida,
                              struct Sensor * sensor
) {
  struct AlarmaSensor * self = _self;
  
  Alarma_constructor(self,(struct AlarmaConf*)configuracion);
 
  crearLazo(self,_AlarmaConf_getLazo(configuracion),salida,sensor);
}

void AlarmaSensor_defConstructor(void * _self,va_list * args){
  AlarmaSensor_constructor(_self,va_arg(*args,void*),va_arg(*args,void*),va_arg(*args,void*));  
}

void crearLazo(struct AlarmaSensor *self,TTipoAlarma tipoAlarma,struct ISalida * salida,struct Sensor * sensor){  

  switch(tipoAlarma){
    case ALARMA_RETRANSMISION:
      newAlloced(self->lazo,&RetransmisionPWMClass,_AlarmaConf_getRetConf( Alarma_getConfiguracion(self) ),salida,sensor);        
    break;
    case ALARMA_CONTROL:
    default:
      newAlloced(self->lazo,&LazoControlAlSen,_AlarmaSenConf_getLazoCntrAlConf( Alarma_getConfiguracion(self) ),salida,sensor);  
    break;
  }

}
                             


TTipoAlarma  AlarmaSensor_getTipo(void* _self){
  struct AlarmaSensor *self = _self;
  return _AlarmaConf_getLazo( Alarma_getConfiguracion(self) );
}

byte AlarmaSensor_setTipo(void*_self,TTipoAlarma tipoAlarma){
  struct AlarmaSensor *self = _self;
  byte err = _AlarmaConf_setLazo( Alarma_getConfiguracion(self) ,tipoAlarma);
  if(!err){
    struct ISalida * salida = getSalida(self->lazo);
    struct Sensor * sensor = getSensor(self->lazo);
    deleteAlloced(self->lazo);
    crearLazo(self,tipoAlarma,salida,sensor);
  }
  return err;
}

TAdaptador  AlarmaSensor_getAdaptadorSalida(void*_self){
  struct AlarmaSensor *self = _self;
  if( classOf(self->lazo)==&LazoControlAlSen)
    return LazoControlAlSen_getAdaptadorSalida(self->lazo);    
  else
    return _AlarmaSenConf_getAdaptadorSalida( Alarma_getConfiguracion(self) );
  
}

byte AlarmaSensor_setAdaptadorSalida(void*_self,TAdaptador adaptSalida){
  struct AlarmaSensor *self = _self;
  if( classOf(self->lazo)==&LazoControlAlSen)
    return LazoControlAlSen_setAdaptadorSalida(self->lazo,adaptSalida);    
  else
    return _AlarmaSenConf_setAdaptadorSalida( Alarma_getConfiguracion(self) ,adaptSalida);
}

int   Alarma_getValor(void*_self){
  struct AlarmaSensor *self = _self;
  if( classOf(self->lazo)==&LazoControlAlSen)
    return LazoControlAlSen_getValor(self->lazo);  
  else  
    return _AlarmaSenConf_getValorControl(Alarma_getConfiguracion(self));
}

byte  Alarma_setValor(void*_self,int valor){
  struct AlarmaSensor *self = _self;
  if( classOf(self->lazo)==&LazoControlAlSen)
    return LazoControlAlSen_setValor(self->lazo,valor);  
  else  
    return _AlarmaSenConf_setValorControl(Alarma_getConfiguracion(self),valor);
}

int    Alarma_getHisteresis(void*_self){
  struct AlarmaSensor *self = _self;
  if( classOf(self->lazo)==&LazoControlAlSen)
    return LazoControlAlSen_getHisteresis(self->lazo);  
  else  
    return _AlarmaSenConf_getHisteresis(Alarma_getConfiguracion(self));
}

byte   Alarma_setHisteresis(void*_self,int histeresis){
  struct AlarmaSensor *self = _self;
  if( classOf(self->lazo)==&LazoControlAlSen)
    return LazoControlAlSen_setHisteresis(self->lazo,histeresis);  
  else  
    return _AlarmaSenConf_setHisteresis(Alarma_getConfiguracion(self),histeresis);
}
