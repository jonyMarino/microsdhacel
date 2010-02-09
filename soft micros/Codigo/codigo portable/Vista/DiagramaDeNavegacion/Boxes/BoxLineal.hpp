#ifndef _BOX_LINEAL_HPP
#define _BOX_LINEAL_HPP

#include "BoxPropiedad.hpp"
#include "PropiedadIncrementable.hpp"
#include "ConstructorPropiedadGetter.hpp"

struct ConstructorBoxLineal{
  struct ConstructorBox super;
  const struct ConstructorPropGetterVisual *const* propiedades;
  const struct ConstructorBox * proximoBox;
      
};

class BoxLineal:public BoxPropiedad{
  public:
    BoxLineal(struct ConstructorBoxLineal * constructor,void*obj,uchar numObjeto);  
    ~BoxLineal();
    virtual Box * procesarTecla(uchar tecla,TEstadoBox& estado);
  
  protected:
    BoxLineal(struct ConstructorBoxLineal * constructor);  
    void mostrarPropiedad(void * obj,int numObjeto); 
     struct ConstructorBoxLineal * getConstructor ();
     uchar getNumProp ();
     void setNumProp (uchar n);
  
  private:
    void initBoxLineal (struct ConstructorBoxLineal * _constructor);
    struct ConstructorBoxLineal * constructor;
    uchar numProp;
  
};


struct BoxLinealFactory:public BoxFactory{
  virtual Box& getBox(const void*args,void*obj,uchar numObjeto)const{
    return *new BoxLineal((struct ConstructorBoxLineal *)args,obj,numObjeto);
  }
};

extern const struct BoxLinealFactory boxLinealFactory;

#endif
