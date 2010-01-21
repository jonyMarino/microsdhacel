#ifndef _PROPIEDAD_GETTER_FACTORY_HPP
#define _PROPIEDAD_GETTER_FACTORY_HPP

#include "PropiedadGetter.hpp"

struct PropiedadGetterFactory{
  public:
    virtual PropiedadGetter& getPropiedad(void*obj,const struct ArgumentosPropiedadGetter* args)const{
      return *new PropiedadGetter(obj,args);
    }
};


#endif