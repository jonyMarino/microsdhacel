#ifndef _PROP_NUM_P_V
#define _PROP_NUM_P_V

#include "stdtypes.h"
#include "stddef.h"
#include "PropWithInc.h"

struct ConstPropNumPV{
  struct ConstructorPropWInc _base;  
  uchar (*_getDec)(void*);
};

struct PropNumPV{
  struct PropWInc _base_prop;
};

extern const struct PropWIncClass PropNumPV; 

#endif 