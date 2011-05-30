#include "comunicacionAlarma.hpp"
#include "propiedadesAlarma.hpp"

const void * costructoresPropiedadesAlarma[] = {
      &cPropiedadModoAlarma,
      &cPropiedadTipoCtrlAlarma,
      &cPropiedadTipoLazo,
      &cPropiedadRetLimInf,
      &cPropiedadRetLimSup,
      &cPropiedadHistAlarma,
      &cPropiedadTipoSalida,
      &cPropiedadSetPointAlarma
};

const NEW_ARRAY( arrayCostructoresPropiedadesAlarma,costructoresPropiedadesAlarma) ;

const GetsProps getPropiedadesAlarma={
  &arrayCostructoresPropiedadesAlarma,
  TRUE
};

/*Getters*/
const void * costructoresGettersAlarma[] = {
  &cPropiedadGetPotencia
};

const NEW_ARRAY( arrayCostructoresGettersAlarma,costructoresGettersAlarma) ;

const GetsProps getGettersAlarma={
  &arrayCostructoresGettersAlarma,
  FALSE
};
