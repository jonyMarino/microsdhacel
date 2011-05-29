#include "comunicacionControl.hpp"
#include "propiedadesControl.hpp"

const void * costructoresPropiedadesControl[] = {
    &cPropiedadModos,
    &cPropiedadReset,
    &cPropiedadHisteresis,
    &cPropiedadIntegral,
    &cPropiedadDerivada,
    &cPropiedadSetPoint,
    &cPropiedadSetPointAutoSintonia,
    &cPropiedadModoSalida,
    &cPropiedadPotManual,
    &cPropiedadGetPotenciaInst,
    &cPropiedadLimInfPot,
    &cPropiedadLimSupPot,
    &cPropiedadLimInfSp,
    &cPropiedadLimSupSp,
    &cPropiedadLimInfPotAs,
    &cPropiedadLimSupPotAs,
    &cPropiedadLimInfSpAs,
    &cPropiedadLimSupSpAs,
    &cPropiedadGetSensor1
};

const NEW_ARRAY( arrayCostructoresPropiedadesControl,costructoresPropiedadesControl) ;

const GetsProps getPropiedadesControl={
  &arrayCostructoresPropiedadesControl,
  TRUE
};
