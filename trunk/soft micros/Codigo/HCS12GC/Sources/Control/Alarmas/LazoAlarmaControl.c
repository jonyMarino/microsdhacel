#include "LazoAlarmaControl.h"
#include "ConfLazoCntrAlCntr.h"
#include "ControlPID.h"

#include "LazoAlarmaControl.h"
#include "LazoControl_protected.h"
#include "IPWM.h"
#include "PWMPeriodoEvent.h"


void LazoAlarmaControl_defConstructor(void * _self,va_list * args);
void LazoAlarmaControl_destructor(void * _self);
struct ISalida*LazoAlarmaControl_getSalida(void * _self);

const struct LazoClass LazoAlarmaControl={
  LAZO_CLASS_INITIALIZATION(LazoClass,
                            LazoAlarmaControl,
                            Lazo,
                            LazoAlarmaControl_defConstructor,
                            LazoAlarmaControl_destructor,
                            NULL,
                            NULL,
                            LazoControl_onNuevaMedicion,
                            LazoControl_getSensor,
                            LazoAlarmaControl_getSalida)  
};

static void factoryAdaptSalida(struct LazoAlarmaControl * self, TAdaptador adaptSalida);
static void factoryControl(struct LazoAlarmaControl * self, TControlAlarma control);
static byte AlarmaControl_onControlPeriodoCambio(void*_self);

/**/
void LazoAlarmaControl_constructor(void * _self, 
                             struct ConfLazoCntrAlCntr * configuracion,
                             struct Control * control,
                             struct ISalida * salida
                             
){
  struct LazoAlarmaControl * self = (struct LazoAlarmaControl *)_self;
  struct ISalida * salidaPID;
  
  //newAlloced(&self->control,&CntrProporcionalInvClass,&configuracion->confControl,sensor);
  newAlloced(&self->salidaInvertida,&SalidaInvertida,salida);
  self->configuracion = configuracion;
  self->lazoControl = control;
  factoryControl(self, _ConfLazoCntrAlCntr_getControl(configuracion) );
  factoryAdaptSalida(self, _ConfLazoCntrlAlSen_getAdaptadorSalida(configuracion) );  
  //cuidado! el constructor se llama al final a proposito
  LazoControl_constructor(_self,(struct ValorControl *)&self->control,(struct AdaptacionSalida *)&self->adaptadorSalida); 
  newAlloced(&self->onPeridoControlCambio,&Method,AlarmaControl_onControlPeriodoCambio,_self);
  
  salidaPID=PID_getSal(self->lazoControl);
  //cambiar por lo comentado:
  //if( instanceOf(salidaPID,&PWMPeriodoEvent) && instanceOf(salida,&IPWM) ){    
  if( classOf(salidaPID)==&PWMPeriodoEvent){ 
    
    PWMPeriodoEvent_addPeriodoListener(salidaPID,&self->onPeridoControlCambio);
    AlarmaControl_onControlPeriodoCambio(_self);
  }
}

/**/
void LazoAlarmaControl_defConstructor(void * _self,va_list * args){
  LazoAlarmaControl_constructor(_self,va_arg(*args,struct ConfLazoCntrAlCntr *),va_arg(*args,struct Control *),va_arg(*args,struct ISalida *));  
}

/**/
byte AlarmaControl_onControlPeriodoCambio(void*_self){
  struct LazoAlarmaControl * self = (struct LazoAlarmaControl *)_self;

  struct ISalida * salidaPID=PID_getSal(self->lazoControl);
  //cambiar por lo comentado:
  //if( instanceof(salidaPID,IPWM) && instanceof(salida,IPWM) )

  int periodoPID = getPeriodo((struct IPWM *)salidaPID);
  setPeriodo((struct IPWM *)LazoAlarmaControl_getSalida(self),periodoPID);
  
  return ERR_OK;   
}

/**/
void factoryAdaptSalida(struct LazoAlarmaControl * self, TAdaptador adaptSalida){
  switch(adaptSalida){
    case SALIDA_RETENIDA:
        SalidaInvertida_setInvertida(&self->salidaInvertida,FALSE);
        newAlloced(&self->adaptadorSalida,&SalidaRetenida, _ConfLazoCntrlAlSen_getConfAdaptador(self->configuracion),&self->salidaInvertida);        
        break;
    case SALIDA_DEFECTO_RETENIDA:
        SalidaInvertida_setInvertida(&self->salidaInvertida,TRUE);
        newAlloced(&self->adaptadorSalida,&SalidaRetenidaBajo, _ConfLazoCntrlAlSen_getConfAdaptador(self->configuracion),&self->salidaInvertida);        
        break;
    case SALIDA_DEFECTO_BLOQUEADA:
        SalidaInvertida_setInvertida(&self->salidaInvertida,FALSE);
        newAlloced(&self->adaptadorSalida,&SalidaBloqueadaClass, _ConfLazoCntrlAlSen_getConfAdaptador(self->configuracion),&self->salidaInvertida);        
        break;
    case SALIDA_DEFECTO:         
        SalidaInvertida_setInvertida(&self->salidaInvertida,TRUE);       
        newAlloced(&self->adaptadorSalida,&SalidaBanda, _ConfLazoCntrlAlSen_getConfAdaptador(self->configuracion),&self->salidaInvertida);        
      break;
    case SALIDA_EXCESO:
    default:  //error
        SalidaInvertida_setInvertida(&self->salidaInvertida,FALSE);
        newAlloced(&self->adaptadorSalida,&SalidaBanda, _ConfLazoCntrlAlSen_getConfAdaptador(self->configuracion),&self->salidaInvertida);
      break;      
  }
}

/**/
static void factoryControl(struct LazoAlarmaControl * self, TControlAlarma control){
  struct Sensor * sensor = PID_getSensor(self->lazoControl);
  
  switch(control){             
    case CONTROL_PROPORCIONAL:               
        newAlloced(&self->control,&CntrProporcionalInv, _ConfLazoCntrlAlSen_getConfControl(self->configuracion),sensor);        
      break;
    case CONTROL_RELATIVO: 
        newAlloced(&self->control,&CntrRelativo, _ConfLazoCntrlAlSen_getConfControl(self->configuracion),sensor,self->lazoControl);
      break;
    case CONTROL_BANDA: 
    default:  //error 
        newAlloced(&self->control,&CntrBanda, _ConfLazoCntrlAlSen_getConfControl(self->configuracion),sensor,self->lazoControl);
      break;      
  } 
   
}

/**/
void LazoAlarmaControl_destructor(void * _self){
  struct LazoAlarmaControl * self = (struct LazoAlarmaControl *)_self;
  struct ISalida * salidaPID=PID_getSal(self->lazoControl);
  if( classOf(salidaPID)==&PWMPeriodoEvent)     
    PWMPeriodoEvent_deletePeriodoListener(salidaPID,&self->onPeridoControlCambio);
  
  deleteAlloced(&self->adaptadorSalida);
  deleteAlloced(&self->control);
  Lazo_destructor(_self);  //cambiar : el descriptor de clase debe tener info de cual es la clase siguiente para llamar a su destructor  
}

/**/
TControlAlarma  LazoAlarmaControl_getControl(void*_self){
  struct LazoAlarmaControl * self = (struct LazoAlarmaControl *)_self;
    return _ConfLazoCntrAlCntr_getControl(self->configuracion);
}
/**/
byte LazoAlarmaControl_setControl(void*_self,TControlAlarma control){
  struct LazoAlarmaControl * self = (struct LazoAlarmaControl *)_self;
  byte err = _ConfLazoCntrAlCntr_setControl(self->configuracion,control);
  if(!err){
    deleteAlloced(&self->control);    //thread unsafe con LazoControl_onNuevaMedicion
    factoryControl(self,control);    
  }
  return ERR_OK;
}

/*AdaptadorSalida*/
TAdaptador  LazoAlarmaControl_getAdaptadorSalida(void*_self){
  struct LazoAlarmaControl * self = (struct LazoAlarmaControl *)_self;
  return _ConfLazoCntrlAlSen_getAdaptadorSalida(self->configuracion);
}

byte LazoAlarmaControl_setAdaptadorSalida(void*_self,TAdaptador adaptSalida){
  struct LazoAlarmaControl * self = (struct LazoAlarmaControl *)_self;
  byte err = _ConfLazoCntrlAlSen_setAdaptadorSalida(self->configuracion,adaptSalida);
  if(!err){
    deleteAlloced(&self->adaptadorSalida);    //thread unsafe con LazoControl_onNuevaMedicion
    factoryAdaptSalida(self,adaptSalida);    
  }
  return ERR_OK;
}

/*Valor*/
int   LazoAlarmaControl_getValor(void*_self){
  struct LazoAlarmaControl * self = (struct LazoAlarmaControl *)_self;
  return ValorControl_getValorControlador(&self->control);
}

byte  LazoAlarmaControl_setValor(void*_self,int valor){
  struct LazoAlarmaControl * self = (struct LazoAlarmaControl *)_self;
  return ValorControl_setValorControlador(&self->control,valor);
}

/*Histeresis*/
int   LazoAlarmaControl_getHisteresis(void*_self){
  struct LazoAlarmaControl * self = (struct LazoAlarmaControl *)_self;
  return getHisteresis(&self->adaptadorSalida);
}

byte  LazoAlarmaControl_setHisteresis(void*_self,int histeresis){
  struct LazoAlarmaControl * self = (struct LazoAlarmaControl *)_self;
  return setHisteresis(&self->adaptadorSalida,histeresis);
}

/*Salida*/
struct ISalida*LazoAlarmaControl_getSalida(void * _self){
  struct LazoAlarmaControl * self = (struct LazoAlarmaControl *)_self;
  return DecoradorSalida_getDecorado(&self->salidaInvertida);
}



