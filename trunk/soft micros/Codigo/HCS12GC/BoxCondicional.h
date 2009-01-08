#ifndef BOX_CONDICIONAL_H
#define BOX_CONDICIONAL_H

#include "BoxPropBase.h"

#include "PropWithInc.h"


struct BlockConstBoxCondicional{
  struct BlockConstBoxPropBase _base;
  struct BlockBoxConstruct * (*getNextBlckConst)(void*,uchar); 	 //recibe la propiedad
};

struct BoxCondicional{
  struct BoxPropBase _base;
};

extern const struct BoxClass BoxCondicional; 



#endif 