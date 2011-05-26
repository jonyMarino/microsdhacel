#include "CoordinadorLazosAlSenRet.hpp"

void * operator new(size_t size,byte * dir){
  return dir;  
}

void operator delete(void *ptr){
  return;  
}

CoordinadorLazosAlSenRet::CoordinadorLazosAlSenRet( ConfiguracionCoordinadorLazosAlSenRet& _configuracion,
                              ConfiguracionAlarmaSensor& _confAlarma,
                              ConfiguracionValorControl& _confValorControl,
                              AdaptadorSalidaConfiguracion& _confAdaptadorSalida,
                              ConfiguracionRetransmision& _confRetransmision,
                              Sensor& sensor,
                              ISalida& salida):configuracion(_configuracion),confAlarma(_confAlarma),confValorControl(_confValorControl),confAdaptadorSalida(_confAdaptadorSalida),confRetransmision(_confRetransmision) {

  crearLazo(getLazo(),sensor,salida);
}

void CoordinadorLazosAlSenRet::crearLazo(TipoLazo tipo,Sensor& sensor,ISalida& salida){  

  switch(tipo){
    case RETRANSMISION:
      lazo = new((byte*)&poolLazo) Retransmision(sensor,salida,confRetransmision);        
    break;
    case ALARMA:
    default:
      lazo = new((byte*)&poolLazo) AlarmaSensor(confAlarma,confValorControl,sensor,confAdaptadorSalida,salida);  
    break;
  }

}
                             


TipoLazo  CoordinadorLazosAlSenRet::getLazo(){
  return configuracion.getLazo( );
}

void CoordinadorLazosAlSenRet::setLazo(TipoLazo tipo){
  configuracion.setLazo( tipo );
  ISalida& salida = lazo->getSalida();
  struct Sensor& sensor = lazo->getSensor();
  delete lazo;
  crearLazo(tipo,sensor,salida); 
}

TipoAdaptadorSalida  CoordinadorLazosAlSenRet::getAdaptadorSalida(){
  if( getLazo()==ALARMA)
    return ((AlarmaSensor*)lazo)->getAdaptadorSalida();    
  else
    return confAlarma.getAdaptadorSalida();
  
}

void CoordinadorLazosAlSenRet::setAdaptadorSalida(TipoAdaptadorSalida adaptSalida){
  if( getLazo()==ALARMA )
    ((AlarmaSensor*)lazo)->setAdaptadorSalida(adaptSalida);    
  else
    confAlarma.setAdaptadorSalida(adaptSalida);
}