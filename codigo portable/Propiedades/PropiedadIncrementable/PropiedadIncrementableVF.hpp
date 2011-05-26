#ifndef _PROPIEDAD_INCREMENTABLE_VF_HPP
#define _PROPIEDAD_INCREMENTABLE_VF_HPP

#include <stdtypes.h>
#include "Propiedades/PropiedadGetterVisual/PropGetterVisualVF.hpp"
#include "PE/include/PE_Types.h"

#pragma DATA_SEG PROP_GETTER_VF_NUMERICO_DATA                                            
#pragma CODE_SEG PROP_GETTER_VF_NUMERICO_CODE 
#pragma CONST_SEG DEFAULT

struct ArgumentosPropiedadIncrementableVF{
  struct ArgumentosPropGetterVisualVF super;
  void (*set)(void*,int,int);
};

class PropiedadIncrementableVF:public PropGetterVisualVF{
  public:
    PropiedadIncrementableVF(void*obj,const struct ArgumentosPropiedadIncrementableVF* args,uchar numObjeto);
    virtual void incrementar()=0;
    virtual void decrementar()=0;
    void guardar(); //para que los incrementos surjan efecto en el objeto controlado por la propiedad
    virtual int getVal();
    void refrescar();
    bool getIsGuardado();
    void setIsGuardado(bool val);
  protected:
    void setValorTmp(int valor);
  private:
    int valorTmp;
    int nroTmp;
    bool isGuardado;  //al guardar un parametro nuevo se pone en true, al refrescar se pone en false
};


#pragma DATA_SEG DEFAULT                                            
#pragma CODE_SEG DEFAULT 


#endif