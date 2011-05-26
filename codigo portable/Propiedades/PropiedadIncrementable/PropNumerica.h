#ifndef _PROP_NUMERICA_H
#define _PROP_NUMERICA_H

#include "PropWithInc.h"

struct ConstPropNum{
  struct ConstructorPropWInc _base;
  uchar dot;
};

struct PropNum{
  struct PropWInc _prop_base;
};

extern const struct PropWIncClass PropNum;

#endif