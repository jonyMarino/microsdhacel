#ifndef _CONSTRUCTOR_PROPIEDAD_GETTER_HPP
#define _CONSTRUCTOR_PROPIEDAD_GETTER_HPP

#include "../Standard/Getter.hpp"
#include "PropiedadGetter.hpp"
#include "PropiedadGetterFactory.hpp"

struct ConstructorPropiedadGetter{
 // public: 
    //atributos:
    //ConstructorPropiedadGetter(const struct PropiedadGetterFactory * _factory,const struct ArgumentosPropiedadGetter *_args):factory(_factory),args(_args){}
    const struct PropiedadGetterFactory * factory;
    struct ArgumentosPropiedadGetter args;
    //Metodos:
    PropiedadGetter& getPropiedad(void*obj)const;
};



#endif