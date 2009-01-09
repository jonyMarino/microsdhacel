/** ###################################################################
**     Filename  : _12_10.C
**     Project   : _12_10
**     Processor : MC9S12A256BCPV
**     Version   : Driver 01.10
**     Compiler  : Metrowerks HC12 C Compiler
**     Date/Time : 13/07/2005, 16:06
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
/* MODULE _12_10 */

#include <stdlib.h>
/* Including used modules for compiling procedure */ 
#include "Cpu.h"
#include "Events.h"
#include "Display1.h"
#include "bits5ULN.h"
#include "bits2ULN.h"
#include "trx.h"
#include "PTSL.h"
#include "PWSN.h"
#include "PUL.h"
#include "WDog1.h"
#include "AS1.h"
#include "ADC1.h"
#include "FLASH1.h"
#include "PWM.h"
#include "PWM.h"
#include "TI1.h"
#include "O7.h"
#include "test.h"
#include "In2.h"
#include "In1.h"
#include "PWM4.h"
#include "PWM5.h"
#include "PWM6.h"
#include "O2.h"
#include "O4.h"
#include "O6.h"
#include "ADC.h"
/* Include shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

#include "limits.h"
#include "teclas.h"

//////////////////mis includes//////////////////////////////
#include "Mydefines.h"
#include "boxes.h"
#include "procesamiento.h"
#include "piddefines.h"
#include "paramdefines.h"
#ifdef _COLADA_CALIENTE
  #include "ControlCC.h"
#else
  #include "Control.h"
#endif
#include "SelfTune.h"
#include "Sensores.h"
#include "cnfbox.h"
#include "alarmas.h"
#include "teclas.h"
#include "ValvulaP.h"
#include "Grabacion.h"
#include "Programador.h"

////////////////////////////////////////////////////////////////////////////
// VARIABLES GLOBALES
////////////////////////////////////////////////////////////////////////////
///////VAriables que se ven desde la comunicacion//////
#pragma DATA_SEG MYDATA
int ValFinal[4];
int SetPoint[4];  // Set Point en Ram que se utiliza para el control y los calculos
int duty_ch[8];
word Result[4];						//valor linealizado
#pragma DATA_SEG DEFAULT
////////////////////////////////////////////////////////////////////////////////
bool Flag1;								      // contador (10 seg) de RTIs usado para la navegacion
//////////VARIABLES DE LOS BOXES////////////////
#ifdef adquisidor
int Estado_Adquisicion;
#endif
////////////////////////////////////////////////

////////////MEMORIZACION/////////////////////////
#ifdef adquisidor
extern bool Date_EnUser;
#endif
bool Mostrar_Proc;


////////////////////////////////////////////////

/////////////////FUNCION PRINCIPAL//////////////////
////////////////////////////////////////////////////
////////////////////////////////////////////////////				 

void main(void)
{ 
  static byte i;
  static byte chan;
  
  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/
	
  /* Write your code here */   
    
  Grabacion_Init(); 
  Boxes_Init();
  SENSOR_Init(); // Inicializo Sensor
  	
 #ifdef adquisidor
		TmDt1_Init(); 	 // Inicializacion Fecha y Hora 
		Setup_index();	 // Busca el indice para grabar parametros adquiridos

  	if (PRom[R_adq]==1) {		 // la adquisición quedo en si al apagarse el equipo?								  
  	  Escribir_Powerdown();  // Header que indica que hubo un corte de Energia durante la adquisición
  	  Estado_Adquisicion = 2;// Cartel en HLT (hult) por corte de energia
  	  EscribirParametro(R_adq,0);		 // Poner la adquisición en no
    	}
 #endif
 

  #ifdef _PROGRAMADOR
  Prog_Init();      // Inicializacion del programador  
 	#endif


  CST_OnInit(SENSOR_getProcVal);  // inicializacion de Control con Self Tune
  #ifdef _VP
  VP_Init();
  #endif 
  
  
/////////////////// LOOP CONTINUO /////////////////////////
  for(;;)
  { 
	
	byte tecla=get_key();
  ProcesarBox(tecla);
    
  #ifdef _BUTTON_CHANEL_HMI
  if(tecla=='c')          // Se presionó la tecla de cambio de canal
    Boxes_change_chan();
  #endif
  
  /*  Verifico Funciones de programador*/
  #ifdef _PROGRAMADOR
  if(get_Programa(0)!=CONF_NO_PROGRAMA){
    if(tecla=='s'){
        Prog_Stop();
    } else if(tecla=='c' || !In2_GetVal()){
        Prog_Continue();
    } else if(tecla=='p' || !In1_GetVal()){
        Prog_reset();
    }
  }
  #endif
  
  /*  Flag de Alarma*/
  #if CANTIDAD_SAL_ALARMA>0
  if(tecla=='k')
    AL_SetFlag();
  #endif

  
  WDog1_Clear();					// resetear Watch dog
   
//normalizo para entrar en la tabla de linealizacion. Ajusta cero y offset del ad
//el ajuste de cero es absoluto y el de ganancia porcentual

     
  if (ADC_isread(chan))		// esta el flag de procesar los resultados del AD??
  {
/////////////////// Calculos para los canales leidos//////////  
    long vx=ADC_getVal(chan);
    Result[chan]=Sensores_Procesar(vx,chan); 
		ValFinal[chan]=SENSOR_getProcVal(chan);
		
    Mostrar_Proc=TRUE;  //Mostrar los valores en la pantalla principal (se procesa en Main Handler) 

////////////////// ELECCION DE SET POINTS ////////////////
    #ifndef _PROGRAMADOR
      CNTR_setIntSP(get_SP(chan),chan);
    #else
		  if(get_Programa(chan)!=CONF_NO_PROGRAMA) CNTR_setIntSP(get_SP_Programa(chan),chan) ;
		  else CNTR_setIntSP(get_SP(chan),chan); 
    #endif
		
		#ifdef _SP_EXTERNO
      CNTR_setIntSP(CNTR_getIntSP(0)+ ValFinal[1],0);
    #endif
/////////////////////Calculo de las salidas/////////////////////   

/* Calculo de las salidas. Una a una, sin loop*/ 

	  if(chan==0){
      #ifdef _COLADA_CALIENTE
        CC_ActProcesValue(ValFinal[0],Result[0],0);
      #else  
        CNTR_ActProcVal(ValFinal[0],0); //Obtengo variable PID según corresponda
      #endif   
     
      
     CST_DutyControl(&duty_ch[OUT_CNTR_1],OUT_CNTR_1);	//obtengo duty
	
		 #ifndef _VP
        cntrl_set_salida(duty_ch[OUT_CNTR_1],0);
		 #else
	  	  VP_SetDuty(duty_ch[OUT_CNTR_1]);
		 #endif
			  
     DutyAlarma(ValFinal[0],CNTR_getIntSP(0),CNTR_getValControl(0),&duty_ch[OUT_AL_1],0);
     al_set_salida(duty_ch[OUT_AL_1],0);
         
        
     DutyAlarma(ValFinal[0],CNTR_getIntSP(0),CNTR_getValControl(0),&duty_ch[OUT_AL_2],1);
     al_set_salida(duty_ch[OUT_AL_2],1);
			  
     #ifndef _VP
       DutyAlarma(ValFinal[0],CNTR_getIntSP(0),CNTR_getValControl(0),&duty_ch[OUT_AL_3],2);
       al_set_salida(duty_ch[OUT_AL_3],2); 
		 #endif

     
     
     if(++chan==CANTIDAD_CANALES){
       chan=0;
       AL_clrFlag();              //lo limpio despues de procesar todos los flags
     }
	  }
    
////////////////////////////////////////////////////////////////////////	
  }

////////////////////////Funciones de Tiempo///////////////
  ActualizarTimers(); // se llama a todas las funciones que utilizan el Timer

/////////////// Veo si hubo un overflow en el timer////////////////
    #ifdef adquisidor
    if (TFLG2_TOF==1){	 // el free counter runing dio una vuelta??
    TFLG2_TOF=1; //clear bit  free counter runing
      if (Date_EnUser) // se esta llevando la cuenta de la hora y el dia???
      TmDt1_Inc();   // Llamar a la funcion de tiempo
    }
    #endif
///////// veo si vuelvo a la pantalla principal/////////////
	  if(Flag1)		// PAsaron 10 segundos fuera de la pantalla principal??
	    Box_set_new((PunteroF)&Principal1); 	 
  
  }

  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
}/*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/


/* END _12_10 */

													
/*
** ###################################################################
**
**     This file was created by UNIS Processor Expert 2.95 [03.62]
**     for the Freescale HCS12 series of microcontrollers.
**
** ###################################################################
*/

