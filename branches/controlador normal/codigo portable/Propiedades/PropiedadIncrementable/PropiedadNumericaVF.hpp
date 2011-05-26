#ifndef _PROPIEDAD_NUMERICA_VF_HPP
#define _PROPIEDAD_NUMERICA_VF_HPP

#include <stdtypes.h>
#include "PropiedadIncrementableVF.hpp"

#pragma DATA_SEG PROPIEDAD_TEXTUAL_DATA                                            
#pragma CODE_SEG PROPIEDAD_TEXTUAL_CODE 
#pragma CONST_SEG DEFAULT

class PropiedadNumericaVF:public PropiedadIncrementableVF{
  public:
    PropiedadNumericaVF(void*obj,const struct ArgumentosPropiedadIncrementableVF* args,uchar numObjeto);
    virtual void incrementar();
    virtual void decrementar();
    virtual void print(OutputStream&os);
    virtual int getLimiteInferior()=0;
    virtual int getLimiteSuperior()=0;
    virtual uchar getCantidadDecimales()=0;
};

#pragma DATA_SEG DEFAULT                                            
#pragma CODE_SEG DEFAULT 


#endif