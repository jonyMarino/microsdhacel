#ifndef _PROP_GETTER_NUMERICO_HPP
#define _PROP_GETTER_NUMERICO_HPP

#include <stdtypes.h>
#include "PropGetterVisual.hpp"

#pragma DATA_SEG PROP_GETTER_NUMERICO_DATA                                            
#pragma CODE_SEG PROP_GETTER_NUMERICO_CODE 
#pragma CONST_SEG DEFAULT

struct ArgumentosPropGetterNumerico{
  struct ArgumentosPropGetterVisual super;
  uchar puntoDecimal;
};

class PropGetterNumerico:public PropGetterVisual{
  public:
    PropGetterNumerico(void*obj,const struct ArgumentosPropGetterNumerico* args,uchar numObjeto);
    virtual void print(OutputStream&os);
};

struct PropGetterNumericoFactory:public PropGetterVisualFactory{
    PropGetterNumericoFactory();
    virtual PropiedadGetter& getPropiedad(void*obj,const struct ArgumentosPropiedadGetter* args,uchar numObjeto)const;
};

struct ConstructorPropGetterNumerico{
    const struct PropGetterVisualFactory * factory;
    struct ArgumentosPropGetterNumerico args;
};
 extern const struct PropGetterNumericoFactory propGetterNumericoFactory;

#pragma DATA_SEG DEFAULT                                            
#pragma CODE_SEG DEFAULT 


#endif