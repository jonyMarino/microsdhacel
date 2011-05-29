#ifndef PROPIEDADES_ALARMA_HPP
#define PROPIEDADES_ALARMA_HPP

#include "PropGetterVisual.hpp"
#include "PropiedadNumerica.hpp"
#include "PropNumLFPV.hpp"
#include "PropNumLFPF.hpp"
#include "PropNumLVPF.hpp"
#include "PropiedadTextual.hpp"
#include "PropGetterNumerico.hpp"
#include "PropDescripcionVariable.hpp"
#include "PropDescripcionVariablePV.hpp"

extern const struct ConstructorPropiedadTextual cPropiedadModoAlarma;
extern const struct ConstructorPropiedadTextual cPropiedadTipoCtrlAlarma;
extern const struct ConstructorPropiedadTextual cPropiedadTipoLazo;
extern const struct ConstructorPropNumLFPF cPropiedadRetLimInf;
extern const struct ConstructorPropNumLFPF cPropiedadRetLimSup;
extern const struct ConstructorPropDescripcionVariablePV cPropiedadHistAlarma;
extern const struct ConstructorPropiedadTextual cPropiedadTipoSalida;
extern const struct ConstructorPropNumLFPV cPropiedadSetPointAlarma;

#endif
