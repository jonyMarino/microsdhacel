#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "IPWM.hpp"
#include "PWMHard.hpp"
#include "PWMHard23.hpp"
#include "PWMManager01_45.hpp"
#include "Method.h"
#include "AS1.h"
#include "RamSimulaFlash.h"
#include "ValvulaProporcional.hpp"
#include "cpu.h"
#include "PWM.hpp"
#include "Salida.hpp"
#include "ThreadAttachable.hpp"
#include "PlataformaEmbedded.hpp"

void testPwmHard45 (PWMHard &pwm);
void testPwmHard01 (PWMHard &pwm);
void testValvulaProporcional (ValvulaProporcional &vp);
void print (char *msj);
void retornoDeCarro(void);
char * nroToAscii(unsigned int nro);
unsigned int potencia=700;
unsigned int potencia1=500;

 unsigned int pote;
 
 PlataformaEmbedded 	plataforma;
 
void main(void) {
  /* put your own code here */
  PE_low_level_init();
  
  struct RamSimulaFlash ram;
  struct RamSimulaFlash ram1;
  struct RamSimulaFlash ram2;
  newAlloced(&ram,&RamSimulaFlash);
  newAlloced(&ram1,&RamSimulaFlash);
  newAlloced(&ram2,&RamSimulaFlash);
  
  TConfPWM conf;
  TConfPWM conf1;
  ValvulaProporcional::ConfValvulaProporcional vpConf={
  10,0
  };
  PWMManager01_45::PWMHard01 test(*(struct ManejadorMemoria*)&ram,conf);
  PWMHard23 test1(*(struct ManejadorMemoria*)&ram1,conf1);
  ValvulaProporcional vpTest (*(struct ManejadorMemoria*)&ram2,&vpConf,&PTT,0,&PTT,1);
  //testPwmHard01 (test);
  //testPwmHard45 (test1);
  
 
  _DISABLE_COP();
   	EnableInterrupts;
  
  testValvulaProporcional (vpTest);




  for(;;) {
    _FEED_COP(); /* feeds the dog */
  } /* loop forever */
  /* please make sure that you never leave main */

}


void testValvulaProporcional (ValvulaProporcional &vp){
  char estado;
  
  print("testing... valvula proporcional'\n'");
  vp.setPotencia(potencia1);              //fijo la potencia para verificar el funcionamiento
  print("esperando cierre inicial ...'\n'");
  while(vp.getTimeCloseInit()>0){
    plataforma.mainLoop();
    
  }//espero que termine timeCloseInit
  print("esperando que se detenga ...'\n'");
  //print("potencia actual: '\n'");
  do{                                     //espero hasta que se detenga
     plataforma.mainLoop();
   //print(nroToAscii(vp.getPotencia()));   //presento la potencia actual
   //retornoDeCarro();
   estado=vp.getStatus(); 
  }while(estado!=DETENIDA);
  
  pote= vp.getPotencia();
  if(pote == potencia1)
    print("test ok'\n'");
  else
    print("test fail'\n'");
}

void testPwmHard01 (PWMHard &pwm){

// pwm.setConectada(TRUE);
 pwm.setPeriodo(PWM_200ms);
 pwm.setTipoSalida((TipoSalida)SALIDA_PROPORCIONAL);
 pwm.setPotencia(potencia);
 print("testing... periodo:200ms'\n'");
     
}


void testPwmHard45 (PWMHard &pwm){

// pwm.setConectada(TRUE);
 pwm.setPeriodo(PWM_100ms);
 pwm.setTipoSalida((TipoSalida)SALIDA_PROPORCIONAL);
 pwm.setPotencia(potencia1);
 print("testing... periodo:100ms'\n'");
     
}

void print (char *msj){
  char i;
  bool f=FALSE;  
  AS1_Enable();
  for(i=0;msj[i]!='\0';){
    while (!(SCISR1 & 0x80));  /* wait for output buffer empty */
    if(msj[i] == '\n'){
      SCIDRL = 0x0a;
      while (!(SCISR1 & 0x80));
      SCIDRL = 0xd;
      i++;
    }else{
      SCIDRL = msj[i];
      i++;
    }
    
  }
  AS1_Disable();
}

char * nroToAscii(unsigned int nro){
  char * asciis;
  char cantDig=1;
  unsigned int buffer=nro;
  
  while(1){
   if(nro>10){
     nro=nro/10;
     cantDig++;
   }else
     break;
  }
  asciis[cantDig] ='\0';
  while(cantDig>0){
   if(cantDig==1){
     asciis[(cantDig-1)]= buffer+0x30;
     cantDig--;
   }else{
     asciis[(cantDig-1)] = (buffer%10)+0x30;
     buffer = buffer/10;
     if(buffer<10)
       asciis[(cantDig-1)]= buffer+0x30;
     cantDig--;
  }
  }
  return asciis;
}


void retornoDeCarro(){
  AS1_Enable();
  while (!(SCISR1 & 0x80));              
  SCIDRL = 0xd;     //retorno de carro
  AS1_Disable();
}