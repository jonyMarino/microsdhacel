#ifndef _PROPIEDAD_TEXTUAL_HPP
#define _PROPIEDAD_TEXTUAL_HPP

#include <stdtypes.h>
#include "PropiedadIncrementable.hpp"

#pragma DATA_SEG PROPIEDAD_TEXTUAL_DATA                                            
#pragma CODE_SEG PROPIEDAD_TEXTUAL_CODE 
#pragma CONST_SEG DEFAULT

struct ArgumentosPropiedadTextual{
  struct ArgumentosPropiedadIncrementable super;
  char* (*getTxt)(uchar);
  uchar maximoValorTexto;
};

class PropiedadTextual:public PropiedadIncrementable{
  public:
    PropiedadTextual(void*obj,const struct ArgumentosPropiedadTextual* args);
    virtual void incrementar();
    virtual void decrementar();
    virtual void print(OutputStream&os);
};

struct PropiedadTextualFactory:public PropiedadGetterFactory{
    virtual PropiedadGetter& getPropiedad(void*obj,const struct ArgumentosPropiedadGetter* args)const;
};

struct ConstructorPropiedadTextual{
    const struct PropiedadGetterFactory * factory;
    struct ArgumentosPropiedadTextual args;
};

extern const struct PropiedadTextualFactory propiedadTextualFactory;

#pragma DATA_SEG DEFAULT                                            
#pragma CODE_SEG DEFAULT 


#endif