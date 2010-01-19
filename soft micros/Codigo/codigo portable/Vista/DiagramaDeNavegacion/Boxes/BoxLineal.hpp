#ifndef _BOX_LINEAL_HPP
#define _BOX_LINEAL_HPP

#include "Box.hpp"
#include "PropiedadIncrementable.hpp"
#include "ConstructorPropiedadGetter.hpp"

struct ConstructorBoxLineal{
  struct ConstructorBox super;
  struct ConstructorPropiedadGetter ** propiedades;
  struct ConstructorBox * proximoBox;    
};

class BoxLineal:public Box{
  public:
    BoxLineal(struct ConstructorBoxLineal * constructor,void*obj,uchar numObjeto);  
    ~BoxLineal();
    virtual void refresh();
    virtual Box * procesarTecla(uchar tecla,TEstadoBox& estado);
  private:
    struct ConstructorBoxLineal * constructor;
    PropiedadIncrementable* propiedadActual;
    uchar numProp;
    uchar save;
    void mostrarPropiedad(void * obj);
};


struct BoxLinealFactory:public BoxFactory{
  virtual Box& getBox(void*args,void*obj,uchar numObjeto)const{
    return *new BoxLineal((struct ConstructorBoxLineal *)args,obj,numObjeto);
  }
};

#endif
