#include "PropiedadHora.hpp"
#include "PE/include/PE_Types.h"
#include "OOC/lang/CharPointer.hpp"

PropiedadHora::PropiedadHora(void*obj,const struct ArgumentosPropiedadIncrementable* args,uchar numObjeto):PropiedadIncrementable(obj,args,numObjeto){}


void PropiedadHora::print(OutputStream&os){
  os.writeAsFloat(getVal(),2);  
}

void PropiedadHora::incrementar(){
  int valorTmp= getVal();
  
  if(valorTmp<2359){    
    valorTmp++;
    if (((valorTmp%100)%60)==0 && valorTmp!=0) valorTmp +=40;
  }else
    valorTmp = 0;
	setValorTmp(valorTmp);  
}

void PropiedadHora::decrementar(){
  int valorTmp= getVal();
	if (valorTmp > 0){
	  
		if (valorTmp%100==0) valorTmp-=40;
		  valorTmp--; 
	}else
	  valorTmp = 2359;
	setValorTmp(valorTmp);  
}

void PropiedadHora::setValor(int valor){
  if( (((uint)valor)%100 < 59) && (((uint)valor)/100<24))
    setValorTmp(valor);
}

PropiedadGetter& PropiedadHoraFactory::getPropiedad(void*obj,const struct ArgumentosPropiedadGetter* args,uchar numObjeto)const{
  return *new PropiedadHora(obj,(const struct ArgumentosPropiedadIncrementable*)args,numObjeto);
} 
