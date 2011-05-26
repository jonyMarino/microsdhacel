#ifndef _PROP_DESCRIPCION_VARIABLE_PV_HPP
#define _PROP_DESCRIPCION_VARIABLE_PV_HPP

#include "PropNumLFPV.hpp"
#include "PropiedadGetter.hpp"

struct ArgumentosPropNumDPPV{
  struct ArgumentosPropNumLFPV super;
  const char * (*getDescripcion)(PropGetterVisual &arg);
};



class PropDescripcionVariablePV :public PropNumLFPV{
  public:
    PropDescripcionVariablePV(void*obj,const struct ArgumentosPropNumDPPV* args,uchar numObjeto);
  protected:
    virtual const char * getDescripcion();

}; 

struct PropDescripcionVariablePVFactory:public PropGetterVisualFactory{
    virtual PropiedadGetter& getPropiedad(void*obj,const struct ArgumentosPropiedadGetter* args,uchar numObjeto)const;
};

struct ConstructorPropDescripcionVariablePV{
    const struct PropGetterVisualFactory * factory;
    struct ArgumentosPropNumDPPV args;
};

extern const struct PropDescripcionVariablePVFactory propDescripcionVariablePVFactory;

  

#endif