#include "DecoradorSalida.hpp"


DecoradorSalida::DecoradorSalida(ISalida& aDecorar):decorado(aDecorar){

}
 
unsigned int DecoradorSalida::getPotencia(){
  return decorado.getPotencia();
}

void DecoradorSalida::setPotencia(unsigned int potencia){
  decorado.setPotencia(potencia);
}

TipoSalida DecoradorSalida::getTipoSalida(){
  return decorado.getTipoSalida();
}

void DecoradorSalida::setTipoSalida(TipoSalida tipoSalida){
  decorado.setTipoSalida(tipoSalida);
}

bool DecoradorSalida::getConectada(){
  return decorado.getConectada();
}

void DecoradorSalida::setConectada(bool conectada){
    decorado.setConectada(conectada);
}

