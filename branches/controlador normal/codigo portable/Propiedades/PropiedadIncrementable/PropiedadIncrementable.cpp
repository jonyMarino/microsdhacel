#include "PropiedadIncrementable.hpp"


PropiedadIncrementable::PropiedadIncrementable(void*obj,const struct ArgumentosPropiedadIncrementable* args,uchar numObjeto):PropGetterVisual(obj,(const struct ArgumentosPropGetterVisual*)args,numObjeto){
  refrescar();
}

void PropiedadIncrementable::guardar(){
  ArgumentosPropiedadIncrementable* args = (ArgumentosPropiedadIncrementable*)getArgumentos();
  (*args->set)(getObjeto(),valorTmp);
  isGuardado = TRUE;
}

int PropiedadIncrementable::getVal(){
  return valorTmp;
}

void PropiedadIncrementable::setValorTmp(int valor){
  valorTmp = valor;  
}

void PropiedadIncrementable::refrescar(){ 
  valorTmp = PropGetterVisual::getVal();
  isGuardado = FALSE;
}

bool PropiedadIncrementable::getIsGuardado(){
  return isGuardado;
}

void PropiedadIncrementable::setIsGuardado(bool val){
   isGuardado = val;
}