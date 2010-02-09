#ifndef _PROP_NUM_L_V_P_F_HPP
#define _PROP_NUM_L_V_P_F_HPP

#include <stdtypes.h>
#include "PropiedadNumerica.hpp"

#pragma DATA_SEG PROPIEDAD_TEXTUAL_DATA                                            
#pragma CODE_SEG PROPIEDAD_TEXTUAL_CODE 
#pragma CONST_SEG DEFAULT

struct ArgumentosPropNumLVPF{
  struct ArgumentosPropiedadIncrementable super;
  int (*getLimiteInferior)(void*);
  int (*getLimiteSuperior)(void*);
  uchar cantidadDecimales;
};

class PropNumLVPF:public PropiedadNumerica{
  public:
    PropNumLVPF(void*obj,const struct ArgumentosPropNumLVPF* args,uchar numObjeto);
    virtual int getLimiteInferior();
    virtual int getLimiteSuperior();
    virtual uchar getCantidadDecimales();
};

struct PropNumLVPFFactory:public PropGetterVisualFactory{
    virtual PropiedadGetter& getPropiedad(void*obj,const struct ArgumentosPropiedadGetter* args,uchar numObjeto)const;
};

struct ConstructorPropNumLVPF{
    const struct PropGetterVisualFactory * factory;
    struct ArgumentosPropNumLVPF args;
};


extern const struct PropNumLVPFFactory propNumLVPFFactory;

#pragma DATA_SEG DEFAULT                                            
#pragma CODE_SEG DEFAULT 


#endif