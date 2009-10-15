
#include "Salida.hpp"

 

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

 
