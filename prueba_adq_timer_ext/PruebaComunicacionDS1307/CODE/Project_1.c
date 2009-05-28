/** ###################################################################
**     Filename  : Project_1.C
**     Project   : Project_1
**     Processor : MC9S12GC32CFU16
**     Version   : Driver 01.12
**     Compiler  : CodeWarrior HC12 C Compiler
**     Date/Time : 05/05/2009, 05:03 p.m.
**     Abstract  :
**         Main module.
**         Here is to be placed user's code.
**     Settings  :
**     Contents  :
**         No public methods
**
**     (c) Copyright UNIS, spol. s r.o. 1997-2007
**     UNIS, spol. s r.o.
**     Jundrovska 33
**     624 00 Brno
**     Czech Republic
**     http      : www.processorexpert.com
**     mail      : info@processorexpert.com
** ###################################################################*/
/* MODULE Project_1 */

/* Including used modules for compiling procedure */
#include "Cpu.h"
#include "Events.h"
#include "EI2C1.h"
#include "Inhr1.h"
#include "Inhr2.h"
/* Include shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

 extern word contador;

typedef union{
  struct{
    byte hourLow:4;
    byte hourHigh:2;
    bool amPm:1;
  }bits;
  byte _byte;
}HoursRegister;


typedef union{

  struct{     
    byte segLow:4;
    byte segHigh:3;
    bool CH:1;
  }bits;
  byte _byte;
}segRegister;

typedef union{

  struct{     
    byte addr;
    byte segLow:4;
    byte segHigh:3;
    bool CH:1;
  }bits;
  word _word;
}segRegisterEnvio;

char error_tx;
char error_rx;
char prueba=0;
char control=0x10;   //onda cuadrada(1hz) 
void main(void)
{
  /* Write your local variable definition here */


  HoursRegister h;
  segRegisterEnvio s;
  segRegister sRcv;
  word i;
  word j;
  word b;
  PE_low_level_init();
 // s.bits.CH =0;
  s._word=0;
  s.bits.segLow=2;
  // s.bits.CH =0; 
 error_tx=
          EI2C1_SendBlock(&s,sizeof(s),&b);
          EI2C1_SendStop();
for(;;){
  
  for(i=0;i<10000;i++){
  for(j=0;j<10;j++){
   Delay();
   //s.bits.CH =0;
  }
  }
  EI2C1_SendChar(0);
  EI2C1_SendStop();
  EI2C1_RecvBlock(&sRcv,sizeof(sRcv),&b);
  EI2C1_SendStop();
 
  }
/*  EI2C1_SendChar(2);  // me posiciono en las horas
  EI2C1_RecvChar(&h);
  if(h.bits.amPm){    //Esta configurado como am/pm?
    h.bits.amPm = FALSE;
   // EI2C1_SendChar(h._byte);
  }
  h.bits.hourLow=2;
  EI2C1_SendChar(h._byte);
  */
  //EI2C1_SendStop();


  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
 // PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */

  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END Project_1 */
/*
** ###################################################################
**
**     This file was created by UNIS Processor Expert 2.98 [03.98]
**     for the Freescale HCS12 series of microcontrollers.
**
** ###################################################################
*/
