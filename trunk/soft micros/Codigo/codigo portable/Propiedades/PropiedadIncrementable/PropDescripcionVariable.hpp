#ifndef _PROP_DESCRIPCION_VARIABLE_HPP
#define _PROP_DESCRIPCION_VARIABLE_HPP

#include "PropNumLFPF.hpp"
#include "PropiedadGetter.hpp"

struct ArgumentosPropNumDP{
  struct ArgumentosPropNumLFPF super;
  const char * (*getDescripcion)(PropGetterVisual &arg);
};



class PropDescripcionVariable :public PropNumLFPF{
  public:
    PropDescripcionVariable(void*obj,const struct ArgumentosPropNumDP* args,uchar numObjeto);
  protected:
    virtual const char * getDescripcion();

}; 

struct PropDescripcionVariableFactory:public PropGetterVisualFactory{
    virtual PropiedadGetter& getPropiedad(void*obj,const struct ArgumentosPropiedadGetter* args,uchar numObjeto)const;
};

struct ConstructorPropDescripcionVariable{
    const struct PropGetterVisualFactory * factory;
    struct ArgumentosPropNumDP args;
};

extern const struct PropDescripcionVariableFactory propDescripcionVariableFactory;

  

#endif