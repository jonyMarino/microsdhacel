#include "PropiedadNumericaVF.hpp"
#include "PE/include/PE_Types.h"

PropiedadNumericaVF::PropiedadNumericaVF(void*obj,const struct ArgumentosPropiedadIncrementableVF* args,uchar numObjeto):PropiedadIncrementableVF(obj,args,numObjeto){}


void PropiedadNumericaVF::print(OutputStream&os){
  os.writeAsFloat(getVal(),getCantidadDecimales()); 
}

void PropiedadNumericaVF::incrementar(){
  int valorTmp= getVal();
  int limSup =  getLimiteSuperior();
  
  if(valorTmp<limSup){
    valorTmp++;
	  setValorTmp(valorTmp); 
  }
}

void PropiedadNumericaVF::decrementar(){
  int valorTmp= getVal();
  int limInf =  getLimiteInferior();
  
	if (valorTmp > limInf){
		  valorTmp--;
		  setValorTmp(valorTmp); 
	}
	  
}