#ifndef _BOX_ACCESS_H
#define _BOX_ACCESS_H

#include <stdtypes.h>

#include "ClassBox.h"
#include "PropWithInc.h"

struct BoxAccess{
  struct Box _box;
  int ValorTmp;
  int Code;
};

extern const struct BoxClass BoxAccess;

/*
** ===================================================================
**     Method      :  AccessBox_Constructor 
**     Description :  Constructor del Box
** ===================================================================
*/
void AccessBox_Constructor(void * _self, char*str1,int Code);


#endif