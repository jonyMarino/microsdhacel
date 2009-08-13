#include "IPWM.h"

const struct Class IPWMClass={
    CLASS_INITIALIZATION(Class,IPWMClass,Class,Object_ctor,Object_dtor,Object_differ,Object_puto)  
};

const struct IPWMClass IPWM={
    CLASS_INITIALIZATION(IPWMClass,IPWM,ISalida,Object_ctor,Object_dtor,Object_differ,Object_puto)  
};