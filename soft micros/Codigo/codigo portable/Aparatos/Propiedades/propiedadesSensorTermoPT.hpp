#ifndef PROPIEDADES_SENSOR_TERMO_PT_HPP
#define PROPIEDADES_SENSOR_TERMO_PT_HPP

#include "PropGetterVisual.hpp"
#include "PropiedadNumerica.hpp"
#include "PropNumLFPV.hpp"
#include "PropNumLFPF.hpp"
#include "PropiedadTextual.hpp"

extern const struct ConstructorPropiedadTextual cPropiedadTipoSensor;
extern const struct ConstructorPropNumLFPF cPropiedadFiltro;
extern const struct ConstructorPropNumLFPV cPropiedadOffset;
extern const struct ConstructorPropNumLFPF cPropiedadGanancia;
extern const struct ConstructorPropNumLFPV cPropiedadAjCeroT;
extern const struct ConstructorPropNumLFPF cPropiedadAjGanT;
extern const struct ConstructorPropNumLFPV cPropiedadAjCeroPT;
extern const struct ConstructorPropNumLFPF cPropiedadAjGanPT;
extern const struct ConstructorPropNumLFPF cPropiedadAjTempAmb;

#endif
