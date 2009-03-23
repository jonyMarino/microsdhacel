/** ###################################################################
**     THIS BEAN MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename  : ADC.C
**     Project   : _19_10
**     Processor : MC9S12A256BCPV
**     Beantype  : ADC
**     Version   : Bean 01.279, Driver 01.07, CPU db: 2.87.260
**     Compiler  : Metrowerks HC12 C Compiler
**     Date/Time : 12/08/2005, 03:02 p.m.
**     Abstract  :
**         This device "ADC" implements an A/D converter,
**         its control methods and interrupt/event handling procedure.
**     Settings  :
**         AD control register         : ATD0CTL2    [130]
**         AD control register         : ATD0CTL3    [131]
**         AD control register         : ATD0CTL4    [132]
**         AD control register         : ATD0CTL5    [133]
**         AD control register         : ATD0STAT0   [134]
**         AD control register         : ATD0STAT1   [139]
**         AD control register         : ATD0CTL23   [130]
**         AD control register         : ATD0CTL45   [132]
**         AD control register         : ATD0TEST1   [137]
**         AD control register         : ATD0DIEN    [141]
**         AD result register          : ATD0DR2     [148]
**         AD result register          : ATD0DR3     [150]
**         Interrupt name              : Vatd0
**         Interrupt enable reg.       : ATD0CTL2    [130]
**         Priority                    : 0
**         User handling procedure     : not specified
**         Number of conversions       : 1
**         AD resolution               : 10-bit
**
**         Input pins
**
**              Port name              : AD0
**              Bit number (in port)   : 2
**              Bit mask of the port   : 4
**              Port data register     : PORTAD0     [143]
**
**              Port name              : AD0
**              Bit number (in port)   : 3
**              Bit mask of the port   : 8
**              Port data register     : PORTAD0     [143]
**
**         Initialization:
**              Conversion             : Enabled
**              Event                  : Enabled
**     Contents  :
**         Start - byte ADC_Select(void);
**         Stop  - byte ADC_Stop(void);
**
**     (c) Copyright UNIS, spol. s r.o. 1997-2004
**     UNIS, spol. s r.o.
**     Jundrovska 33
**     624 00 Brno
**     Czech Republic
**     http      : www.processorexpert.com
**     mail      : info@processorexpert.com
** ###################################################################*/


/* MODULE ADC. */

#pragma MESSAGE DISABLE C5703          /* Disable warning C5703 "Parameter is not referenced" */
#pragma MESSAGE DISABLE C4002          /* Disable warning C4002 "Result not used is ignored" */
#pragma MESSAGE DISABLE C12056         /* Disable warning C12056 "SP debug info incorrect because of optimization or inline assembler" */

#include "ADC.h"
#include "Mydefines.h"
#pragma DATA_SEG ADC_DATA                                            
#pragma CODE_SEG ADC_CODE                     
#pragma CONST_SEG DEFAULT            /* Constant section for this module */

#define STOP            0              /* STOP state           */
#define MEASURE         1              /* MESURE state         */
#define CONTINUOUS      2              /* CONTINUOUS state      */
#define SINGLE          3              /* SINGLE state         */

#define PENDIENTE_DIODO -127/100 //-0.127030205 *10
#define ORDENADA_DIODO  2726    //272.6193737 *10

unsigned long int VZ;
//int AD_TA; //temperatura ambiente en rango AD
long ADCTa;		//Temperatura ambiente
bool AD_proc[CANTIDAD_CANALES];
static byte SumChan;                   /* Number of measured channels */
volatile static byte ModeFlg= STOP;          /* Current state of device */
unsigned long int ADC_OutV;
long Vx[CANTIDAD_CANALES];
static byte EnUser;                       /* Set the flag "device enabled" */
static unsigned short ADCont; 
//const unsigned int DIV_TA =  (KNMEDCH * 8.0 * 1024) / KDIV;
const unsigned int KDIV_AD = (KNMEDCH * 8.0 * 1024) / KDIV;
 
/* Array of measured values */

/*
** ===================================================================
**     Method      :  ADC_Interrupt (bean ADC)
**
**     Description :
**         This method is internal. It is used by Processor Expert
**         only.
**
** ===================================================================
*/


#pragma CODE_SEG __NEAR_SEG NON_BANKED     
ISR(ADC_Interrupt)
{ 
  static bool vz;      

  if (ModeFlg == STOP){
    ATDDR0;
    /* Test if the device is in an allowed mode */
    return;                          /* if not, return from the interrupt */ 
  }
  ADC_OutV += ATDDR0;         /* Save measured value */
  ADC_OutV += ATDDR1;         /* Save measured value */
  ADC_OutV += ATDDR2;         /* Save measured value */
  ADC_OutV += ATDDR3;         /* Save measured value */
  ADC_OutV += ATDDR4;         /* Save measured value */
  ADC_OutV += ATDDR5;         /* Save measured value */
  ADC_OutV += ATDDR6;         /* Save measured value */
  ADC_OutV += ATDDR7;         /* Save measured value */
  
  ADCont++;							 // Aumentar Contador
  
  if (ADCont==KNMEDCH){		// ya van KNMEDCH mediciones???
  (void)ADC_Stop();				// Detener el ADC
  ADCont=0;							  // Resetear el contador
  
   
   
   
   if (SumChan<CANTIDAD_CANALES){      // se midio algun canal de proceso ???  
    Vx[SumChan]=ADC_OutV;	 
    AD_proc[SumChan]=TRUE;       //ejecutar los procesos con los valores del AD
   }else  if(SumChan==CANTIDAD_CANALES){							// se midio el canal de Temp. Amb. ???
          //int AD_TA = (long)ADC_OutV/KDIV_AD;        //entre 0 y KDIV(14305)
          ADCTa= ADC_OutV;// (long)AD_TA *PENDIENTE_DIODO + ORDENADA_DIODO; 
   }else if(SumChan==CANTIDAD_CANALES+1)
          VZ=ADC_OutV;	            // Se midio el canal de VZ???
   
   ADC_OutV=0;	                    // resetear el acumulador del canal
    
   
/////////////////////////ELECCION PROXIMO CANAL////////////////////////   
   SumChan++;					 // Seleccionar proximo canal

    if (SumChan>CANTIDAD_CANALES){			 //	 es el prox can mayor que dos???
      SumChan=0;					 // vuelvo a empezar
    }
    if (SumChan==CANTIDAD_CANALES) {		// el prox can es VZ o TA??? 
      if (vz)						  // vz=TRUE?? Leer VZ
        vz=FALSE;					//vz=FALSE
      else{							  //vz=FALSE?? 
        vz=TRUE;					//vz=TRUE
        SumChan++;				//Leer chan TA
      }
    }

    if (SumChan!=0)				// no se vuelve a empezar???
      ADC_Select(SumChan);	// Comenzar mediciones del siguiente canal
  }

}

#pragma CODE_SEG ADC_CODE                     
/*
** ===================================================================
**     Method      :  ADC_isread 
**
**     Description :
**         avisa si el ADC termino de convertir aquel canal.
**     Parameters  : chan  _ Numero de canal
**     Returns     :
**         ---             _ TRUE - Canal listo para leerse
**                         _ FALSE - No se terminaron las mediciones para el canal  
** ===================================================================
*/
bool ADC_isread(byte chan){
  bool read;
  if(chan>= CANTIDAD_CANALES) 
    return FALSE;
  Cpu_DisableInt();
  read=AD_proc[chan]; 
 // AD_proc[chan]=FALSE;
  Cpu_EnableInt();
  return read;  
}

/*
** ===================================================================
**     Method      :  ADC_getTA 
**
**     Description :
**         Devuelve el valor medido para la temperatura ambiente en decimas de grado
**     de grado.
**     Parameters  : None
**     Returns     :
**         ---             _ Valor medido
** ===================================================================
*/
#pragma INLINE
int ADC_getTA(void){
  long ad;
  int TA;
  Cpu_DisableInt();
  ad= ADCTa;
  Cpu_EnableInt();
  TA = (long)ad/KDIV_AD;
  TA =(long)TA *PENDIENTE_DIODO + ORDENADA_DIODO; 
  return TA;  
}

/*int ADC_getADTA(void){
  return AD_TA;  
}
  */
long ADC_getVZ(void){
  long ad;

  Cpu_DisableInt();
  ad= VZ;
  Cpu_EnableInt();  
  return ad;
}

/*
** ===================================================================
**     Method      :  ADC_getVal 
**
**     Description :
**         Devuelve el valor medido para el canal
**     Parameters  : chan  _ Numero de canal
**     Returns     :
**         ---             _ Valor medido
** ===================================================================
*/
int ADC_getVal(byte chan){
  long ad;
  int val;
  
  if(chan>= CANTIDAD_CANALES )
    return 0; //error
  Cpu_DisableInt();
  AD_proc[chan]=FALSE; 
  ad = Vx[chan]; 
  Cpu_EnableInt();
  
  val= ((long)(ad - ADC_getVZ()))/KDIV_AD;	
  return val;  
}

/*
** ===================================================================
**     Method      :  ADC_Start 
**
**     Description :
**         Empieza el conjunto de mediciones de 1 a CANTIDAD_CANALES
**     Parameters  : 
**     Returns     :
**         ---             _ Error
** ===================================================================
*/
byte ADC_Start(void){
  EnUser = TRUE;
  return ADC_Select(0);
}

/*
** ===================================================================
**     Method      :  ADC_Select (bean ADC)
**
**     Description :
**         This method starts continuous conversion of the A/D
**         channels. When each measurement on all channels has
**         finished the <OnEnd > event may be invoked. This method
**         is not available if the <interrupt service> is disabled
**         and the device doesn't support the continuous mode. Note:
**         If time of measurement is too short and the instruction
**         clock is too slow then the conversion complete interrupt
**         and its handler may cause a system overflow.
**     Parameters  : None
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_DISABLED - Device is disabled
**                           ERR_BUSY - A conversion is already
**                           running
** ===================================================================
*/
byte ADC_Select(char chan)
{
  if (ModeFlg != STOP)                 /* Is the device in running mode? */
    return ERR_BUSY;                   /* If yes then error */
  ModeFlg = CONTINUOUS;                /* Set state of device to the continuos mode */
  SumChan=chan;
  /* ATD0CTL5: DJM=1,DSGN=0,SCAN=1,MULT=0,??=0,CC=X,CB=X,CA=X */
   #if CANTIDAD_CANALES == 1
   if (chan == 0) ATDCTL5 = 166;            // vx1         /* Start conversions */
   else if (chan==1) ATDCTL5 = 164;					//Tamb
   else ATDCTL5 = 167;											// vz
   #elif CANTIDAD_CANALES == 2
   if (chan == 0) ATDCTL5 = 166;            // vx1         /* Start conversions */
   else if (chan==1) ATDCTL5 = 165;					//vx2
   else if (chan==2) ATDCTL5 = 164;					//Tamb
   else ATDCTL5 = 167;											// vz
   #elif CANTIDAD_CANALES == 3
   if (chan == 0) ATDCTL5 = 166;            // vx1         /* Start conversions */
   else if (chan==1) ATDCTL5 = 165;					//vx2
   else if (chan==2) ATDCTL5 = 162;					//vx3
   else if (chan==3) ATDCTL5 = 164;					//Tamb
   else ATDCTL5 = 167;											// vz
   #elif CANTIDAD_CANALES == 4
   if (chan == 0) ATDCTL5 = 165;            // vx1         /* Start conversions */
   else if (chan==1) ATDCTL5 = 164;					//vx2
   else if (chan==2) ATDCTL5 = 163;					//vx3
   else if (chan==3) ATDCTL5 = 162;					//vx4
   else if (chan==4) ATDCTL5 = 167;					//Tamb
   else ATDCTL5 = 166;											// vz
   #endif
   
  

  return ERR_OK;                       /* OK */
}

/*
** ===================================================================
**     Method      :  ADC_Stop (bean ADC)
**
**     Description :
**         This method stops the continuous measurement, which had
**         been started by <Start> method, or this method disables a
**         trigger mode which has been enabled by <EnableInt(Chan)
**         Trigger> or <EnableExt(Chan)Trigger> method (if these are
**         supported by HW). This method is available if at least
**         one of <Start>, <EnableInt(Chan)Trigger> or
**         <EnableExt(Chan)Trigger> methods is supported by A/D
**         converter device and it is enabled to be generated.
**     Parameters  : None
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_DISABLED - Device is disabled
**                           ERR_BUSY - A conversion is already
**                           running
** ===================================================================
*/
byte ADC_Stop(void)
{
  if (ModeFlg != CONTINUOUS)           /* Is the device in different mode than "continuos"? */
    return ERR_BUSY;                   /* If yes then error */
  /* ATD0CTL3: ??=0,S8C=0,S4C=0,S2C=0,S1C=1,FIFO=0,FRZ1=1,FRZ0=1 */
  ATDCTL3 = 3;                        /* Abort current measurement */
  ModeFlg = STOP;                      /* Set state of device to the stop mode */
  return ERR_OK;                       /* OK */
}

/*
** ===================================================================
**     Method      :  HWEnDi (bean ADC)
**
**     Description :
**         Enables or disables the peripheral(s) associated with the bean.
**         The method is called automatically as a part of the Enable and 
**         Disable methods and several internal methods.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
static void HWEnDi(void)
{
  volatile byte i;

  if (EnUser) {                        /* Enable device? */
    if (!ATDCTL2_ADPU) {               /* Is device power down? */
      ATDCTL2_ADPU = 1;                /* If yes then device power up */
      for (i=0;i<100;i++) {}           /* Recovery time */
     // ADC_Select(0);
    }
    if (ModeFlg) {                     /* Start or stop measurement? */
      ADCont = 0;
      SumChan = 0;                     /* Set the number of measured channels to 0 */
      /* ATDCTL5: DJM=1,DSGN=0,SCAN=0,MULT=0,??=0,CC=0,CB=1,CA=0 */
      //ADC_Select(0);
      //ATDCTL5 = 130;                   /* Start the conversion */
    }
    else {
      /* ATDCTL3: ??=0,S8C=0,S4C=0,S2C=0,S1C=1,FIFO=0,FRZ1=0,FRZ0=0 */
      ATDCTL3 = 3;                     /* Abort current measurement */
    }
  }
  else {
    ATDCTL3 = 3;                     /* Abort current measurement */
    ModeFlg = STOP;
    ATDCTL2_ADPU = 0;                  /* If no then device power down */
  }
}

/*
** ===================================================================
**     Method      :  AD1_Enable (bean ADC)
**
**     Description :
**         Enables A/D converter bean. <Events> may be generated
**         (<DisableEvent>/<EnableEvent>). If possible, this method
**         switches on A/D converter device, voltage reference, etc.
**     Parameters  : None
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
** ===================================================================
*/
byte ADC_Enable(void)
{
  if (EnUser) {                        /* Is the device enabled by user? */
    return ERR_OK;                     /* If yes then set the flag "device enabled" */
  }
  EnUser = TRUE;                       /* Set the flag "device enabled" */
  HWEnDi();                            /* Enable the device */
  return ERR_OK;                       /* OK */
}

/*
** ===================================================================
**     Method      :  AD1_Disable (bean ADC)
**
**     Description :
**         Disables A/D converter bean. No <events> will be
**         generated. If possible, this method switches off A/D
**         converter device, voltage reference, etc.
**     Parameters  : None
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
** ===================================================================
*/
byte ADC_Disable(void)
{
  if (!EnUser) {                       /* Is the device disabled by user? */
    return ERR_OK;                     /* If yes then OK */
  }
  EnUser = FALSE;                      /* If yes then set the flag "device disabled" */
 // ModeFlg = STOP; 
  HWEnDi();                            /* Enable the device */
  return ERR_OK;                       /* OK */
}


					 
/* END ADC. */

/*
** ###################################################################
**
**     This file was created by UNIS Processor Expert 2.95 [03.62]
**     for the Freescale HCS12 series of microcontrollers.
**
** ###################################################################
*/
