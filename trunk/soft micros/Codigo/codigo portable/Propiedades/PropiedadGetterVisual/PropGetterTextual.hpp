#ifndef _PROP_GETTER_TEXTUAL_HPP
#define _PROP_GETTER_TEXTUAL_HPP

#include <stdtypes.h>
#include "PropGetterVisual.hpp"

#pragma DATA_SEG PROP_GETTER_TEXTUAL_DATA                                            
#pragma CODE_SEG PROP_GETTER_TEXTUAL_CODE 
#pragma CONST_SEG DEFAULT

struct ArgumentosPropGetterTextual{
  struct ArgumentosPropGetterVisual super;
  char* (*getTxt)(uchar);
};

class PropGetterTextual:public PropGetterVisual{
  public:
    PropGetterTextual(void*obj,const struct ArgumentosPropGetterTextual* args,uchar numObjeto);
    virtual void print(OutputStream&os);
};

struct PropGetterTextualFactory:public PropGetterVisualFactory{
    virtual PropiedadGetter& getPropiedad(void*obj,const struct ArgumentosPropiedadGetter* args,uchar numObjeto)const;
};

struct ConstructorPropGetterTextual{
    const struct PropGetterVisualFactory * factory;
    struct ArgumentosPropGetterTextual args;
};


#pragma DATA_SEG DEFAULT                                            
#pragma CODE_SEG DEFAULT 


#endif