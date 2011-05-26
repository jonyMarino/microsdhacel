#ifndef _PROP_NUM_L_F_HPP
#define _PROP_NUM_L_F_HPP

#include <stdtypes.h>
#include "PropiedadIncrementable.hpp"
#include "PropiedadNumerica.hpp"

#pragma DATA_SEG PROPIEDAD_TEXTUAL_DATA                                            
#pragma CODE_SEG PROPIEDAD_TEXTUAL_CODE 
#pragma CONST_SEG DEFAULT

struct ArgumentosPropNumLF{
  struct ArgumentosPropiedadIncrementable super;
  int limiteInferior;
  int limiteSuperior;
};

class PropNumLF:public PropiedadNumerica{
  public:
    PropNumLF(void*obj,const struct ArgumentosPropNumLF* args,uchar numObjeto);
    virtual int getLimiteInferior();
    virtual int getLimiteSuperior();
    virtual uchar getCantidadDecimales();
};

struct PropNumLFFactory:public PropGetterVisualFactory{
    virtual PropiedadGetter& getPropiedad(void*obj,const struct ArgumentosPropiedadGetter* args,uchar numObjeto)const;
};

struct ConstructorPropNumLF{
    const struct PropGetterVisualFactory * factory;
    struct ArgumentosPropNumLF args;
};

extern const struct PropNumLFFactory propNumLFFactory;


#pragma DATA_SEG DEFAULT                                            
#pragma CODE_SEG DEFAULT 


#endif