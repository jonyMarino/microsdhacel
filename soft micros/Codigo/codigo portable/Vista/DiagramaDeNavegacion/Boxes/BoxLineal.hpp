#ifndef _BOX_LINEAL_HPP
#define _BOX_LINEAL_HPP

#include "BoxPropiedad.hpp"
#include "PropiedadIncrementable.hpp"
#include "ConstructorPropiedadGetter.hpp"

struct ConstructorBoxLineal{
  struct ConstructorBox super;
  const struct ConstructorPropiedadGetter *const* propiedades;
  const struct ConstructorBox * proximoBox;    
};

class BoxLineal:public BoxPropiedad{
  public:
    BoxLineal(struct ConstructorBoxLineal * constructor,void*obj,uchar numObjeto);  
    ~BoxLineal();
    virtual Box * procesarTecla(uchar tecla,TEstadoBox& estado);
  private:
    struct ConstructorBoxLineal * constructor;
    uchar numProp;
    void mostrarPropiedad(void * obj);
};


struct BoxLinealFactory:public BoxFactory{
  virtual Box& getBox(const void*args,void*obj,uchar numObjeto)const{
    return *new BoxLineal((struct ConstructorBoxLineal *)args,obj,numObjeto);
  }
};

extern const struct BoxLinealFactory boxLinealFactory;

#endif
