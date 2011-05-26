#ifndef _BOX_LINEAL_VF_HPP
#define _BOX_LINEAL_VF_HPP

#include "BoxPropiedadVF.hpp"
#include "Propiedades/PropiedadIncrementable/PropiedadIncrementableVF.hpp"
#include "Propiedades/ConstructorPropiedadGetter.hpp"

struct ConstructorBoxLinealVF{
  struct ConstructorBox super;
  const struct ConstructorPropGetterVisualVF *const* propiedades;
  const struct ConstructorBox * proximoBox;
      
};

class BoxLinealVF:public BoxPropiedadVF{
  public:
    BoxLinealVF(struct ConstructorBoxLinealVF * constructor,void*obj,uchar numObjeto);  
    ~BoxLinealVF();
    virtual Box * procesarTecla(uchar tecla,TEstadoBox& estado);
  
  protected:
    BoxLinealVF(struct ConstructorBoxLinealVF * constructor);  
    void mostrarPropiedad(void * obj,int numObjeto); 
     struct ConstructorBoxLinealVF * getConstructor ();
     uchar getNumProp ();
     void setNumProp (uchar n);
  
  private:
    void initBoxLineal (struct ConstructorBoxLinealVF * _constructor);
    struct ConstructorBoxLinealVF * constructor;
    uchar numProp;
  
};


struct BoxLinealVFFactory:public BoxFactory{
  virtual Box& getBox(const void*args,void*obj,uchar numObjeto)const{
    return *new BoxLinealVF((struct ConstructorBoxLinealVF *)args,obj,numObjeto);
  }
};

extern const struct BoxLinealVFFactory boxLinealVFFactory;

#endif
