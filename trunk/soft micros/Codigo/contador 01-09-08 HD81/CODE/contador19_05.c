/** ###################################################################
**     Filename  : contador_28_04.C
**     Project   : contador_28_04
**     Processor : MC9S12GC32CFU16
**     Version   : Driver 01.10
**     Compiler  : Metrowerks HC12 C Compiler
**     Date/Time : 28/04/2006, 08:31
**     Abstract  :
**         Main module. 
**         Here is to be placed user's code.
**     Settings  :
**     Contents  :
**         No public methods
**
**     (c) Copyright UNIS, spol. s r.o. 1997-2004
**     UNIS, spol. s r.o.
**     Jundrovska 33
**     624 00 Brno
**     Czech Republic
**     http      : www.processorexpert.com
**     mail      : info@processorexpert.com
** ###################################################################*/
/* MODULE contador_28_04 */

/* Including used modules for compiling procedure */
#include "Cpu.h"
#include "Events.h"
#include "Display1.h"
#include "Display2.h"
#include "vx1.h"
#include "vx2.h"
#include "bits5ULN.h"
#include "trx.h"
#include "PTSL.h"
#include "PWSN.h"
#include "PUL.h"
#include "AS1.h"
#include "FLASH1.h"
#include "TI2.h"
#include "TI1.h"
#include "WDog1.h"
#include "Rele1.h"
#include "Rele2.h"
#include "Reset.h"
#include "PP4.h"
#include "PP3.h"
#include "DL2.h"
/* Include shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

////////////MY INCLUDES//////////////
#include "Mydefines.h"
#include "boxes.h"
#include "Comunicacion.h"
#include "IFsh10.h"
#include "Masks.h"
////////////////////////////////////////////////////////////////////////////
// VARIABLES EN FLASH	 
////////////////////////////////////////////////////////////////////////////
word CNT1_RTI;								      // contador (10 seg) de RTIs usado para la navegacion
PunteroF PtrTmp;			/* para el manipuleo */
////////////////////////////////////////////////

///////////////// variables externas para el teclado /////////////////////////////
byte	KeyEdge;				// teclas presionada. Reset en main
////////////////////////////////////////////////////////////////////////////////////////

////////////// variables de los displays ///////////////////////////////
byte DotNum[CANTIDAD_DISPLAYS];			/* punto decimal a encender */
unsigned int cont;					//contadores para scrolling
/////////////////////////////////////////////////////////////

/////////////LEDS//////////////////////
extern bool led[2];
///////////////////////////////////
/////////////COMUNICACION///////////////////////
extern bool AS1_Tx;
extern byte msn[16];
extern byte Step;
////////////////////////////////////////////////
extern bool PreVal;
extern long CntRele[2];
bool ActiveSP[2];

void main(void)
{
  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */
  Rele1_PutVal(led[0]=(ModoSetPoint[0]==EXCESO)?0:1);
	Rele2_PutVal(led[1]=(ModoSetPoint[1]==EXCESO)?0:1);
  /*Recuperacion de valores*/
  if (SavedCuenta!=0xFFFFFFFF){
    Cuenta = SavedCuenta;
    ValProc = Cuenta * (FactorEscala[0] / 10000.0); 
  }
  if (SavedPreTotalizador!=0xFFFFFFFF)
    PreTotalizador = SavedPreTotalizador;
  if (Totalizador[0]!=0xFFFFFFFF)
    Totalizador[0] = SavedTotalizador[0];
  if (Totalizador[1]!=0xFFFFFFFF)
    Totalizador[1] = SavedTotalizador[1];
  if (SavedContFlags!=0xFF)
    ContFlags=SavedContFlags;
  if (SavedOverflowFlags!=0xFF)
    OverflowFlags=SavedOverflowFlags;
  /*Espera para asegurarse el encendido satisfactorio*/
  #ifndef TEST_MODE
  (void)TI2_Enable();	 /*Habilitacion de los timers*/
  #endif
  PtrTmp = &B_Intro.DirProc;	
  (*PtrTmp)();
  CNT1_RTI=1500;
  #ifndef TEST_MODE
  while(CNT1_RTI);
  #endif    
  /*Reset de valores guardados en la Flash*/
  IFsh10_DeleteSector((word)&SavedCuenta,(sizeof(long)*4+sizeof(byte)*2)/2);  
  /*Empieza a contar*/
  PreVal= vx1_GetVal();
  (void)TI1_Enable();
  FstTime=TRUE;
  PtrTmp=&B_Principal1.DirProc;		            // Empezar en Principal
/*												 
 *
 * CICLO PRINCIPAL
 *
*/
  for(;;){
    WDog1_Clear();
    #ifdef TEST_MODE
    TI2_OnInterrupt();
    #endif
    /*Entrada a boxes*/
    (*PtrTmp)();            // Funcion para el box correspondiente; llama a Num Handler, TextHandler, etc.	
		/*Lectura*/
		if(!(ContFlags&STOP_MASK)){
	//	  Cpu_DisableInt();
		  ValProc = Cuenta;
	//	  Cpu_EnableInt();
		  ValProc *= (FactorEscala[0] / 10000.0);
		/*Veo El Modo de Contar y mostrar en el display*/ 
		  if(ModoCuenta[0]!=CONTINUE && ModoCuenta2[0]==DOWN){
		    ValProc = SetPoint[1] - ValProc;
		    ActiveSP[0]=ValProc<=SetPoint[0];
		    if(ActiveSP[1]=(ValProc<=0))ValProc=0; 		  
		  }else {
		    ActiveSP[0]=ValProc>=SetPoint[0];
		    ActiveSP[1]=ValProc>=SetPoint[1];
		  }
			ValDisp=ValProc;
		  /*Control*/
		   if(ActiveSP[0] && (!(ContFlags&SP1_MASK))){
		    Rele1_PutVal(led[0]=(ModoSetPoint[0]==EXCESO)?1:0);
		    CntRele[0] = TiempoRele[0]; 
		    ContFlags|=SP1_MASK;
		  }
		  if(ActiveSP[1] && !(ContFlags&SP2_MASK)){
		    Rele2_PutVal(led[1]=(ModoSetPoint[1]==EXCESO)?1:0);
		    if(!(OverflowFlags&OF_TOT2_MASK))
		      Totalizador[1]++;
		    CntRele[1] = TiempoRele[1];
		    ContFlags |= SP2_MASK;
		    switch(ModoCuenta[0]){
		      case STOP:
		              //  ValProc = SetPoint[1];
		                ContFlags|=STOP_MASK;
		  						  break;
		      case AUTO_RESET:
		    					  PreTotalizador+=Cuenta;
	                  Cuenta=0;
	                  ValProc=0;
	                  ContFlags=0;		  						
		  
		    }
		  }
		  
		  if(!(OverflowFlags&OF_TOT1_MASK))
        Totalizador[0] = (PreTotalizador + Cuenta)* (FactorEscala[1] / 10000.0);
		  /*Verifico Over Flows*/
	//	  if(!(OverflowFlags&OF_TOT1_MASK) && Totalizador[0]<0)
	//	    OverflowFlags|=OF_TOT1_MASK;
	//	  if(!(OverflowFlags&OF_TOT2_MASK) && Totalizador[1]<0)
	//	    OverflowFlags|=OF_TOT2_MASK;
		 // if(Cuenta<0 || ValProc<0)
		 //   ContFlags|=STOP_MASK;
		}
		/*Resets*/
		if(!Reset_GetVal())
		  ResetCuenta();
		   		
		if(ModoRele[0]==AUTOMATICO && !CntRele[0]/* && (ContFlags&SP1_MASK)*/){
		  Rele1_PutVal(led[0]=(ModoSetPoint[0]==EXCESO)?0:1);		  
		}
		if(ModoRele[1]==AUTOMATICO && !CntRele[1]/*&& (ContFlags&SP2_MASK)*/){
		  Rele2_PutVal(led[1]=(ModoSetPoint[1]==EXCESO)?0:1);		  
		}
    
		/*Comunicacion */
    if (AS1_Tx==TRUE)						//Hay algo para enviar??
	    AS1_TxChar();						// Enviar
		
    if ( AS1_RecvChar(&msn[Step])==ERR_OK)  //Recibi algo????		
	    AS1_OnRxChar();											// Procesar

    /* veo si vuelvo a la pantalla principal*/
	  if(CNT1_RTI==0 && PtrTmp!=&B_Principal1.DirProc)		// PAsaron 10 segundos fuera de la pantalla principal??
	  { 
	    PtrTmp=&B_Principal1.DirProc;											//Volver a la pantalla principal
	    FstTime=TRUE;
	  }
  }
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/


/* END contador_28_04 */

void ResetCuenta(void){
      PreTotalizador+=Cuenta;
	    Cuenta=0;
	    ValProc=0;
	    ContFlags=0;
	    #ifdef TEST_MODE
      Entries=0;
      PreCuenta=0;
      #endif
	    Rele1_PutVal(led[0]=(ModoSetPoint[0]==EXCESO)?0:1);
	    Rele2_PutVal(led[1]=(ModoSetPoint[1]==EXCESO)?0:1);
  
}

/*
** ###################################################################
**
**     This file was created by UNIS Processor Expert 2.95 [03.62]
**     for the Freescale HCS12 series of microcontrollers.
**
** ###################################################################
*/
