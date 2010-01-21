#ifndef _PROP_NUM_L_F_P_F_HPP
#define _PROP_NUM_L_F_P_F_HPP

#include <stdtypes.h>
#include "PropNumLF.hpp"

#pragma DATA_SEG PROPIEDAD_TEXTUAL_DATA                                            
#pragma CODE_SEG PROPIEDAD_TEXTUAL_CODE 
#pragma CONST_SEG DEFAULT

struct ArgumentosPropNumLFPF{
  struct ArgumentosPropNumLF super;
  uchar decimales;
};

class PropNumLFPF:public PropNumLF{
  public:
    PropNumLFPF(void*obj,const struct ArgumentosPropNumLFPF* args);
    virtual uchar getCantidadDecimales();
};

struct PropNumLFPFFactory:public PropiedadGetterFactory{
    virtual PropiedadGetter& getPropiedad(void*obj,const struct ArgumentosPropiedadGetter* args)const;
};

struct ConstructorPropNumLFPF{
    const struct PropiedadGetterFactory * factory;
    struct ArgumentosPropNumLFPF args;
};

extern const struct PropNumLFPFFactory propNumLFPFFactory;


#pragma DATA_SEG DEFAULT                                            
#pragma CODE_SEG DEFAULT 


#endif