#include "GetterWName.h"


const struct Class GetterWNameClass={
  CLASS_INITIALIZATION(Class,GetterWNameClass,Class,Object_ctor,Object_dtor,Object_differ,Object_puto)    
};
const struct GetterWNameClass GetterWName={
  CLASS_INITIALIZATION(GetterWNameClass,GetterWName,Object,Object_ctor,Object_dtor,Object_differ,Object_puto)    
};
