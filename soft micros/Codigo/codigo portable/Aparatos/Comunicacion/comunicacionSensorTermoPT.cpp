#include "comunicacionSensorTermoPT.hpp"
#include "propiedadesSensorTermoPT.hpp"

const void * costructoresGettersSensorTermoPT[] = {
    &cGetterValSen,
    &cGetterEstado
};

const void * costructoresPropiedadesSensorTermoPT[] = {
    &cPropiedadTipoSensor,
    &cPropiedadFiltro,
    &cPropiedadOffset,
    &cPropiedadGanancia,
    &cPropiedadAjCeroT,
    &cPropiedadAjGanT,
    &cPropiedadAjCeroPT,
    &cPropiedadAjGanPT,
    &cPropiedadAjTempAmb
};

const NEW_ARRAY( arrayCostructoresPropiedadesSensorTermoPT,costructoresPropiedadesSensorTermoPT) ;

const GetsProps getPropiedadesSensorTermoPT={
  &arrayCostructoresPropiedadesSensorTermoPT,
  TRUE
};

const NEW_ARRAY( arrayCostructoresGettersSensorTermoPT,costructoresGettersSensorTermoPT) ;

const GetsProps getGettersSensorTermoPT={
  &arrayCostructoresGettersSensorTermoPT,
  FALSE
};