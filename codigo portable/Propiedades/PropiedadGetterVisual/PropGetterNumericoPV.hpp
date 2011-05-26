#ifndef _PROP_GETTER_NUMERICO_PV_HPP
#define _PROP_GETTER_NUMERICO_PV_HPP

#include <stdtypes.h>
#include "PropGetterVisual.hpp"

#pragma DATA_SEG PROP_GETTER_NUMERICO_DATA                                            
#pragma CODE_SEG PROP_GETTER_NUMERICO_CODE 
#pragma CONST_SEG DEFAULT

struct ArgumentosPropGetterNumericoPV{
  struct ArgumentosPropGetterVisual super;
  uchar (*getCantidadDecimales)(void*);
};

struct PropGetterNumericoPVFactory:public PropGetterVisualFactory{
    PropGetterNumericoPVFactory();
    virtual PropiedadGetter& getPropiedad(void*obj,const struct ArgumentosPropiedadGetter* args,uchar numObjeto)const;
};


class PropGetterNumericoPV:public PropGetterVisual{
  public:
    PropGetterNumericoPV(void*obj,const struct ArgumentosPropGetterNumericoPV* args,uchar numObjeto);
    virtual void print(OutputStream&os);
};


struct ConstructorPropGetterNumericoPV{
    const struct PropGetterVisualFactory * factory;
    struct ArgumentosPropGetterNumericoPV args;
};
 extern const struct PropGetterNumericoPVFactory propGetterNumericoPVFactory;

#pragma DATA_SEG DEFAULT                                            
#pragma CODE_SEG DEFAULT 


#endif