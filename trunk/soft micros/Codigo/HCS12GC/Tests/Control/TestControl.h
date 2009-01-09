#ifndef _TEST_CONTROL_H
#define _TEST_CONTROL_H

#include "TestCase.h"
#include "SensorSimulado.h"
#include "ControlPID.h"
#include "SalidaSimulada.h"

struct TestControl{
  struct TestCase super;
  struct SensorSimulado sensor;
  struct ControlPID control;
  struct SalidaSimulada salida;
  struct Timer timer; 
};

extern const void * const TestControl;


#endif