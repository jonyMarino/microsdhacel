#include "ConstructorPropiedadGetter.hpp"

PropiedadGetter& ConstructorPropiedadGetter::getPropiedad(void*obj)const{
  return factory->getPropiedad(obj,&args);
}