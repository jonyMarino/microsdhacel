#ifndef _PROP_GETTER_VISUAL_HPP
#define _PROP_GETTER_VISUAL_HPP

#include "../PropiedadGetter.hpp"
#include "ConstructorPropGetterVisual.h"
#include "stdtypes.h"

#pragma DATA_SEG GETTERS_VISUAL_DATA                                            
#pragma CODE_SEG GETTERS_VISUAL_CODE 
#pragma CONST_SEG DEFAULT 

class PropGetterVisual:public PropiedadGetter{
  public:
    const char * getDescripcion();
    void print(OutputStream& os);

};

/*
** ===================================================================
**     Function      :  pProp_Constructor
**     Type        :  Polimorfica 
**     Description :  Constructor general de propiedad mediante 
**                    una propiedad de clase
** ===================================================================
*/
void * pGetter_Constructor(void * ClassGet,void * Obj);


struct ConstrGetterNum{
  struct ConstrGetVisual _base;
  uchar dot;
};

struct GetterNum{
  struct GetterVisual _prop_base;
};

extern const struct GetterWNameClass GetterNum;

/*
** ===================================================================
    GETTER TEXTUAL
** ===================================================================
*/
struct ConstrGetterTxt{
  struct ConstrGetVisual _base;
  char* (*getTxt)(uchar);
};

struct GetterTxt{
  struct GetterVisual _prop_base;
};

extern const struct GetterWNameClass GetterTxt;

#pragma DATA_SEG DEFAULT                                            
#pragma CODE_SEG DEFAULT 


#endif