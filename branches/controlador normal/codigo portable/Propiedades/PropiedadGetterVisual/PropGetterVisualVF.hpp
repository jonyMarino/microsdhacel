#ifndef _PROP_GETTER_VISUAL_VF_HPP
#define _PROP_GETTER_VISUAL_VF_HPP

#include <stdtypes.h>
#include "Propiedades/PropiedadGetterVF.hpp"
#include "OOC/ooc/lib_cpp/OutputStream.hpp"

#pragma DATA_SEG GETTERS_VISUAL_VF_DATA                                            
#pragma CODE_SEG GETTERS_VISUAL_VF_CODE 
#pragma CONST_SEG DEFAULT

struct ArgumentosPropGetterVisualVF{
  struct ArgumentosPropiedadGetterVF super;
  char * descripcion;
  char * unidad;
};

class PropGetterVisualVF:public PropiedadGetterVF{
  public:
    PropGetterVisualVF(void*obj,const struct ArgumentosPropGetterVisualVF* args,uchar numObjeto);
    void printDescripcion(OutputStream&os);
    inline uchar getNumObjeto(){ return numObjeto;}
  protected:
    virtual const char * getDescripcion();
    virtual const char * getUnidad();
  private:
    uchar numObjeto;  
};

struct PropGetterVisualVFFactory{
    PropGetterVisualVFFactory();
    virtual PropiedadGetterVF& getPropiedad(void*obj,const struct ArgumentosPropiedadGetterVF* args,uchar numObjeto)const;/*{
      return *new PropGetterVisual(obj,args);
    }          */
};

struct ConstructorPropGetterVisualVF{
    const struct PropGetterVisualVFFactory * factory;
    struct ArgumentosPropGetterVisualVF args;
    PropiedadGetterVF& getPropiedad(void*obj,uchar numObjeto)const;
};




#pragma DATA_SEG DEFAULT                                            
#pragma CODE_SEG DEFAULT 


#endif