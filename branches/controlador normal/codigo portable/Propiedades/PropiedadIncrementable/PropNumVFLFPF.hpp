#ifndef _PROP_NUM_VF_L_F_P_F_HPP
#define _PROP_NUM_VF_L_F_P_F_HPP

#include <stdtypes.h>
#include "PropNumVFLF.hpp"

#pragma DATA_SEG PROPIEDAD_TEXTUAL_DATA                                            
#pragma CODE_SEG PROPIEDAD_TEXTUAL_CODE 
#pragma CONST_SEG DEFAULT

struct ArgumentosPropNumVFLFPF{
  struct ArgumentosPropNumVFLF super;
  uchar decimales;
};

class PropNumVFLFPF:public PropNumVFLF{
  public:
    PropNumVFLFPF(void*obj,const struct ArgumentosPropNumVFLFPF* args,uchar numObjeto);
    virtual uchar getCantidadDecimales();
};

struct PropNumVFLFPFFactory:public PropGetterVisualVFFactory{
    virtual PropiedadGetterVF& getPropiedad(void*obj,const struct ArgumentosPropiedadGetterVF* args,uchar numObjeto)const;
};

struct ConstructorPropNumVFLFPF{
    const struct PropGetterVisualVFFactory * factory;
    struct ArgumentosPropNumVFLFPF args;
};

extern const struct PropNumVFLFPFFactory propNumVFLFPFFactory;


#pragma DATA_SEG DEFAULT                                            
#pragma CODE_SEG DEFAULT 


#endif