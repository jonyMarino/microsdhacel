#include "comunicacionPWM.hpp"
#include "propiedadesPWM.hpp"

const void * costructoresPropiedadesPWM[] = {
    &cPropiedadPeriodo
};

const NEW_ARRAY( arrayCostructoresPropiedadesPWM,costructoresPropiedadesPWM) ;

const GetsProps getPropiedadesPWM={
  &arrayCostructoresPropiedadesPWM,
  TRUE
};
