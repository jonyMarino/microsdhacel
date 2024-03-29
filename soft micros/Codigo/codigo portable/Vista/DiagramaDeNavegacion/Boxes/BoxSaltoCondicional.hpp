#ifndef _BOX_SALTO_CONDICIONAL_HPP
#define _BOX_SALTO_CONDICIONAL_HPP

#include "BoxPropiedad.hpp"
#include "Propiedades/PropiedadIncrementable/PropiedadIncrementable.hpp"
#include "Propiedades/ConstructorPropiedadGetter.hpp"

struct ConstructorBoxSaltoCondicional{
  struct ConstructorBox super;
  const struct ConstructorPropGetterVisual * propiedad;
  Box * (*getNextBox)(PropGetterVisual * prop,uchar tecla);
};

class BoxSaltoCondicional:public BoxPropiedad{
  public:
    BoxSaltoCondicional(struct ConstructorBoxSaltoCondicional * constructor,void*obj,uchar numObjeto);  
    ~BoxSaltoCondicional();
    virtual Box * procesarTecla(uchar tecla,TEstadoBox& estado);
  private:
    PropiedadIncrementable * propiedad;
    struct ConstructorBoxSaltoCondicional * constructor;
    uchar save;
};


struct BoxSaltoCondicionalFactory:public BoxFactory{
  virtual Box& getBox(const void*args,void*obj,uchar numObjeto)const{
    return *new BoxSaltoCondicional((struct ConstructorBoxSaltoCondicional *)args,obj,numObjeto);
  }
};

extern const struct BoxSaltoCondicionalFactory boxSaltoCondicionalFactory;

#endif
