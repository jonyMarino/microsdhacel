
#include "PWMPeriodoEvent.hpp"
//#include "Method.hpp"

void PWMPeriodoEvent::addPeriodoListener(void * metodo) {
  listeners.add(metodo);
}

void PWMPeriodoEvent::deletePeriodoListenermetodo(void * metodo) {
  listeners.moveOut(metodo);
}

unsigned char PWMPeriodoEvent::setPeriodo(int period) {
  listeners.executeMethods();
  return setPeriodo(period); 
}

