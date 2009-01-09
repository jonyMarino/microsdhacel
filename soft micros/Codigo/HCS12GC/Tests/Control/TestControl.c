#include <string.h>
#include <stdlib.h>
#include "TestControl.h"
#include "Timer.h"
#include "FlashBkpEnFlash.h"


void TestControl_defCtor(void * self,va_list * args);
void TestControl_setup(void * self);
bool TestControl_probarRampaDerivada(void *self,int valInicial,int valFinal,int tiempo);


#define CAMBIO1

const struct TTestCase TestControlTable={
  sizeof(struct TestControl),
  TestControl_defCtor,
  NULL,
  NULL,
  TestControl_setup,
  NULL,
};

const void * const TestControl=&TestControlTable; 

extern   struct FlashBkpEnFlash flash;


/*
*/
void TestControl_setup(void * self){
  struct TestControl * _self=self;
  Timer_Restart(&_self->timer);
}
/*
*/
bool TestControl_testOnOff(void * self){
  struct TestControl * _self = self;
  
  set_H_Control(&_self->control,  0);
  PID_setConfSP(&_self->control,  399);
  set_integral(&_self->control,0); 
  set_derivada(&_self->control,0);
  SensorSimulado_setValue(&_self->sensor,400);
  
  while(PromBkp_grabacionOBorradoEnEspera(&flash));
  
  #ifndef CAMBIO1
    Timer_Restart(&_self->timer);  
    while(!Timer_isfinish(&_self->timer)); //espero a que haya una conversion 
  #else
    SensorSimulado_forzarProcesamiento(&_self->sensor);  
  #endif

  if(_getPotencia(&_self->salida)!=0)
    return EXIT_FAILURE;
  
  PID_setConfSP(&_self->control,  400);
  
  while(PromBkp_grabacionOBorradoEnEspera(&flash));
  #ifndef CAMBIO1
    Timer_Restart(&_self->timer);  
    while(!Timer_isfinish(&_self->timer)); //espero a que haya una conversion 
  #else
    SensorSimulado_forzarProcesamiento(&_self->sensor); 
  #endif
    
  if(_getPotencia(&_self->salida)!=1000) 
    return EXIT_FAILURE;
  
      
  PID_setConfSP(&_self->control, 401);
  while(PromBkp_grabacionOBorradoEnEspera(&flash));
  
  #ifndef CAMBIO1
    Timer_Restart(&_self->timer);  
    while(!Timer_isfinish(&_self->timer)); //espero a que haya una conversion 
  #else
    SensorSimulado_forzarProcesamiento(&_self->sensor);  
  #endif

  
 if(_getPotencia(&_self->salida)!=1000) 
    return EXIT_FAILURE;
  return EXIT_SUCCESS;
}
/*
*/
bool TestControl_testProporcional(void * self){
  struct TestControl * _self = self;
  
  set_H_Control(&_self->control,  10);
  PID_setConfSP(&_self->control,  400);
  
  
  set_TipoControl(&_self->control, CNTR_PID);
  SensorSimulado_setValue(&_self->sensor,395); 
 
 while(PromBkp_grabacionOBorradoEnEspera(&flash));
  #ifndef CAMBIO1
    Timer_Restart(&_self->timer);  
    while(!Timer_isfinish(&_self->timer)); //espero a que haya una conversion 
  #else
    SensorSimulado_forzarProcesamiento(&_self->sensor);  
  #endif 
 
 if(_getPotencia(&_self->salida)!=1000) 
    return EXIT_FAILURE;
 
  SensorSimulado_setValue(&_self->sensor,405);

  #ifndef CAMBIO1
    Timer_Restart(&_self->timer);  
    while(!Timer_isfinish(&_self->timer)); //espero a que haya una conversion 
  #else
    SensorSimulado_forzarProcesamiento(&_self->sensor);  
  #endif
 
 if(_getPotencia(&_self->salida)!=0) 
    return EXIT_FAILURE;
 
  SensorSimulado_setValue(&_self->sensor,400);

  #ifndef CAMBIO1
    Timer_Restart(&_self->timer);  
    while(!Timer_isfinish(&_self->timer)); //espero a que haya una conversion 
  #else
    SensorSimulado_forzarProcesamiento(&_self->sensor);  
  #endif
    
  if(_getPotencia(&_self->salida)!=500) 
    return EXIT_FAILURE;

  SensorSimulado_setValue(&_self->sensor,397);
  
  #ifndef CAMBIO1
    Timer_Restart(&_self->timer);  
    while(!Timer_isfinish(&_self->timer)); //espero a que haya una conversion 
  #else
    SensorSimulado_forzarProcesamiento(&_self->sensor);  
  #endif
    
  if(_getPotencia(&_self->salida)!=800) 
    return EXIT_FAILURE;
  return EXIT_SUCCESS;
}
/*
*/
bool TestControl_testRefrigeracion(void * self){
  struct TestControl * _self = self;
  PID_setConfSP(&_self->control,  400);
  
  set_SalControl(&_self->control, _REF);
  SensorSimulado_setValue(&_self->sensor,402);

  while(PromBkp_grabacionOBorradoEnEspera(&flash));
  #ifndef CAMBIO1
    Timer_Restart(&_self->timer);  
    while(!Timer_isfinish(&_self->timer)); //espero a que haya una conversion 
  #else
    SensorSimulado_forzarProcesamiento(&_self->sensor);  
  #endif
    
  if(_getPotencia(&_self->salida)!=700) 
    return EXIT_FAILURE;
  

  SensorSimulado_setValue(&_self->sensor,400);
  
  #ifndef CAMBIO1
    Timer_Restart(&_self->timer);  
    while(!Timer_isfinish(&_self->timer)); //espero a que haya una conversion 
  #else
    SensorSimulado_forzarProcesamiento(&_self->sensor);  
  #endif
  
  if(_getPotencia(&_self->salida)!=500) 
    return EXIT_FAILURE;
  return EXIT_SUCCESS;
}
/*
*/
bool TestControl_testManual(void * self){
  struct TestControl * _self = self;
  
  PID_setConfSP(&_self->control,  400);
  set_SalControl(&_self->control, _MAN);  
  set_PotenciaManual(&_self->control,100);
  SensorSimulado_setValue(&_self->sensor,400);

  while(PromBkp_grabacionOBorradoEnEspera(&flash));
  #ifndef CAMBIO1
    Timer_Restart(&_self->timer);  
    while(!Timer_isfinish(&_self->timer)); //espero a que haya una conversion 
  #else
    SensorSimulado_forzarProcesamiento(&_self->sensor);  
  #endif
  
  if(_getPotencia(&_self->salida)!=100) 
    return EXIT_FAILURE;
  return EXIT_SUCCESS;
  
}
/*
*/
bool TestControl_testIntegral(void * self){
  struct TestControl * _self = self;
  int i;
  int potSalida = 400;
  
  PID_setConfSP(&_self->control,  1000);
  set_H_Control(&_self->control, 1000);
  set_SalControl(&_self->control, _CAL);
  set_integral(&_self->control,100);

  SensorSimulado_setValue(&_self->sensor,1100);
  
  while(PromBkp_grabacionOBorradoEnEspera(&flash));

  
    
  //va bajando el valor de la integral 1 por segundo  hasta que la potencia llega a 0
  for(i=0;i<400;i++){
    SensorSimulado_forzarProcesamiento(&_self->sensor); 
    potSalida--; 
    if(_getPotencia(&_self->salida)!=potSalida) 
      return EXIT_FAILURE;
  }
  
  if(PID_getValControl(&_self->control)!= -500)
    return EXIT_FAILURE;
  
  //No puede pasar de la banda
  for(i=0;i<200;i++){
    SensorSimulado_forzarProcesamiento(&_self->sensor); 
    if(_getPotencia(&_self->salida)!=0) 
      return EXIT_FAILURE;		
    if(PID_getValControl(&_self->control)!= -500)
      return EXIT_FAILURE;  
  }  
  
  return EXIT_SUCCESS;
}
/*
pruebo con una integral de 9999
*/
bool TestControl_testIntegral2(void * self){
  struct TestControl * _self = self;
  ulong i;
  int potSalida = 499;
  ulong acc=0;
  
  PID_setConfSP(&_self->control,  1000);
  set_H_Control(&_self->control, 1000);
  set_SalControl(&_self->control, _CAL);
  set_integral(&_self->control,9999);

  SensorSimulado_setValue(&_self->sensor,1001);
  
  while(PromBkp_grabacionOBorradoEnEspera(&flash));

  
    
  //va bajando el valor de la integral 1 por segundo  hasta que la potencia llega a 0
  for(i=1;i<5000001;i++){
    SensorSimulado_forzarProcesamiento(&_self->sensor); 
    if(_getPotencia(&_self->salida)!=(potSalida-i/9999)) 
      return EXIT_FAILURE;
  }
  
  if(PID_getValControl(&_self->control)!= -500)
    return EXIT_FAILURE;
  
  //No puede pasar de la banda
  for(i=0;i<200;i++){
    SensorSimulado_forzarProcesamiento(&_self->sensor); 
    if(_getPotencia(&_self->salida)!=0) 
      return EXIT_FAILURE;		
    if(PID_getValControl(&_self->control)!= -500)
      return EXIT_FAILURE;  
  }  
  
  return EXIT_SUCCESS;
}
/*
*/
bool TestControl_testDerivada(void * self){
  struct TestControl * _self = self;
  int i;
  int valorPotencia;
  int valorSensor;
  byte err;
  
  PID_setConfSP(&_self->control,  1000);
  set_H_Control(&_self->control, 1000);
  set_SalControl(&_self->control, _CAL);
  set_integral(&_self->control,0); 
  set_derivada(&_self->control,1);
   

  while(PromBkp_grabacionOBorradoEnEspera(&flash));
  
  SensorSimulado_setValue(&_self->sensor,1000);		 //salto 100 para abajo
  SensorSimulado_forzarProcesamiento(&_self->sensor); 
  
  if(_getPotencia(&_self->salida)!= 500 + 100)  /* Pr + Dr */
      return EXIT_FAILURE;
  
  
  // Con el mismo valor la derivada vuelve a cero
  SensorSimulado_forzarProcesamiento(&_self->sensor); 
  
  if(_getPotencia(&_self->salida)!= 500 )  /* Pr + Dr */
      return EXIT_FAILURE;
  
  // El buffer para el filtro queda en 0.
  //Aumento el valor de la derivada para que actue el filtro (KDer * 1/5)
  set_derivada(&_self->control,50);
  while(PromBkp_grabacionOBorradoEnEspera(&flash));
  
  SensorSimulado_setValue(&_self->sensor,1050);		 //salto 50 para arriba
  SensorSimulado_forzarProcesamiento(&_self->sensor);
  
  // Pruebo el comportamiento de un pico en la derivada
  valorPotencia=_getPotencia(&_self->salida);
  for(i=0;i<60;i++){
    int valorPotenciaActual;
    SensorSimulado_forzarProcesamiento(&_self->sensor);
    valorPotenciaActual = _getPotencia(&_self->salida);
    if(valorPotencia > valorPotenciaActual)  /* Pr + Dr */
      return EXIT_FAILURE;
    valorPotencia=valorPotenciaActual; 
  }
  
  //Pruebo si despues de los 60 segundos, la salida es solo el valor de la proporcional
  if(_getPotencia(&_self->salida)!= 450)  /* Pr + Dr */
    return EXIT_FAILURE;
  
  
  for(i=0;i<4;i++){    
    err= TestControl_probarRampaDerivada(self,1000,1000+(i+1)*50,100);
    if(err)
      return EXIT_FAILURE;
  }

}

bool TestControl_probarRampaDerivada(void *self,int valInicial,int valFinal,int tiempo){
  struct TestControl * _self = self;
  int i,valorSensor,Pr,Dr;
  static const int K_DER = 50;
  //Pruebo rampa
  valorSensor = valInicial;
  SensorSimulado_setValue(&_self->sensor,valorSensor);
  //Borro el buffer de derivada
  set_derivada(&_self->control,0);
  while(PromBkp_grabacionOBorradoEnEspera(&flash));
  SensorSimulado_forzarProcesamiento(&_self->sensor);
  //Pongo la derivada en 50
  set_derivada(&_self->control,K_DER);
  while(PromBkp_grabacionOBorradoEnEspera(&flash));
  
  //lo pongo en una rampa 
  for(i=1;i<=tiempo;i++){
    valorSensor= valInicial + (valFinal - valInicial) * i/tiempo;
    SensorSimulado_setValue(&_self->sensor,valorSensor);
    SensorSimulado_forzarProcesamiento(&_self->sensor);
        
  }
  
  Pr =  500 - (valFinal - valInicial);
  Dr =  (valFinal - valInicial)*K_DER/tiempo;
  if( abs(_getPotencia(&_self->salida) - (Pr - Dr)) > 1  )  /* Pr + Dr */
    return EXIT_FAILURE;  
 
  return EXIT_SUCCESS;  
}
  
/*
*/
void TestControl_constructor(void *self,struct AdjuntadorAHilo*adj,ControlConf * conf){
  struct TestControl * _self = self;
  TestCase_constructor(self);
  
  #ifndef CAMBIO1
    newAllocObj(&_self->sensor,SensorSimulado,0,adj,1000,"SEn Sim");
  #else
    newAllocObj(&_self->sensor,SensorSimulado,0,NULL,1000,"SEn Sim");
  #endif
      
  newAllocObj(&_self->salida,SalidaSimulada);
  Salida_conectar(&_self->salida,TRUE);
  newAllocObj(&_self->control,ControlPID,conf,&_self->sensor,&_self->salida,0);
  newAllocObj(&_self->timer,Timer,(ulong)3000); //dura un ciclo de conversion
  //tests 	 
  
  TESTCASE_ADD_TEST(self,TestControl_testDerivada);
  TESTCASE_ADD_TEST(self,TestControl_testIntegral2);
  TESTCASE_ADD_TEST(self,TestControl_testIntegral);
  TESTCASE_ADD_TEST(self,TestControl_testManual);
  TESTCASE_ADD_TEST(self,TestControl_testRefrigeracion);
  TESTCASE_ADD_TEST(self,TestControl_testProporcional);
  TESTCASE_ADD_TEST(self,TestControl_testOnOff);
}
/**/
void TestControl_defCtor(void * self,va_list * args){
  TestControl_constructor(self,va_arg(*args,void*),va_arg(*args,void*));  
}
