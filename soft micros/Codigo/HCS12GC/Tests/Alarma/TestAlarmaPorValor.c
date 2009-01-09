#include <string.h>
#include <stdlib.h>
#include "TestAlarmaPorValor.h"
#include "Timer.h"
#include "SalidaBanda.h"
#include "CntrProporcional.h"
#include "LazoControl.h"
#include "AlarmaSensor.h"
#include "RetransmisionConf.h"
#include "SalidaRetenida.h"

void TestAlarmaPorValor_defCtor(void * self,va_list * args);
void TestAlarmaPorValor_setup(void * self);


#define CAMBIO1

const struct TestCaseClass TestAlarmaPorValor={
  TEST_CASE_CLASS_INITIALIZATION(TestCaseClass,
                                 TestAlarmaPorValor,
                                 TestCase,
                                 TestAlarmaPorValor_defCtor,
                                 Object_dtor,
                                 Object_differ,
                                 Object_puto,
                                 NULL,
                                 NULL)
};


/*
*/
bool TestAlarmaPorValor_testSalidaBanda(void * _self){
  struct TestAlarmaPorValor * self = _self;
  struct AdaptSalidaConf config;
  void * salida;
  
  salida=new(&SalidaBanda,&config,&self->salida);
  
  setHisteresis(salida,1000);
  //pruebo on off
  setTipoSalida(&self->salida,SALIDA_ONOFF);
  
  AdaptacionSalida_setPotenciaSalida(salida,0);
  
  if( getPotencia(&self->salida)!=0 )
    return EXIT_FAILURE;
  
  //pruebo proporcional
  setTipoSalida(&self->salida,SALIDA_PROPORCIONAL);
  
  AdaptacionSalida_setPotenciaSalida(salida,0);
  
  if( getPotencia(&self->salida)!=500 ) {    
    delete(salida);
    return EXIT_FAILURE;    
  }
    
  delete(salida);  
  return EXIT_SUCCESS;
}

/*
*/
bool TestAlarmaPorValor_testSalidaRetenida(void * _self){
  struct TestAlarmaPorValor * self = _self;
  struct AdaptSalidaConf config;
  void * salida;
  
  salida=new(&SalidaRetenidaClass,&config,&self->salida);
  
  setHisteresis(salida,100);
  
  AdaptacionSalida_setPotenciaSalida(salida,1000);
  
  if( getPotencia(&self->salida)!=1000 )
    return EXIT_FAILURE;
  
  AdaptacionSalida_setPotenciaSalida(salida,-100);
    
  //mantiene la salida
  if( getPotencia(&self->salida)!=1000 ) {    
    delete(salida);
    return EXIT_FAILURE;    
  }
  
  // libero la salida para que deje de mantenerla
  SalidaRetenida_liberar(salida);
  AdaptacionSalida_setPotenciaSalida(salida,-100);
  
    if( getPotencia(&self->salida)!=0 ) {    
    delete(salida);
    return EXIT_FAILURE;    
  }
    
  delete(salida);  
  return EXIT_SUCCESS;
}
/*
*/
bool TestAlarmaPorValor_testSalidaBloqueada(void * _self){
  struct TestAlarmaPorValor * self = _self;
  struct AdaptSalidaConf config;
  void * salida;
  
  salida=new(&SalidaBloqueadaClass,&config,&self->salida);
  
  setHisteresis(salida,100);
  
  AdaptacionSalida_setPotenciaSalida(salida,-100); // no deberia pegar a pesar de estar en condicion
  
  if( getPotencia(&self->salida)!=0 )
    return EXIT_FAILURE;
  
  AdaptacionSalida_setPotenciaSalida(salida,0);  
  AdaptacionSalida_setPotenciaSalida(salida,-100);  //deberia pegar
  
  //mantiene la salida
  if( getPotencia(&self->salida)!=1000 ) {    
    delete(salida);
    return EXIT_FAILURE;    
  }
    
  delete(salida);  
  return EXIT_SUCCESS;
}

/*
*/
bool TestAlarmaPorValor_testCntrProp(void * _self){
  struct TestAlarmaPorValor * self = _self;
  struct ValorControlConf config;
  void * control;
  
  control=new(&CntrProporcionalClass,&config,&self->sensor);
  ValorControl_setValorControlador(control,50);
  SensorSimulado_setValue(&self->sensor,100);
  
  if(getValorControl(control)!=-50){    
      delete(&control);
      return EXIT_FAILURE;
  }
  
  delete(control);  
  return EXIT_SUCCESS;

}

/*
*/
bool TestAlarmaPorValor_testLazoControl(void * _self){
  struct TestAlarmaPorValor * self = _self;
  bool result;
  struct ValorControlConf config;
  struct AdaptSalidaConf configAdapt;
  void * control;
  void * salida;
  void * lazoControl;

  control= new(&CntrProporcionalClass,&config,&self->sensor);  
  salida= new(&SalidaBanda,&configAdapt,&self->salida);
  lazoControl = new(&LazoControlClass,control,salida);
  
  SensorSimulado_setValue(&self->sensor,100);
  ValorControl_setValorControlador(control,150); 
  setHisteresis(salida,1000);
  setTipoSalida(&self->salida,SALIDA_PROPORCIONAL);
  
  SensorSimulado_forzarProcesamiento(&self->sensor);
  
  if( getPotencia(&self->salida)!=550 )
    result = EXIT_FAILURE;
  else
    result = EXIT_SUCCESS;  
  
  delete(lazoControl);
  delete(control);
  delete(salida);
  
  return result;

  
}

/*
*/
bool TestAlarmaPorValor_testLazoControlAlSen(void * _self){
  struct TestAlarmaPorValor * self = _self;
  struct ConfLazoCntrlAlSen config;
  bool result;
  struct  LazoControlAlSen * alarma;
  
  alarma = new(&LazoControlAlSen,&config,&self->salida,&self->sensor);
  
  //AlarmaSensor_setTipo(alarma,ALARMA_CONTROL);
  LazoControlAlSen_setAdaptadorSalida(alarma,SALIDA_EXCESO);
 // AlarmaSensor_setControlador(alarma,CONTROL_ABSOLUTO);
  
  SensorSimulado_setValue(&self->sensor,100);
  
  LazoControlAlSen_setValor(alarma,150);
  LazoControlAlSen_setHisteresis(alarma,1000); 
  
  SensorSimulado_forzarProcesamiento(&self->sensor); 
  
  if( getPotencia(&self->salida)!=450 )
    result = EXIT_FAILURE;
  else
    result = EXIT_SUCCESS; 
  
  if(result==EXIT_SUCCESS){    
    LazoControlAlSen_setAdaptadorSalida(alarma,SALIDA_DEFECTO);
    SensorSimulado_forzarProcesamiento(&self->sensor);
    if( getPotencia(&self->salida)!=550 )
      result = EXIT_FAILURE;
    else
      result = EXIT_SUCCESS;    
  }
  
  delete(alarma);
  
  return result;
  
}


/*
*/
bool TestAlarmaPorValor_testAlarmaSensor(void * _self){
  struct TestAlarmaPorValor * self = _self;
  struct AlarmaSenConf config;
  bool result;
  struct AlarmaSensor * alarma;
  
  alarma = new(&AlarmaSensor,&config,&self->salida,&self->sensor);
  
  AlarmaSensor_setTipo(alarma,ALARMA_CONTROL);
  AlarmaSensor_setAdaptadorSalida(alarma,SALIDA_EXCESO);
 // AlarmaSensor_setControlador(alarma,CONTROL_ABSOLUTO);
  
  SensorSimulado_setValue(&self->sensor,100);
  
  Alarma_setValor(alarma,150);
  Alarma_setHisteresis(alarma,1000); 
  
  SensorSimulado_forzarProcesamiento(&self->sensor);
  
  if( getPotencia(&self->salida)!=450 )
    result = EXIT_FAILURE;
  else
    result = EXIT_SUCCESS;  
  
  if(result == EXIT_SUCCESS){
    struct RetransmisionConf * retConf = _AlarmaConf_getRetConf(&config);
    AlarmaSensor_setTipo(alarma,ALARMA_RETRANSMISION); 
    _RetransmisionConf_setRetLow(retConf,0); 
    _RetransmisionConf_setRetHi(retConf,1000);
    SensorSimulado_forzarProcesamiento(&self->sensor);
    if( getPotencia(&self->salida)!=100 )
      result = EXIT_FAILURE;
    else
      result = EXIT_SUCCESS;   
  }
  
  delete(alarma);
  
  return result;
  
}

/*
*/
void TestAlarmaPorValor_constructor(void *self,struct AdjuntadorAHilo*adj,ControlConf * conf){
  struct TestAlarmaPorValor * _self = self;
  TestCase_constructor(self);
  
  newAlloced(&_self->sensor,&SensorSimulado,0,NULL,1000,"SEn Sim");
      
  newAlloced(&_self->salida,&SalidaSimulada);
  setConectada(&_self->salida,TRUE);
  //newAlloced(&_self->control,ControlPID,conf,&_self->sensor,&_self->salida,0);
                       
  //tests      
  TESTCASE_ADD_TEST(self,TestAlarmaPorValor_testAlarmaSensor);	 
  TESTCASE_ADD_TEST(self,TestAlarmaPorValor_testLazoControlAlSen);
  TESTCASE_ADD_TEST(self,TestAlarmaPorValor_testLazoControl);
  TESTCASE_ADD_TEST(self,TestAlarmaPorValor_testCntrProp);
  TESTCASE_ADD_TEST(self,TestAlarmaPorValor_testSalidaBloqueada);
  TESTCASE_ADD_TEST(self,TestAlarmaPorValor_testSalidaRetenida);
  TESTCASE_ADD_TEST(self,TestAlarmaPorValor_testSalidaBanda);
}
/**/
void TestAlarmaPorValor_defCtor(void * self,va_list * args){
  TestAlarmaPorValor_constructor(self,va_arg(*args,void*),va_arg(*args,void*));  
}
