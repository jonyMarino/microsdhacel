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
