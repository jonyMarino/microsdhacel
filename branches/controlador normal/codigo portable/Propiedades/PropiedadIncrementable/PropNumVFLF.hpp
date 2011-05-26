#ifndef _PROP_NUM_VF_L_F_HPP
#define _PROP_NUM_VF_L_F_HPP

#include <stdtypes.h>
#include "PropiedadIncrementableVF.hpp"
#include "PropiedadNumericaVF.hpp"

#pragma DATA_SEG PROPIEDAD_TEXTUAL_DATA                                            
#pragma CODE_SEG PROPIEDAD_TEXTUAL_CODE 
#pragma CONST_SEG DEFAULT

struct ArgumentosPropNumVFLF{
  struct ArgumentosPropiedadIncrementableVF super;
  int limiteInferior;
  int limiteSuperior;
};

class PropNumVFLF:public PropiedadNumericaVF{
  public:
    PropNumVFLF(void*obj,const struct ArgumentosPropNumVFLF* args,uchar numObjeto);
    virtual int getLimiteInferior();
    virtual int getLimiteSuperior();
    virtual uchar getCantidadDecimales();
};

struct PropNumVFLFFactory:public PropGetterVisualVFFactory{
    virtual PropiedadGetterVF& getPropiedad(void*obj,const struct ArgumentosPropiedadGetterVF* args,uchar numObjeto)const;
};

struct ConstructorPropNumVFLF{
    const struct PropGetterVisualVFFactory * factory;
    struct ArgumentosPropNumVFLF args;
};

extern const struct PropNumVFLFFactory propNumVFLFFactory;


#pragma DATA_SEG DEFAULT                                            
#pragma CODE_SEG DEFAULT 


#endif