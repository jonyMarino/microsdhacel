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
    PropNumLVPF(void*obj,const struct ArgumentosPropNumLVPF* args);
    virtual int getLimiteInferior();
    virtual int getLimiteSuperior();
    virtual uchar getCantidadDecimales();
};

struct PropNumLVPFFactory:public PropiedadGetterFactory{
    virtual PropiedadGetter& getPropiedad(void*obj,const struct ArgumentosPropiedadGetter* args)const;
};

struct ConstructorPropNumLVPF{
    const struct PropiedadGetterFactory * factory;
    struct ArgumentosPropNumLVPF args;
};


#pragma DATA_SEG DEFAULT                                            
#pragma CODE_SEG DEFAULT 


#endif