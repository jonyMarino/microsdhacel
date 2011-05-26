#include "Retransmision.hpp"


#pragma DATA_SEG Retransmision_DATA                                            
#pragma CODE_SEG Retransmision_CODE 
#pragma CONST_SEG DEFAULT


Retransmision::Retransmision( Sensor&sensor,IPWM&_pwm,ConfiguracionRetransmision& _configuracion):Lazo(sensor),pwm(_pwm),configuracion(_configuracion){
  pwm.setPeriodo(PWM_Anl);
}

ISalida& Retransmision::getSalida(){
  return pwm;           
}

void Retransmision::onNuevoValorSensor(){
  int retLow = configuracion.getLimiteInferior();
  int retHi = configuracion.getLimiteSuperior();
  int retVal = getSensor().getVal();
  int duty; 
   
  long dutyTmp=((long)(retVal - retLow))*1000/( retHi- retLow ); 

   if(dutyTmp>1000)
    duty=1000;
   else if(dutyTmp<0)
    duty=0;
   else
    duty=(int)dutyTmp; 
   
   pwm.setPotencia(duty);
}

int Retransmision::getLimiteInferior(){
  return configuracion.getLimiteInferior();
}

int Retransmision::getLimiteSuperior(){
   return configuracion.getLimiteSuperior();
}

void Retransmision::setLimiteInferior(int val){
    configuracion.setLimiteInferior(val);
}

void Retransmision::setLimiteSuperior(int val){
    configuracion.setLimiteSuperior(val);
}