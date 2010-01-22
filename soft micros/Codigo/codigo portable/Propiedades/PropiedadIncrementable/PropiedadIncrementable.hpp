#ifndef _PROPIEDAD_INCREMENTABLE_HPP
#define _PROPIEDAD_INCREMENTABLE_HPP

#include <stdtypes.h>
#include "PropGetterVisual.hpp"

#pragma DATA_SEG PROP_GETTER_NUMERICO_DATA                                            
#pragma CODE_SEG PROP_GETTER_NUMERICO_CODE 
#pragma CONST_SEG DEFAULT

struct ArgumentosPropiedadIncrementable{
  struct ArgumentosPropGetterVisual super;
  void (*set)(void*,int);
};

class PropiedadIncrementable:public PropGetterVisual{
  public:
    PropiedadIncrementable(void*obj,const struct ArgumentosPropiedadIncrementable* args,uchar numObjeto);
    virtual void incrementar()=0;
    virtual void decrementar()=0;
    void guardar(); //para que los incrementos surjan efecto en el objeto controlado por la propiedad
    virtual int getVal();
  protected:
    void setValorTmp(int valor);
  private:
    int valorTmp;
    
};
/*
struct PropiedadIncrementableFactory:public PropGetterVisualFactory{
    virtual PropiedadGetter& getPropiedad(void*obj,const struct ArgumentosPropiedadIncrementable* args)const;
};

struct ConstructorPropiedadIncrementable{
    const struct PropGetterVisualFactory * factory;
    struct ArgumentosPropiedadIncrementable args;
};
    */

#pragma DATA_SEG DEFAULT                                            
#pragma CODE_SEG DEFAULT 


#endif