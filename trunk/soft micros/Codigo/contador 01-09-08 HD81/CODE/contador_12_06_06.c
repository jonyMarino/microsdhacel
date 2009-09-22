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
#include "Event.h"
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
#include "Rele1.h"
#include "Rele2.h"
#include "Reset.h"
#include "PP4.h"
#include "PP3.h"
#include "FreeCounter.h"
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
#include "FormasConteo.h"
#include "Mensajes.h"
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
word cont;					//contadores para scrolling
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
extern volatile const TAccionSP AccionSPP;
extern volatile const TAccionSP AccionSPA;
bool ActivarSP[2];

extern bool RSave;

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
    Cnt_setCuenta(SavedCuenta);
    ValProc = Cnt_getCuentaEscalada(); 
  }
  if (SavedPreTotalizador!=0xFFFFFFFF)
    PreTotalizador = SavedPreTotalizador;
  if (SavedTotCuenta!=0xFFFFFFFF)
    TotCuenta = SavedTotCuenta;
  if (SavedTotOnSPP!=0xFFFFFFFF)
    TotOnSPP = SavedTotOnSPP;
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
  if(RPM==SI)
    pfContar = FormasConteo_Contador;
  else
    pfContar = FormasConteo_Contador; 
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
  //  WDog1_Clear();
    #ifdef TEST_MODE
    TI2_OnInterrupt();
    #endif
    /*Entrada a boxes*/
    (*PtrTmp)();            // Funcion para el box correspondiente; llama a Num Handler, TextHandler, etc.	
		/*Lectura*/
		if(!(ContFlags&CNT_STOP_MASK)){
		  ValProc = Cnt_getCuentaEscalada(); 
		/*Veo El Modo de Contar y mostrar en el display*/ 
		  if(AccionSPP!=ACCION_CONTINUE && ModoCuenta==MODO_DOWN){
		    ValProc = SP_Principal - ValProc;
		    ActivarSP[1]=(ValProc<=0);
		    if(ActivarSP[1])ValProc=0; 		  
		  }else {
		    ActivarSP[1]=ValProc>=SP_Principal;
		  }
		  
		  
			
			ValDisp=ValProc;

  #ifdef _UN_SET_POINT


		  /*Control*/
//		  if(ActivarSP[0] && (!(ContFlags&SPA_MASK))){
//		    Rele1_PutVal(led[0]=(ModoSetPoint[0]==EXCESO)?1:0);
//		    CntRele[0] = TiempoRele[1]; 
//		    ContFlags|=SPA_MASK;
//		  }
		  if(ActivarSP[1] && !(ContFlags&SPP_MASK)){
 		    Rele1_PutVal(led[0]=(ModoSetPoint[0]==EXCESO)?1:0);
		    if(!(OverflowFlags&OF_TOT2_MASK))
		      TotOnSPP++;
		    CntRele[0] = TiempoRele[1];
		    ContFlags |= SPP_MASK;

          


  #else
  		  /*Control*/
  		  if(ActivarSP[1] && !(ContFlags&SPP_MASK)){
   		    Rele2_PutVal(led[1]=(ModoSetPoint[1]==EXCESO)?1:0);
  		    if(!(ContFlags&TOT_ON_SPP_STOP_MASK) && !(OverflowFlags&OF_TOT2_MASK))
  		      TotOnSPP++;
  		    CntRele[1] = TiempoRele[1];
  		    ContFlags |= SPP_MASK;
  #endif





  		    switch(AccionSPP){

  		      case ACCION_STOP:
  		              //  ValProc = SP_Principal;
  		                ContFlags|=CNT_STOP_MASK;
  		  						  break;
  		      case ACCION_AUTO_RESET:
  		    					  if(!(ContFlags&TOT_CNT_STOP_MASK))
  		    					    PreTotalizador+=Cnt_getCuenta();
  	                  Cnt_setCuenta(0);
  	                  ValProc=0;
  	                  ContFlags=0;		  						
  		  
  		    }
  		  } 
  		  
  		  {
    		  long a=Cnt_getValCmpSPA();
    		  long b=SP_Auxiliar;  
    		  ActivarSP[0]=(a>=b);
  		  }
  		  if(ActivarSP[0] && (!(ContFlags&SPA_MASK))){
  		    Rele1_PutVal(led[0]=(ModoSetPoint[0]==EXCESO)?1:0);
  		    CntRele[0] = TiempoRele[0]; 
  		    ContFlags|=SPA_MASK;
  		    Cnt_OnValEqualToSPA();
  		  }
  		  
  		  if(!(ContFlags&TOT_CNT_STOP_MASK) && !(OverflowFlags&OF_TOT1_MASK))
          TotCuenta = (PreTotalizador + Cnt_getCuenta())* (FactorEscala[1] / 10000.0);
  		  /*Verifico Over Flows*/
  	//	  if(!(OverflowFlags&OF_TOT1_MASK) && TotCuenta<0)
  	//	    OverflowFlags|=OF_TOT1_MASK;
  	//	  if(!(OverflowFlags&OF_TOT2_MASK) && TotOnSPP<0)
  	//	    OverflowFlags|=OF_TOT2_MASK;
  		 // if(Cuenta<0 || ValProc<0)
  		 //   ContFlags|=STOP_MASK;
  		}
  		/*Resets*/
  		if(!Reset_GetVal())
  		  ResetCuenta();
  		   		
  		if(ModoRele[0]==AUTOMATICO && !CntRele[0]/* && (ContFlags&SP1_MASK)*/){
  		  Rele1_PutVal(led[0]=(ModoSetPoint[0]==EXCESO)?0:1);
  		  ContFlags&=~SPA_MASK;		  
  		}
  		if(ModoRele[1]==AUTOMATICO && !CntRele[1]/*&& (ContFlags&SP2_MASK)*/){
  		  Rele2_PutVal(led[1]=(ModoSetPoint[1]==EXCESO)?0:1);		  
  		  ContFlags&=~SPP_MASK;
  		}
		
		/*FLASH*/
		if (RSave){  
      byte err;
      extern word SavedAddress;
      extern word BackupArray[];
      extern bool IndiceFlash[];
      
      Display1_PutVal(0);
      Display2_PutVal(0);
  		err=IFsh10_SetWordsArray(SavedAddress,BackupArray,IndiceFlash);  
      if(!err)
        RSave=FALSE;  
    }			

    /* veo si vuelvo a la pantalla principal*/
	  if(CNT1_RTI==0 && PtrTmp!=&B_Principal1.DirProc)		// PAsaron 10 segundos fuera de la pantalla principal??
	  { 
	    DigitoParpadeante=NO_DIGIT;
	    PtrTmp=&B_Principal1.DirProc;											//Volver a la pantalla principal
	    FstTime=TRUE;
	  }
  }
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
}/*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/


/* END contador_28_04 */

/*
** ###################################################################
**
**     This file was created by UNIS Processor Expert 2.95 [03.62]
**     for the Freescale HCS12 series of microcontrollers.
**
** ###################################################################
*/
