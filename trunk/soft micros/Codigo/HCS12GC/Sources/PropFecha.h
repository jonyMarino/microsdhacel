#ifndef _PROP_HORA_H
#define _PROP_HORA_H

#include "PropWithInc.h"

struct ConstPropHora{
  struct ConstructorPropWInc _prop_base;
};

struct PropHora{
  struct PropWInc _prop;  //PropVisual; ValorTmp; LimInf; LimSup
};

extern const void* PropHora;



#endif