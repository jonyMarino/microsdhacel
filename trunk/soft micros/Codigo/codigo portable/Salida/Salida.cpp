
#include "Salida.hpp"

Salida::Salida(Salida::confSalida _conf_){

  _confSalida.conectado=_conf_.conectado;
  _confSalida.potencia=_conf_.potencia;
  _confSalida.tipoSalida=_conf_.tipoSalida;   
}

bool Salida::getConectada() {

  return _confSalida.conectado;
}

 void Salida::setConectada(unsigned int conectada) {
  if(_confSalida.conectado && !conectada)
    setPotencia(0); 
   
   _confSalida.conectado=conectada;
  
}

unsigned int Salida::getPotencia() {

  return _confSalida.potencia;
}

 
void Salida::setPotencia(unsigned int _potencia){
  if(!getConectada() || _potencia<0 || _potencia>1000)  
    return; //error
    
  setPotencia(_potencia);
}

void Salida::setTipoSalida(TipoSalida _tipoSalida){
   _confSalida.tipoSalida=_tipoSalida;
}

TipoSalida Salida::getTipoSalida(){
  return _confSalida.tipoSalida;
}