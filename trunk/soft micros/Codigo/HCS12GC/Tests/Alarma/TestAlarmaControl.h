#ifndef _TEST_ALARMA_POR_VALOR_H
#define _TEST_ALARMA_POR_VALOR_H

#include "TestCase.h"
#include "SensorSimulado.h"
#include "ControlPID.h"
#include "SalidaSimulada.h"

struct TestAlarmaControl{
  struct TestCase super;
  struct SensorSimulado sensor;
  struct SalidaSimulada salida;
};

extern const struct TestCaseClass TestAlarmaControl;


#endif