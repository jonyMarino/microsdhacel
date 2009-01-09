#ifndef _TEST_RTI_ESPERA_POW_UP_H
#define _TEST_RTI_ESPERA_POW_UP_H

#include "TestCase.h"

struct TestRTIEsperaPowUp{
  struct TestCase super;
  bool prendido;
  void * ins;
};

extern const struct TestCaseClass TestRTIEsperaPowUp;


#endif