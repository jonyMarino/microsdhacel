#include "LazoControl.hpp"

LazoControl::LazoControl(ValorControl& _valorControl,AdaptadorSalida& _adaptadorSalida):Lazo(_valorControl.getSensor()),valorControl(&_valorControl),adaptadorSalida(&_adaptadorSalida)
{}

LazoControl::LazoControl(Sensor&sensor):Lazo(sensor),valorControl(NULL),adaptadorSalida(NULL){
}

void LazoControl::onNuevoValorSensor(){
  ISalida&salida= getSalida();
  if( salida.getConectada() ){
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


ValorControl& LazoControl::getValorControl(){
 return *valorControl; 
}