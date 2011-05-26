#include "CoordinadorLazosAlCntrRet.hpp"
#include "CoordinadorControladorSintonizador.hpp"

CoordinadorLazosAlCntrRet::RetransmisionOptMem::RetransmisionOptMem(Sensor&sensor,IPWM&pwm,ConfiguracionRetransmision& configuracion):Retransmision(sensor,pwm,configuracion){
}

void * CoordinadorLazosAlCntrRet::RetransmisionOptMem::operator new(size_t size,byte * dir){
  return dir;  
}

void CoordinadorLazosAlCntrRet::RetransmisionOptMem::operator delete(void *ptr){
  return;  
}

CoordinadorLazosAlCntrRet::AlarmaOptMem::AlarmaOptMem(ConfiguracionAlarmaControl& configuracion,ConfiguracionValorControl& confValorControl,AdaptadorSalidaConfiguracion& confAdaptadorSalida,ControlPID& control,ISalida&salida):AlarmaControl(configuracion,confValorControl,confAdaptadorSalida,control,salida){
}

void * CoordinadorLazosAlCntrRet::AlarmaOptMem::operator new(size_t size,byte * dir){
  return dir;  
}

void CoordinadorLazosAlCntrRet::AlarmaOptMem::operator delete(void *ptr){
  return;  
}

CoordinadorLazosAlCntrRet::CoordinadorLazosAlCntrRet( ConfiguracionCoordinadorLazosAlCntrRet& _configuracion,
                              ConfiguracionAlarmaControl& _confAlarma,
                              ConfiguracionValorControl& _confValorControl,
                              AdaptadorSalidaConfiguracion& _confAdaptadorSalida,
                              ConfiguracionRetransmision& _confRetransmision,
                              ControlPID& _control,
                              //CoordinadorControladorSintonizador& _control,
                              IPWM&_pwm):configuracion(_configuracion),confAlarma(_confAlarma),confValorControl(_confValorControl),confAdaptadorSalida(_confAdaptadorSalida),confRetransmision(_confRetransmision), control(_control),pwm(_pwm){

  crearLazo(getLazo(),_pwm);
}

void CoordinadorLazosAlCntrRet::crearLazo(TipoLazo tipo,IPWM&pwm_){  

  switch(tipo){
    case RETRANSMISION:
      lazo = new ((byte*)&poolLazo) RetransmisionOptMem(control.getSensor(),pwm_,confRetransmision);        
    break;
    case ALARMA:
    default:
      lazo = new((byte*)&poolLazo) AlarmaOptMem(confAlarma,confValorControl,confAdaptadorSalida,control,pwm_);  
    break;
  }

}
                             


TipoLazo  CoordinadorLazosAlCntrRet::getLazo(){
  return configuracion.getLazo( );
}

void CoordinadorLazosAlCntrRet::setLazo(TipoLazo tipo){
  configuracion.setLazo( tipo );
  
  IPWM&pwm = (IPWM&)lazo->getSalida();
  
  delete lazo;
  crearLazo(tipo,pwm); 
}

Retransmision& CoordinadorLazosAlCntrRet::getRetransmision(){
  //si no se encuentra en modo RETRANSMISION devuelve NULL
 // if(getLazo()!=RETRANSMISION)
   // return NULL;
  return *(Retransmision *)lazo;
}
AlarmaControl& CoordinadorLazosAlCntrRet::getAlarmaControl(){
  //si no se encuentra en modo ALARMA devuelve NULL
  //if(getLazo()!=ALARMA)
    //return NULL;
  return *(AlarmaControl *)lazo;
}

