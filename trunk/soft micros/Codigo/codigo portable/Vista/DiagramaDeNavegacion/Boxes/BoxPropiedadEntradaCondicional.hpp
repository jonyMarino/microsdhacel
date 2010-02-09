#ifndef _BOX_PROPIEDAD_ENTRADA_CONDICIONAL_HPP
#define _BOX_PROPIEDAD_ENTRADA_CONDICIONAL_HPP

#include "BoxPropiedad.hpp"

struct ConstructorBoxPropiedadEntradaCondicional{
  struct ConstructorBoxPropiedad super;
  bool (*getEvaluacionEntrada)(void * obj);   
};

struct BoxPropiedadEntradaCondicionalFactory:public BoxFactory{
  virtual Box& getBox(const void*args,void*obj,uchar numObjeto)const{
    BoxPropiedad&b = *new BoxPropiedad();
    struct ConstructorBoxPropiedadEntradaCondicional * c = (struct ConstructorBoxPropiedadEntradaCondicional *)args;
    if(c->getEvaluacionEntrada(obj))
      b.setPropiedad(*(PropGetterVisual*)&c->super.propiedad->getPropiedad(obj,numObjeto),FALSE);
    return b;
  }
};

extern const struct BoxPropiedadEntradaCondicionalFactory boxPropiedadEntradaCondicionalFactory;

#endif