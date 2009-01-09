#include <string.h>
#include <stdlib.h>
#include "TestAlarmaControl.h"
#include "Timer.h"
#include "SalidaBanda.h"
#include "CntrProporcional.h"
#include "LazoControl.h"
#include "AlarmaControl.h"

void TestAlarmaControl_defCtor(void * self,va_list * args);


#define CAMBIO1

const struct TestCaseClass TestAlarmaControl={
  &TestCaseClass,
  "TestAlarmaControl",
  &TestCase,
  sizeof(struct TestAlarmaControl),
  TestAlarmaControl_defCtor,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL
};


/*
*/
bool TestAlarmaControl_testAlarmaControl(void * _self){
  struct TestAlarmaControl * self = _self;
  struct AlarmaCntrConf config;
  bool result;
  struct AlarmaControl * alarma;
  struct ControlPID * control;
  ControlConf configuracionControl;
  
  control = new(ControlPID,&configuracionControl,&self->sensor,new(&SalidaSimulada));
  alarma = new(&AlarmaControlClass,&config,control,&self->salida);
  
  PID_setConfSP(control,10);
  
  AlarmaControl_setTipo(alarma,ALARMA_CONTROL);
  AlarmaControl_setAdaptadorSalida(alarma,SALIDA_EXCESO);
  AlarmaControl_setControl(alarma,CONTROL_BANDA);
  
  SensorSimulado_setValue(&self->sensor,100);
  
  AlarmaControl_setValor(alarma,100);
  AlarmaControl_setHisteresis(alarma,1000); 
//salida no on off:  
  setTipoSalida(&self->salida,SALIDA_PROPORCIONAL);
  SensorSimulado_forzarProcesamiento(&self->sensor);
  //valorControl = 40
  if( getPotencia(&self->salida)!=540 )
    result = EXIT_FAILURE;
  else
    result = EXIT_SUCCESS; 
  
  delete(alarma);
  
  return result;
  
}

/*
*/
void TestAlarmaControl_constructor(void *self){
  struct TestAlarmaControl * _self = self;
  TestCase_constructor(self);
  
  newAlloced(&_self->sensor,&SensorSimulado,0,NULL,1000,"SEn Sim");
      
  newAlloced(&_self->salida,&SalidaSimulada);
  setConectada(&_self->salida,TRUE);
  //newAllocObj(&_self->control,ControlPID,conf,&_self->sensor,&_self->salida,0);
                       
  //tests 
  TESTCASE_ADD_TEST(self,TestAlarmaControl_testAlarmaControl);	 
}
/**/
void TestAlarmaControl_defCtor(void * self,va_list * args){
  TestAlarmaControl_constructor(self);  
}
