#include "CoordinadorLazosAlCntrRet.hpp"

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
                              IPWM&_pwm):configuracion(_configuracion),confAlarma(_confAlarma),confValorControl(_confValorControl),confAdaptadorSalida(_confAdaptadorSalida),confRetransmision(_confRetransmision), control(_control){

  crearLazo(getLazo(),_pwm);
}

void CoordinadorLazosAlCntrRet::crearLazo(TipoLazo tipo,IPWM&pwm_){  

  switch(tipo){
    case RETRANSMISION:
      lazo = new((byte*)&poolLazo) RetransmisionOptMem(control.getSensor(),pwm_,confRetransmision);        
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

TipoAdaptadorSalida  CoordinadorLazosAlCntrRet::getAdaptadorSalida(){
  if( getLazo()==ALARMA)
    return ((AlarmaControl*)lazo)->getAdaptadorSalida();    
  else
    return confAlarma.getAdaptadorSalida();
  
}

void CoordinadorLazosAlCntrRet::setAdaptadorSalida(TipoAdaptadorSalida adaptSalida){
  if( getLazo()==ALARMA )
    ((AlarmaControl*)lazo)->setAdaptadorSalida(adaptSalida);    
  else
    confAlarma.setAdaptadorSalida(adaptSalida);
}

TipoControl  CoordinadorLazosAlCntrRet::getTipoControl(){
  if( getLazo()==ALARMA)
    return ((AlarmaControl*)lazo)->getTipoControl();    
  else
    return confAlarma.getTipoControl();
}

void CoordinadorLazosAlCntrRet::setTipoControl(TipoControl tipoControl){
  if( getLazo()==ALARMA )
    ((AlarmaControl*)lazo)->setTipoControl(tipoControl);    
  else
    confAlarma.setTipoControl(tipoControl);
}
    
    
    