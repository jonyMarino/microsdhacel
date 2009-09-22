
/* MODULE RTI. */

#include "Events.h"
#include "RTI.h"
#include "PWSN.h"
#include "Mydefines.h"
#include "ADC.h"
#include "BoxesStruct.h"
#include "Programador.h"
#pragma DATA_SEG RTI_DATA                                            
#pragma CODE_SEG RTI_CODE                     
#pragma CONST_SEG DEFAULT


/*
** ===================================================================
**     Method      :  Inicialización del timer
**
**     Description :
**         This method is internal. It is used by Processor Expert
**         only.
** ===================================================================
*/
#pragma CODE_SEG __NEAR_SEG NON_BANKED     

void RTI_Init(void){
  /* TSCR1: TEN=0,TSWAI=0,TSFRZ=0,TFFCA=0 */ 
  clrReg8Bits(TSCR1, 240); 
  /* OC7M: OC7M0=0 */
  clrReg8Bits(OC7M, 1);                 
  /* TIOS: IOS0=1 */
  setReg8Bits(TIOS, 1);                 
  /* TCTL2: OM1=0,OL1=0,OM0=0,OL0=0 */
  clrReg8Bits(TCTL2, 3);               
  /* TTOV: TOV0=0 */
  clrReg8Bits(TTOV, 1);                 
  /* TSCR2: TCRE=0,PR2=1,PR1=0,PR0=1 */
  clrSetReg8Bits(TSCR2, 10, 5);         
  /* TFLG1: C7F=1,C6F=1,C5F=1,C4F=1,C3F=1,C2F=1,C1F=1,C0F=1 */
  setReg8(TFLG1, 255);                  
  /* TIE: C0I=1 */
  setReg8Bits(TIE, 1);                  
              
  TC0 = 782;
   /* TSCR1: TEN=1 */
  setReg8Bits(TSCR1, 128);     
}

/*
** ===================================================================
**     Method      :  RTI_Interrupt (bean TimerInt)
**
**     Description :
**         This method is internal. It is used by Processor Expert
**         only.
** ===================================================================
*/

extern void DpyAndSwitch(void);
typedef void (**PunteroF)(void);
byte pwsn=0;
word TimerVal=782;
word CycleCont;
word screen_cont;
word tiempo_refresco_numeroram;
byte Error;
word * datos_grabar;
byte indice_datos[2];
word direccion_grabar;
byte cant_datos_grabar;
word TiempoProgramaCh[CANTIDAD_SAL_CONTROL];
bool PwsnError;
extern int SetPoint[4];
extern dword St_Counter[CANTIDAD_SAL_CONTROL+CANTIDAD_SAL_ALARMA];
extern bool led_c[CANTIDAD_SAL_CONTROL];
extern const int PRom[PARAMETROS];
extern bool save_parametros, save_array;
extern bool RSave, AS1_Tx;
extern byte ASespera;
extern byte Step;
extern word RSave_espera;
extern byte ProgramaActual[CANTIDAD_SAL_CONTROL];
extern int PRam[PARAMETROS];          /* Array for backup data */ 
extern byte IndiceFlash[PARAMETROS/8+1]; /* Indice de parametros modificados*/

ISR(RTI_Interrupt)
{
byte i;
extern unsigned int CNT1_RTI;
extern unsigned int cont; 
extern bool ADfinish;
extern PunteroF PtrTmp;
extern bool FstTime;

TC0 += TimerVal;                    /* Add value corresponding with periode */
TFLG1 = 1;                           /* Reset interrupt request flag */
 
asm{
  cli
  }

  if (TimerVal ==  31280){
  TimerVal =  782; //Next interrupt is 1ms length
  CycleCont +=40;
    
    if (PRom[R_Stn]==Stc)
      St_Counter[0]+=40;  		
    
    for(i=0;i<CANTIDAD_SAL_CONTROL;i++)
      if (PRom[R_Programa+i]!=-1) TiempoProgramaCh[i]+=40;
    
    Display1_PutVal(0);
		if (save_parametros){
      Error=IFsh10_SetWordsArray(FLASH_PARAMETROS_START,(word*)PRam,IndiceFlash,255);  //GRABACION EN LA FLASH	
      FstTime = TRUE;
      save_parametros = FALSE;
    }else{//save_array
      Error=IFsh10_SetWordsArray2(direccion_grabar,datos_grabar,cant_datos_grabar);  //GRABACION EN LA FLASH				
      save_array = FALSE;
    }
    if(Error)
  			led_c[0]=!led_c[0];
  
  
  
  } else { 
  CycleCont++;
		if (PRom[R_Stn]==Stc)
		St_Counter[0]++;


///////////
    if (CycleCont == ADTIME){		// Llego el Contador del Ciclo al tiempo de conversion???
    ADC_Start(0);         //Empieza a hacer los samples
    CycleCont =0;
    }	 else if (CycleCont==(ADTIME-41) && ((save_parametros && (*PtrTmp==MainHandler || *PtrTmp==TitleHandler))|| save_array))
	  TimerVal =  31280; // Next interrupt is 40 ms length
///////////



////////////////////Power Sense/////////////////////// 
    if (PWSN_GetVal() && !PwsnError)		    //Pwsn is high??
    {		 
    pwsn++;									// inc counter
      if (pwsn==30){  // is counter = 30?				
      Cpu_DisableInt();
      #ifdef programador
      
      GuardarPrograma();
      
      #endif
      PwsnError=TRUE;
      Cpu_EnableInt();
      }
    }else pwsn=0;							 // put counter=0
 
/////////////////////////////////////////////////////
 

//////////////Contadores////////////////////////////
  
    if(CNT1_RTI!=0)	        // evito dar la vuelta
    CNT1_RTI--;						// decremento contador de RTI
  
    if(ASespera!=0)	        // evito dar la vuelta
    ASespera--;		        //decremento contador de la comunicacion
	  else if (Step!=0) {
	  Step=0; // error (recibimiento parcial de un mensaje)
	  }
	 
    if (cont!=0)
    cont--;  					      //contador del scroll

	 #ifdef programador
    for(i=0;i<CANTIDAD_SAL_CONTROL;i++){
      if (PRom[R_Programa+i]!=-1) {
        if (TiempoProgramaCh[i]>=1000){
        ActualizarSetPointPrograma(i);
        TiempoProgramaCh[i]-=1000;
        }
      TiempoProgramaCh[i]++;
      }
    }
   #endif
    
    if(screen_cont!=MAIN_TEXT_PERIOD)			//Contador para mostrar diferentes cosas en pantalla
    screen_cont++;
    else screen_cont=0 ;
  
    if(tiempo_refresco_numeroram==REFESH_NUMBER)
    tiempo_refresco_numeroram=0;
    else tiempo_refresco_numeroram++;
 
    if(RSave_espera!=0)RSave_espera--;
    else if (RSave) {
      save_parametros=TRUE;				 //Guardar en la Flash despues de un tiempo
      RSave=FALSE;
      }

  
///////////////////////////////////////////////////////////
  DpyAndSwitch();					// refresh LCD y scan switch

  }
}



#pragma CODE_SEG RTI_CODE                     



/* END RTI. */

/*
** ###################################################################
**
**     This file was created by UNIS Processor Expert 2.95 [03.62]
**     for the Freescale HCS12 series of microcontrollers.
**
** ###################################################################
*/
