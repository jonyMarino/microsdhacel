#include "PropiedadIncrementableVF.hpp"


PropiedadIncrementableVF::PropiedadIncrementableVF(void*obj,const struct ArgumentosPropiedadIncrementableVF* args,uchar numObjeto):PropGetterVisualVF(obj,(const struct ArgumentosPropGetterVisualVF*)args,numObjeto),nroTmp(numObjeto){
  refrescar();
}

void PropiedadIncrementableVF::guardar(){
  ArgumentosPropiedadIncrementableVF* args = (ArgumentosPropiedadIncrementableVF*)getArgumentos();
  (*args->set)(getObjeto(),nroTmp,valorTmp);
  isGuardado = TRUE;
}

int PropiedadIncrementableVF::getVal(){
  return valorTmp;
}



void PropiedadIncrementableVF::setValorTmp(int valor){
  valorTmp = valor;  
}

void PropiedadIncrementableVF::refrescar(){ 
  valorTmp = PropGetterVisualVF::getVal();
  
  isGuardado = FALSE;
}

bool PropiedadIncrementableVF::getIsGuardado(){
  return isGuardado;
}

void PropiedadIncrementableVF::setIsGuardado(bool val){
   isGuardado = val;
}