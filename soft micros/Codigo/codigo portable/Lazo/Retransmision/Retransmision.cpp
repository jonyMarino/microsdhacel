#include "Retransmision.hpp"


#pragma DATA_SEG Retransmision_DATA                                            
#pragma CODE_SEG Retransmision_CODE 
#pragma CONST_SEG DEFAULT


Retransmision::Retransmision( Sensor&sensor,ISalida&_salida,ConfiguracionRetransmision& _configuracion):Lazo(sensor),salida(_salida),configuracion(_configuracion){
}

ISalida& Retransmision::getSalida(){
  return salida;           
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
   
   salida.setPotencia(duty);
}
