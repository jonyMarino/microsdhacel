#include <string.h>
#include <stdlib.h>
#include "TestRTIEsperaPowUp.h"
#include "Timer.h"
#include "OnPowDown.h"
#include "IO_Map.h"
#include "timer_interrupt.h"
#include "Method.h"
#include "RTIEsperaPowUp.h"
#include "PlataformaEmbedded.h"

void TestRTIEsperaPowUp_defCtor(void * self,va_list * args);


const struct TestCaseClass TestRTIEsperaPowUp={
  &TestCaseClass,
  "TestRTIEsperaPowUp",
  &TestCase,
  sizeof(struct TestRTIEsperaPowUp),
  TestRTIEsperaPowUp_defCtor,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL
};


void TestRTIEsperaPowUp_desconectadoLinea(void *_self){
  struct TestRTIEsperaPowUp * self = _self;
  self->prendido=!self->prendido;  
}
/*
*/
bool TestRTIEsperaPowUp_testReloj(void * _self){
  struct TestRTIEsperaPowUp * self = _self;
  bool result;
  void * timer;
  long msTotales;
  void * onPowDown=OnPowDown_getInstance();
  void * esperaPowUp = RTIEsperaPowUp_getInstance();
  void * conDesconMetodo = new(&Method,TestRTIEsperaPowUp_desconectadoLinea,_self);
  long msTimer= 200123;
  RTIEsperaPowUp_addOnSalirListener(esperaPowUp,conDesconMetodo);
  OnPowDown_addPowDownListener(onPowDown,conDesconMetodo); 
    /* DDRE: BIT2=0 */
  setReg8Bits(DDRE, 4);  // seteo como output
  setReg8Bits(PORTE, 4); // alto = desconectado
  while(self->prendido);
  timer = new(&Timer,msTimer);
  RTIEsperaPowUp_despertar(esperaPowUp);
  while(!Timer_isfinish(timer)){
    
    
    mainLoop(self->ins);
  }
  clrReg8Bits(PORTE, 4); // bajo = conectado
  while(!self->prendido);
  
  msTotales = RTIEsperaPowUp_getSegundosEsperados(esperaPowUp)*1000 + RTIEsperaPowUp_getMSegundosEsperados(esperaPowUp); 
  if( abs(msTotales - msTimer)>500) //error mayor a 500 ms por la entrada del RTI
    return EXIT_FAILURE;
  return EXIT_SUCCESS;
  
}

/*
*/
void TestRTIEsperaPowUp_constructor(void *_self){
  struct TestRTIEsperaPowUp * self = _self;
  TestCase_constructor(self);
  self->prendido = TRUE;
  self->ins = new(&PlataformaEmbedded);
  OnPowDown_enable( OnPowDown_getInstance() );
  //tests 
  TESTCASE_ADD_TEST(_self,TestRTIEsperaPowUp_testReloj);	 
}
/**/
void TestRTIEsperaPowUp_defCtor(void * self,va_list * args){
  TestRTIEsperaPowUp_constructor(self);  
}
