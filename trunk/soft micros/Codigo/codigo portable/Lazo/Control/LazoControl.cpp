#include "LazoControl.hpp"

void LazoControl::LazoControl(ValorControl& _valorControl,AdaptadorSalida& _adaptadorSalida):Lazo(_valorControl.getSensor()),valorControl(&_valorControl),adaptadorSalida(&_adaptadorSalida)
{}

void LazoControl::onNuevoValorSensor(){
  if( getSalida().getConectada() ){
    int valControl = valorControl->getValorControl();
    adaptadorSalida->setPotenciaSalida( valControl );
  }
}

ISalida& LazoControl::getSalida(){
  return adaptadorSalida->getSalida();
}

AdaptadorSalida& LazoControl::getAdaptadorSalida(){
  return *adaptadorSalida;
}