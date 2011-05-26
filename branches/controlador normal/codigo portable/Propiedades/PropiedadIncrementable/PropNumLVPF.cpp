#include "PropNumLVPF.hpp"
//#include "PE/include/PE_Types.h"

const struct PropNumLVPFFactory propNumLVPFFactory;

PropNumLVPF::PropNumLVPF(void*obj,const struct ArgumentosPropNumLVPF* args,uchar numObjeto):PropiedadNumerica(obj,(const struct ArgumentosPropiedadIncrementable*)args,numObjeto){}

int PropNumLVPF::getLimiteInferior(){
  struct ArgumentosPropNumLVPF* arg= (struct ArgumentosPropNumLVPF*)getArgumentos();
  return (*arg->getLimiteInferior)(getObjeto());
}

int PropNumLVPF::getLimiteSuperior(){
  struct ArgumentosPropNumLVPF* arg= (struct ArgumentosPropNumLVPF*)getArgumentos();
  return (*arg->getLimiteSuperior)(getObjeto());

}

uchar PropNumLVPF::getCantidadDecimales(){
  struct ArgumentosPropNumLVPF* arg= (struct ArgumentosPropNumLVPF*)getArgumentos();
  return arg->cantidadDecimales;
}

PropiedadGetter& PropNumLVPFFactory::getPropiedad(void*obj,const struct ArgumentosPropiedadGetter* args,uchar numObjeto)const{
  return *new PropNumLVPF(obj,(const struct ArgumentosPropNumLVPF*)args,numObjeto);
} 
