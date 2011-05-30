#ifndef _PROPIEDADES_CONTROL_HPP
#define _PROPIEDADES_CONTROL_HPP

#include "PropDescripcionVariable.hpp"
#include "PropDescripcionVariablePV.hpp"
#include "PropGetterNumericoPV.hpp"
#include "PropGetterVisual.hpp"
#include "PropiedadNumerica.hpp"
#include "PropNumLFPV.hpp"
#include "PropNumLFPF.hpp"
#include "PropNumLVPF.hpp"
#include "PropiedadTextual.hpp"
#include "PropGetterNumerico.hpp"

//extern const struct ConstructorPropGetterNumericoPV cPropiedadSetPointAutoSintonia;
extern const struct ConstructorPropGetterNumerico cPropiedadGetPotenciaInst;

extern const struct ConstructorPropiedadTextual cPropiedadModos;
extern const struct ConstructorPropNumLFPV cPropiedadReset;
extern const struct ConstructorPropDescripcionVariablePV cPropiedadHisteresis;
extern const struct ConstructorPropNumLFPF cPropiedadIntegral;
extern const struct ConstructorPropNumLFPF cPropiedadDerivada;
extern const struct ConstructorPropNumLFPV cPropiedadSetPoint;
extern const struct ConstructorPropiedadTextual cPropiedadModoSalida;
extern const struct ConstructorPropNumLVPF cPropiedadPotManual;
extern const struct ConstructorPropNumLFPF cPropiedadLimInfPot;
extern const struct ConstructorPropNumLFPF cPropiedadLimSupPot;
extern const struct ConstructorPropNumLFPV cPropiedadLimInfSp;
extern const struct ConstructorPropNumLFPV cPropiedadLimSupSp;
extern const struct ConstructorPropNumLFPF cPropiedadLimInfPotAs;
extern const struct ConstructorPropNumLFPF cPropiedadLimSupPotAs;
extern const struct ConstructorPropNumLFPV cPropiedadLimInfSpAs;
extern const struct ConstructorPropNumLFPV cPropiedadLimSupSpAs;
extern const struct ConstructorPropGetterNumericoPV cPropiedadGetSensor1;


#endif
