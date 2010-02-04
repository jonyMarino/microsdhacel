
#include "Salida.hpp"

Salida::Salida(){

  conectado=FALSE;
  potencia=0;
  tipoSalida=SALIDA_ONOFF;   
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

 
void Salida::setPotencia(unsigned int _potencia){
  if(!getConectada() || _potencia<0 || _potencia>1000)  
    return; //error
    
  setPotencia(_potencia);
}

void Salida::setTipoSalida(TipoSalida _tipoSalida){
   tipoSalida = _tipoSalida;
}

TipoSalida Salida::getTipoSalida(){
  return tipoSalida;
}