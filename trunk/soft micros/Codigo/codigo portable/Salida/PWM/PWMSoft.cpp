
#include "PWMSoft.hpp"

void PWMSoft::setPotencia(unsigned int potencia){
  if(setTipoSalida(tipoSalida)==SALIDA_ONOFF){		    
    if(potencia==0)
      clrReg8Bits(*salida, mascara);             
    else
      setReg8Bits(*salida, mascara);            
  }
  Salida_setPotencia(potencia);
}

unsigned char PWMSoft::setPeriodo(int period){
}

void PWMSoft::setTipoSalida(TipoSalida tipoSalida){
}

TipoSalida PWMSoft::getTipoSalida(){
}