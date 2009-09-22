/** ###################################################################
**     Filename  : Events.C
**     Project   : contador_28_04
**     Processor : MC9S12GC32CFU16
**     Beantype  : Events
**     Version   : Driver 01.03
**     Compiler  : Metrowerks HC12 C Compiler
**     Date/Time : 28/04/2006, 08:51
**     Abstract  :
**         This is user's event module.
**         Put your event handler code here.
**     Settings  :
**     Contents  :
**         TI1_OnInterrupt - void TI1_OnInterrupt(void);
**
**     (c) Copyright UNIS, spol. s r.o. 1997-2004
**     UNIS, spol. s r.o.
**     Jundrovska 33
**     624 00 Brno
**     Czech Republic
**     http      : www.processorexpert.com
**     mail      : info@processorexpert.com
** ###################################################################*/
/* MODULE Events */


#include "Cpu.h"
#include "Event.h"
#include "Events.h"
#include "BoxesStruct.h"
#include "Masks.h"
#include "Mydefines.h"
#include "display.h"
#include "IFsh10.h"
#include "FormasConteo.h"
#include "Comunicacion.h"

#ifdef TEST_CUENTA_CALCULADA
  #undef vx1_GetVal
  #undef vx2_GetVal
  #include "CuentaCalculada.h"
#endif
/*
** ===================================================================
**     Event       :  TI1_OnInterrupt (module Events)
**
**     From bean   :  TI1 [TimerInt]
**     Description :
**         When a timer interrupt occurs this event is called (only
**         when the bean is enabled - "Enable" and the events are
**         enabled - "EnableEvent").
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
bool PreVal;
extern long Cuenta;
extern byte Sensor[1];
extern byte ContFlags;
void (*pfContar)(void);
#ifdef TEST_MODE
long Entries=0;
#endif
void TI1_OnInterrupt(void)
{
 if (!PreVal){
  PreVal=vx1_GetVal();
  if(PreVal)
    (*pfContar)();
 }else PreVal=vx1_GetVal();		
}


/*
** ===================================================================
**     Event       :  TI2_OnInterrupt (module Events)
**
**     From bean   :  TI2 [TimerInt]
**     Description :
**         When a timer interrupt occurs this event is called (only
**         when the bean is enabled - "Enable" and the events are
**         enabled - "EnableEvent").
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
#define SalvarValores() WriteArray((word)&SavedCuenta,0,sizeof(long)*4+sizeof(byte)*2, (word*)&Cuenta)
word screen_cont;
byte DebounceTime;
long CntRele[2];
extern long TotCuenta;
extern long TotOnSPP;
extern const long SavedCuenta;
extern byte OverflowFlags;
extern word CNT1_RTI;
extern word RSave_espera;
extern bool RSave;
extern word SavedAddress,BackupArray[256];
extern word cont;
extern byte IndiceFlash[255/8+1];
extern byte ASespera;
extern byte Step;

void TI2_OnInterrupt(void)
{
  byte i,err;
  static byte pwsn;
  static bool PwsnError;
  extern bool led[2];
  extern bool AS1_Tx;  
 Cpu_EnableInt();
 #ifdef TEST_MODE
 PP4_SetVal();
 #endif 
  if (PWSN_GetVal() && !PwsnError)		    //Pwsn is high??
    {		 
      pwsn++;					// inc counter
      if (pwsn==30){  // is counter = 30?				
        SalvarValores();
//        bits5ULN_PutVal(2); 	 //PTM
//        DL2_PutVal(1);
        PwsnError=TRUE;
      }
    }else pwsn=0;
 
  if(CNT1_RTI)
     CNT1_RTI--;
  
  //////////////Comunicacion////////////////////////////
    
    if(ASespera)	        // evito dar la vuelta
      ASespera--;		        //decremento contador de la comunicacion
	  else if (Step)
	    Step=0; // error (recibimiento parcial de un mensaje)
	  else if (AS1_Tx)
	    ModBus_Send();

  
  if(screen_cont!=MAIN_TEXT_PERIOD)			//Contador para mostrar diferentes cosas en pantalla
    screen_cont++;
  else screen_cont=0 ;
  
  if(Sensor[0]==MICROSWITCH && DebounceTime)
    DebounceTime--;
  
  for(i=0;i<2;i++)
    if(CntRele[i])
		  CntRele[i]--;
  
  if (cont!=0)cont--; 
  
  
  if(RSave_espera!=0)
    RSave_espera--;


  DpyAndSwitch();
  #ifdef TEST_MODE
  PP4_ClrVal();
  #endif

}




/*
** ===================================================================
**     Event       :  WDog1_OnWatchDog (module Events)
**
**     From bean   :  WDog1 [WatchDog]
**     Description :
**         This event is called whenever the watchdog starts "barking"
**         (e.g., after a specified period of the last clearing).
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void WDog1_OnWatchDog(void)
{
  /* Write your code here ... */
  SalvarValores();
}


/* END Events */

/*
** ###################################################################
**
**     This file was created by UNIS Processor Expert 2.95 [03.62]
**     for the Freescale HCS12 series of microcontrollers.
**
** ###################################################################
*/
