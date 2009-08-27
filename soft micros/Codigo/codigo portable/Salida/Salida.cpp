
#include "Salida.hpp"

 void Salida::Salida_setPotencia(unsigned int potencia) {
  if(!getConectada() || potencia<0 || potencia>1000)  
    return; //error
    
  setPotencia(potencia);
  
}

bool Salida::getConectada() {

  return conectado;
}

 void Salida::setConectada(unsigned int conectada) {
  if(conectado && !conectada)
    setPotencia(0); 
   
   conectado=conectada;
  
}

unsigned int Salida::getPotencia() {

  return potencia;
}

 void Salida::setPotencia(unsigned int _potencia) {
  if(getTipoSalida()==SALIDA_PROPORCIONAL) 
    potencia = _potencia; 
  else{
    if(_potencia)
      potencia = 1000;
    else
      potencia = 0;
  }  
}

