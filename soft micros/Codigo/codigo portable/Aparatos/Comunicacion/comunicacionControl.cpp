#include "comunicacionControl.hpp"
#include "propiedadesControl.hpp"

const void * costructoresPropiedadesControl[] = {
    &cPropiedadModos,
    &cPropiedadReset,
    &cPropiedadHisteresis,
    &cPropiedadIntegral,
    &cPropiedadDerivada,
    &cPropiedadSetPoint,
    &cPropiedadModoSalida,
    &cPropiedadPotManual,
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

const void * costructoresGettersControl[] = {
  &cPropiedadGetPotenciaInst
};

const NEW_ARRAY( arrayCostructoresGettersControl,costructoresGettersControl) ;

const GetsProps getGettersControl={
  &arrayCostructoresGettersControl,
  FALSE
};
