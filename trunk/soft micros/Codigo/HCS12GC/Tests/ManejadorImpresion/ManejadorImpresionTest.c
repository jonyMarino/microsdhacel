#include <string.h>
#include <stdlib.h>
#include "ManejadorImpresionTest.h"
#include "Timer.h"
#include "ManejadorImpresion.h"
#include "System.h"
#include "OutputStream.h"
#include "ManejadorImpresion.h"

void ManejadorImpresionTest_defCtor(void * self,va_list * args);


const struct TestCaseClass ManejadorImpresionTest={
  &TestCaseClass,
  "ManejadorImpresionTest",
  &TestCase,
  sizeof(struct ManejadorImpresionTest),
  ManejadorImpresionTest_defCtor,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL
};


/*
*/
bool ManejadorImpresionTest_test(void * _self){
  struct ManejadorImpresionTest * self = _self;
  long i,j ;
  struct SensorSimulado * s = new(&SensorSimulado);
  struct OutputStream * os = new(&OutputStream);
  struct ManejadorImpresion * mi = new(&ManejadorImpresion,os);
  
  LinkedList_add(mi,s);
  
  ManejadorImpresion_setIntervalo(mi,1000);
   
  
  for(i=0;i<20000;i++){
    SensorSimulado_setValue(s,i);
    SensorSimulado_setDecimales(s,i%5);
    IncTimers(1);
    RlxMTimer_Handler();
  }
  
  return ERR_OK;
}

/*
*/
void ManejadorImpresionTest_constructor(void *self){
  struct ManejadorImpresionTest * _self = self;
  TestCase_constructor(self);
  System_init();                     
  //tests 
  TESTCASE_ADD_TEST(self,ManejadorImpresionTest_test);	 
}
/**/
void ManejadorImpresionTest_defCtor(void * self,va_list * args){
  ManejadorImpresionTest_constructor(self);  
}
