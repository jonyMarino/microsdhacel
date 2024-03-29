#ifndef _PROPIEDAD_HORA_HPP
#define _PROPIEDAD_HORA_HPP

#include <stdtypes.h>
#include "PropiedadIncrementable.hpp"

#pragma DATA_SEG PROPIEDAD_HORA_DATA                                            
#pragma CODE_SEG PROPIEDAD_HORA_CODE 
#pragma CONST_SEG DEFAULT

class PropiedadHora:public PropiedadIncrementable{
  public:
    PropiedadHora(void*obj,const struct ArgumentosPropiedadIncrementable* args,uchar numObjeto);
    virtual void incrementar();
    virtual void decrementar();
    virtual void setValor(int valor);
    virtual void print(OutputStream&os);
};

struct PropiedadHoraFactory:public PropGetterVisualFactory{
    virtual PropiedadGetter& getPropiedad(void*obj,const struct ArgumentosPropiedadGetter* args,uchar numObjeto)const;
};

struct ConstructorPropiedadHora{
    const struct PropGetterVisualFactory * factory;
    struct ArgumentosPropiedadIncrementable args;
};


#pragma DATA_SEG DEFAULT                                            
#pragma CODE_SEG DEFAULT 


#endif