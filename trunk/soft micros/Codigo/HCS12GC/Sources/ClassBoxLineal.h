#ifndef _CLASS_BOX_LINEAL
#define _CLASS_BOX_LINEAL

#include "ClassObjBox.h"
#include "PropWithInc.h"

struct BlockCnstrBoxLin{
  struct BlockBoxConstruct BlckConst;
  struct ConstructorPropWInc ** props;
  struct BlockBoxConstruct * pNextBlckConst;    
};

struct BoxLineal{
  struct ObjBox _box;
  struct BlockCnstrBoxLin * pBlockSelf;
  uchar NumProp;
//Private:  
  struct PropWInc * prop_actual;  // propiedad actual
  void * Obj;                     //Objeto al que pertenecen el conjunto de las propiedades
  uchar save;                     // si tiene algun valor que guardar  
};

extern const struct BoxClass BoxLineal; 

#endif