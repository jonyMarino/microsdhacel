#ifndef _ON_POW_PROTECTED_H
#define _ON_POW_PROTECTED_H

#include "Object.h"
#include "MethodContainer.h"
#include "FunctionContainer.h"

struct OnPowDown{
  struct Object super;
  struct MethodContainer listeners;
};


#endif