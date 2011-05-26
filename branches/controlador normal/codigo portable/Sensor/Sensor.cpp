
#include "Sensor/Sensor.hpp"

void Sensor::addOnNuevoValorListener(const struct Method* metodo) {
  listeners.add((void*)metodo);
}

void Sensor::callOnNuevoValorListeners() {
  listeners.executeMethods();
}

void Sensor::deleteOnNuevoValorListener(const struct Method * metodo) {
  listeners.moveOut((void*)metodo);  
}

Sensor::TSensorState Sensor::getEstado() {
  return SENSOR_OK;
}

int Sensor::getLimiteInferior() {
  return 0;
}

int Sensor::getLimiteSuperior() {
  return 9999;
}

