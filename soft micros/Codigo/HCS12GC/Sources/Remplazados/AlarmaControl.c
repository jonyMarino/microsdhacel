#include "AlarmaControl.h"
#include "SalidaBanda.h"
#include "ControlPID.h"


void AlarmaControl_defConstructor(void * _self,va_list * args);


const struct Class AlarmaControlClass={
  &Class,
  "",
  &Object, 
  sizeof(struct AlarmaControl),
  AlarmaControl_defConstructor,
  NULL,
  NULL, // differ
  NULL // puto
};

static void crearLazo(struct AlarmaControl *self,TTipoAlarma tipoAlarma,struct ISalida * salida);


void AlarmaControl_constructor(void * _self, 
                              struct AlarmaCntrConf * configuracion,
                              struct Control * control,
                              struct ISalida * salida
                              
) {
  struct AlarmaControl * self = _self;
  
  self->control = control;
  Alarma_constructor(self,(struct AlarmaConf*)configuracion);
 
  crearLazo(self,_AlarmaConf_getLazo(configuracion),salida);
}

void AlarmaControl_defConstructor(void * _self,va_list * args){
  AlarmaControl_constructor(_self,va_arg(*args,void*),va_arg(*args,void*),va_arg(*args,void*));  
}

void crearLazo(struct AlarmaControl *self,TTipoAlarma tipoAlarma,struct ISalida * salida){  

  switch(tipoAlarma){
    case ALARMA_RETRANSMISION:
      newAlloced(&self->lazo,&RetransmisionPWMClass,_AlarmaConf_getRetConf( Alarma_getConfiguracion(self) ),salida,PID_getSensor(self->control));        
    break;
    case ALARMA_CONTROL:
    default:
      newAlloced(&self->lazo,&LazoAlarmaControl,_AlarmaCntrConf_getLazoCntrAlConf( Alarma_getConfiguracion(self) ),self->control,salida);  
    break;
  }

}
                             


TTipoAlarma  AlarmaControl_getTipo(void* _self){
  struct AlarmaControl *self = _self;
  return _AlarmaConf_getLazo( Alarma_getConfiguracion(self) );
}

byte AlarmaControl_setTipo(void*_self,TTipoAlarma tipoAlarma){
  struct AlarmaControl *self = _self;
  byte err = _AlarmaConf_setLazo( Alarma_getConfiguracion(self) ,tipoAlarma);
  if(!err){
    struct ISalida * salida = getSalida(&self->lazo);
 //   struct Sensor * sensor = getSensor(self->lazo);
    deleteAlloced(&self->lazo);
    crearLazo(self,tipoAlarma,salida);
  }
  return err;
}

/**/
TControlAlarma  AlarmaControl_getControl(void*_self){
  struct AlarmaControl *self = _self;
  if( classOf(&self->lazo)==&LazoAlarmaControl)
    return LazoAlarmaControl_getControl(&self->lazo);    
  else
    return _AlarmaCntrConf_getControl( Alarma_getConfiguracion(self) );
  
}
/**/
byte AlarmaControl_setControl(void*_self,TAdaptador adaptSalida){
  struct AlarmaControl *self = _self;
  if( classOf(&self->lazo)==&LazoAlarmaControl)
    return LazoAlarmaControl_setControl(&self->lazo,adaptSalida);    
  else
    return _AlarmaCntrConf_setControl( Alarma_getConfiguracion(self) ,adaptSalida);
}

/**/
TAdaptador  AlarmaControl_getAdaptadorSalida(void*_self){
  struct AlarmaControl *self = _self;
  if( classOf(&self->lazo)==&LazoAlarmaControl)
    return LazoAlarmaControl_getAdaptadorSalida(&self->lazo);    
  else
    return _AlarmaCntrConf_getAdaptadorSalida( Alarma_getConfiguracion(self) );
  
}
/**/
byte AlarmaControl_setAdaptadorSalida(void*_self,TAdaptador adaptSalida){
  struct AlarmaControl *self = _self;
  if( classOf(&self->lazo)==&LazoAlarmaControl)
    return LazoAlarmaControl_setAdaptadorSalida(&self->lazo,adaptSalida);    
  else
    return _AlarmaCntrConf_setAdaptadorSalida( Alarma_getConfiguracion(self) ,adaptSalida);
}

/**/
int AlarmaControl_adaptSalidaLimSup(void * _self){
  return  ADAPTADOR_MAX_VALOR;
}
/**/
int   AlarmaControl_getValor(void*_self){
  struct AlarmaControl *self = _self;
  if( classOf(&self->lazo)==&LazoAlarmaControl)
    return LazoAlarmaControl_getValor(&self->lazo);  
  else  
    return _AlarmaCntrConf_getValorControl(Alarma_getConfiguracion(self));
}

byte  AlarmaControl_setValor(void*_self,int valor){
  struct AlarmaControl *self = _self;
  if( classOf(&self->lazo)==&LazoAlarmaControl)
    return LazoAlarmaControl_setValor(&self->lazo,valor);  
  else  
    return _AlarmaCntrConf_setValorControl(Alarma_getConfiguracion(self),valor);
}

/**/
int    AlarmaControl_getHisteresis(void*_self){
  struct AlarmaControl *self = _self;
  if( classOf(&self->lazo)==&LazoAlarmaControl)
    return LazoAlarmaControl_getHisteresis(&self->lazo);  
  else  
    return _AlarmaCntrConf_getHisteresis(Alarma_getConfiguracion(self));
}

byte   AlarmaControl_setHisteresis(void*_self,int histeresis){
  struct AlarmaControl *self = _self;
  if( classOf(&self->lazo)==&LazoAlarmaControl)
    return LazoAlarmaControl_setHisteresis(&self->lazo,histeresis);  
  else  
    return _AlarmaCntrConf_setHisteresis(Alarma_getConfiguracion(self),histeresis);
}

/**/
TipoSalida    AlarmaControl_getTipoSalida(void*_self){
  struct AlarmaControl *self = _self;
  if( classOf(&self->lazo)==&LazoAlarmaControl)
    return LazoControl_getTipoSalida(&self->lazo);  
  else  
    return _AlarmaCntrConf_getTipoSalida(Alarma_getConfiguracion(self));
}

byte   AlarmaControl_setTipoSalida(void*_self,TipoSalida tipoSalida){
  struct AlarmaControl *self = _self;
  if( classOf(&self->lazo)==&LazoAlarmaControl)
    return LazoControl_setTipoSalida(&self->lazo,tipoSalida);  
  else  
    return _AlarmaCntrConf_setTipoSalida(Alarma_getConfiguracion(self),tipoSalida);
}

/**/
struct Sensor * AlarmaControl_getSensor(void * _self){
  struct AlarmaControl *self = _self;
  return getSensor(&self->lazo);
}




