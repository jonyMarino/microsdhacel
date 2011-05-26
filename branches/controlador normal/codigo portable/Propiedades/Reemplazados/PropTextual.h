#ifndef _PROP_TEXTUAL_H
#define _PROP_TEXTUAL_H

#include "PropWithInc.h"

struct ConstPropTxt{
  struct ConstructorPropWInc _prop_base;
  char*(*_getTxt)(uchar);
};

struct PropTxt{
  struct PropWInc _prop;  //PropVisual; ValorTmp; LimInf; LimSup
};

extern const struct PropWIncClass PropTxt;



#endif