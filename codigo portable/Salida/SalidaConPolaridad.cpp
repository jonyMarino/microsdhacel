#include "SalidaConPolaridad.hpp"

SalidaConPolaridad::SalidaConPolaridad(ISalida& aDecorar):DecoradorSalida(aDecorar),polaridad(TRUE){}

bool SalidaConPolaridad::getPolaridad(){
  return polaridad;   
}

void SalidaConPolaridad::setPolaridad(bool polaridad){
  this->polaridad = polaridad; 
}


void SalidaConPolaridad::setPotencia(unsigned int potencia){
  if(!polaridad)
    potencia = 1000 - potencia;
  DecoradorSalida::setPotencia(potencia);
}
