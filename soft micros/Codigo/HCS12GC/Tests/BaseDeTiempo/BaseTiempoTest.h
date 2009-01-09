#ifndef _BASE_TIEMPO_TEST_H
#define _BASE_TIEMPO_TEST_H

#include "TestCase.h"
#include "SensorSimulado.h"
#include "ControlPID.h"
#include "SalidaSimulada.h"

struct BaseTiempoTest{
  struct TestCase super;
  struct SensorSimulado sensor;
  struct SalidaSimulada salida;
};

extern const struct TestCaseClass BaseTiempoTest;


#endif