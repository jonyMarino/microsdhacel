#ifndef _PROPIEDAD_NUMERICA_HPP
#define _PROPIEDAD_NUMERICA_HPP

#include <stdtypes.h>
#include "PropiedadIncrementable.hpp"

#pragma DATA_SEG PROPIEDAD_TEXTUAL_DATA                                            
#pragma CODE_SEG PROPIEDAD_TEXTUAL_CODE 
#pragma CONST_SEG DEFAULT

class PropiedadNumerica:public PropiedadIncrementable{
  public:
    PropiedadNumerica(void*obj,const struct ArgumentosPropiedadIncrementable* args,uchar numObjeto);
    virtual void incrementar();
    virtual void decrementar();
    virtual void setValor(int valor);
    virtual void print(OutputStream&os);
    virtual int getLimiteInferior()=0;
    virtual int getLimiteSuperior()=0;
    virtual uchar getCantidadDecimales()=0;
};

#pragma DATA_SEG DEFAULT                                            
#pragma CODE_SEG DEFAULT 


#endif