#ifndef _PROP_GETTER_VISUAL_HPP
#define _PROP_GETTER_VISUAL_HPP

#include <stdtypes.h>
#include "../PropiedadGetter.hpp"
#include "OOC/ooc/lib_cpp/OutputStream.hpp"

#pragma DATA_SEG GETTERS_VISUAL_DATA                                            
#pragma CODE_SEG GETTERS_VISUAL_CODE 
#pragma CONST_SEG DEFAULT

struct ArgumentosPropGetterVisual{
  struct ArgumentosPropiedadGetter super;
  char * descripcion;
};

class PropGetterVisual:public PropiedadGetter{
  public:
    PropGetterVisual(void*obj,const struct ArgumentosPropGetterVisual* args,uchar numObjeto);
    void printDescripcion(OutputStream&os);
    inline uchar getNumObjeto(){ return numObjeto;}
  protected:
    virtual const char * getDescripcion();
  private:
    uchar numObjeto;  
};

struct PropGetterVisualFactory{
    virtual PropiedadGetter& getPropiedad(void*obj,const struct ArgumentosPropiedadGetter* args,uchar numObjeto)const;/*{
      return *new PropGetterVisual(obj,args);
    }          */
};

struct ConstructorPropGetterVisual{
    const struct PropGetterVisualFactory * factory;
    struct ArgumentosPropGetterVisual args;
    PropiedadGetter& getPropiedad(void*obj,uchar numObjeto)const;
};




#pragma DATA_SEG DEFAULT                                            
#pragma CODE_SEG DEFAULT 


#endif