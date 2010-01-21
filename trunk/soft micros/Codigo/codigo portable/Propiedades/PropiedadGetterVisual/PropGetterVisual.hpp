#ifndef _PROP_GETTER_VISUAL_HPP
#define _PROP_GETTER_VISUAL_HPP

#include <stdtypes.h>
#include "../PropiedadGetter.hpp"
#include "OOC/ooc/lib_cpp/OutputStream.hpp"
#include "PropiedadGetterFactory.hpp"

#pragma DATA_SEG GETTERS_VISUAL_DATA                                            
#pragma CODE_SEG GETTERS_VISUAL_CODE 
#pragma CONST_SEG DEFAULT

struct ArgumentosPropGetterVisual{
  struct ArgumentosPropiedadGetter super;
  char * descripcion;
};

class PropGetterVisual:public PropiedadGetter{
  public:
    PropGetterVisual(void*obj,int numObjeto,const struct ArgumentosPropGetterVisual* args);
    void printDescripcion(OutputStream&os);
  private:
    const char * getDescripcion();  
};

struct PropGetterVisualFactory:public PropiedadGetterFactory{
    virtual PropiedadGetter& getPropiedad(void*obj,const struct ArgumentosPropiedadGetter* args)const;/*{
      return *new PropGetterVisual(obj,args);
    }          */
};

struct ConstructorPropGetterVisual{
    const struct PropiedadGetterFactory * factory;
    struct ArgumentosPropGetterVisual args;
};




#pragma DATA_SEG DEFAULT                                            
#pragma CODE_SEG DEFAULT 


#endif