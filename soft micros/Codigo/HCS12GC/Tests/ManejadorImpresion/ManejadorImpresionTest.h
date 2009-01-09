#ifndef _MANEJADOR_IMPRESION_H
#define _MANEJADOR_IMPRESION_H

#include "TestCase.h"
#include "SensorSimulado.h"
#include "ControlPID.h"
#include "SalidaSimulada.h"

struct ManejadorImpresionTest{
  struct TestCase super;
};

extern const struct TestCaseClass ManejadorImpresionTest;


#endif