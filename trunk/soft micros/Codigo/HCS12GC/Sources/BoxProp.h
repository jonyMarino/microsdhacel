#ifndef BOX_PROP_H
#define BOX_PROP_H

#include "BoxPropBase.h"

#include "PropWithInc.h"


struct BlockConstBoxProp{
  struct BlockConstBoxPropBase _base;
  struct BlockBoxConstruct * pNextBlckConst;    
};

struct BoxProp{
  struct BoxPropBase _base;
};

extern const struct BoxClass BoxProp; 


/*
** ===================================================================
**     Method      :  BoxLineal_getNext 
**     Description :  Devuelve el Bloque Constructor del siguiente Box
** ===================================================================
*/
struct BlockBoxConstruct * BoxProp_getNext(void * _self,uchar tecla);


#endif 