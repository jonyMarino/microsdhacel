#ifndef _PROP_NUM_L_F_P_V_HPP
#define _PROP_NUM_L_F_P_V_HPP

#include <stdtypes.h>
#include "PropNumLF.hpp"

#pragma DATA_SEG PROPIEDAD_TEXTUAL_DATA                                            
#pragma CODE_SEG PROPIEDAD_TEXTUAL_CODE 
#pragma CONST_SEG DEFAULT

struct ArgumentosPropNumLFPV{
  struct ArgumentosPropNumLF super;
  uchar (*getCantidadDecimales)(void*);
};

class PropNumLFPV:public PropNumLF{
  public:
    PropNumLFPV(void*obj,const struct ArgumentosPropNumLFPV* args);
    virtual uchar getCantidadDecimales();
};

struct PropNumLFPVFactory:public PropiedadGetterFactory{
    virtual PropiedadGetter& getPropiedad(void*obj,const struct ArgumentosPropiedadGetter* args)const;
};

struct ConstructorPropNumLFPV{
    const struct PropiedadGetterFactory * factory;
    struct ArgumentosPropNumLFPV args;
};

extern const struct PropNumLFPVFactory propNumLFPVFactory;


#pragma DATA_SEG DEFAULT                                            
#pragma CODE_SEG DEFAULT 


#endif