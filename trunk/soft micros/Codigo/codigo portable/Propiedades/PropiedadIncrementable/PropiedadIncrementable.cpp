#include "PropiedadIncrementable.hpp"


PropiedadIncrementable::PropiedadIncrementable(void*obj,const struct ArgumentosPropiedadIncrementable* args,uchar numObjeto):PropGetterVisual(obj,(const struct ArgumentosPropGetterVisual*)args,numObjeto){
  valorTmp = PropGetterVisual::getVal();
}

void PropiedadIncrementable::guardar(){
  ArgumentosPropiedadIncrementable* args = (ArgumentosPropiedadIncrementable*)getArgumentos();
  (*args->set)(getObjeto(),valorTmp);
}

int PropiedadIncrementable::getVal(){
  return valorTmp;
}

void PropiedadIncrementable::setValorTmp(int valor){
  valorTmp = valor;  
}

