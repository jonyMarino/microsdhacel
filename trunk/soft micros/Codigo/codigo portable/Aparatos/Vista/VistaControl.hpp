#ifndef _VISTA_CONTROL_HPP
#define _VISTA_CONTROL_HPP

#include "BoxLineal.hpp"
#include "PropNumLFPV.hpp"

extern const struct ConstructorBoxLineal cBoxesSintonia;
extern const struct ConstructorBoxPropiedadEntradaCondicional cBoxesHisteresis;
extern const struct ConstructorBoxPropiedadEntradaCondicional cBoxesDerivada;
extern const struct ConstructorBoxPropiedadEntradaCondicional cBoxesIntegral;
extern const struct ConstructorBoxPropiedad cBoxesReset;
extern const struct ConstructorBoxPropiedad cBoxesSetPoint;
extern const struct ConstructorPropNumLFPV cPropiedadSetPointAutoSintonia;
extern const struct ConstructorPropNumLFPV cPropiedadSetPoint;
extern const struct ConstructorPropNumLVPF cPropiedadPotManual;
extern const struct ConstructorPropGetterNumerico cPropiedadGetPotenciaInst;
extern const struct ConstructorBoxPropiedad cBoxModoSalida;
extern const struct ConstructorBoxPropiedadEntradaCondicional cBoxPotInst;
extern const struct ConstructorBoxLinealCondicional cBoxPotMan;
extern const struct ConstructorBoxLineal cBoxesLimites;
extern const struct ConstructorPropiedadTextual cPropiedadModoSalida;
extern const struct ConstructorPropGetterNumericoPV cPropiedadGetSensor1;
extern const struct ConstructorBoxPropiedad cBoxModos;
#endif