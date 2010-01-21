#include "PropNumLVPF.hpp"
//#include "PE/include/PE_Types.h"

PropNumLVPF::PropNumLVPF(void*obj,const struct ArgumentosPropNumLVPF* args):PropiedadNumerica(obj,(const struct ArgumentosPropiedadIncrementable*)args){}

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

PropiedadGetter& PropNumLVPFFactory::getPropiedad(void*obj,const struct ArgumentosPropiedadGetter* args)const{
  return *new PropNumLVPF(obj,(const struct ArgumentosPropNumLVPF*)args);
} 
