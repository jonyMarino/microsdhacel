#include "PropNumLF.hpp"
//#include "PE/include/PE_Types.h"

const struct PropNumLFFactory propNumLFFactory;

PropNumLF::PropNumLF(void*obj,const struct ArgumentosPropNumLF* args,uchar numObjeto):PropiedadNumerica(obj,(const struct ArgumentosPropiedadIncrementable*)args,numObjeto){}

int PropNumLF::getLimiteInferior(){
  struct ArgumentosPropNumLF* arg= (struct ArgumentosPropNumLF*)getArgumentos();
  return arg->limiteInferior;
}

int PropNumLF::getLimiteSuperior(){
  struct ArgumentosPropNumLF* arg= (struct ArgumentosPropNumLF*)getArgumentos();
  return arg->limiteSuperior;
}

uchar PropNumLF::getCantidadDecimales(){
  return 0;
}

PropiedadGetter& PropNumLFFactory::getPropiedad(void*obj,const struct ArgumentosPropiedadGetter* args,uchar numObjeto)const{
  return *new PropNumLF(obj,(const struct ArgumentosPropNumLF*)args,numObjeto);
} 
