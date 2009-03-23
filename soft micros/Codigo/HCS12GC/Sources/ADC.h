/** ###################################################################
**     THIS BEAN MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename  : ADC.H
**     Project   : Metro13_07_05
**     Processor : MC9S12A256BCPV
**     Beantype  : ADC
**     Version   : Bean 01.279, Driver 01.07, CPU db: 2.87.260
**     Compiler  : Metrowerks HC12 C Compiler
**     Date/Time : 09/09/2005, 8:39
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
**         Initialization:
**              Conversion             : Enabled
**              Event                  : Enabled
**         High speed mode
**             Prescaler               : divide-by-32
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

#ifndef __ADC
#define __ADC

/* MODULE ADC. */

/*Include shared modules, which are used for whole project*/
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "Cpu.h"
#include "Mydefines.h"
//#include "AD_Time.h"


#pragma DATA_SEG ADC_DATA                                            
#pragma CODE_SEG ADC_CODE    

#pragma CREATE_ASM_LISTING ON                  

#define ADC_EnableTrigger ADC_EnableExtChanTrigger
/*************PARAMETROS DE LA CONVERSION*****************/
#define MAXAD      10000          //cuentas maximo que salen del ad
#define MAXMV      5000          //decivoltios para esa cuenta
#define MINAD      -2000          //cuentas minimo que salen del ad
#define MINMV      -1000          //decivoltios para esa cuenta

#define BUS_CLOCK 16000000.0		 /*Hz*/
#define ATD_PRESCALER	8					 /*Clock Prescaler (ATDCTL4+1)*2 */
#define ATD_CLOCK  (BUS_CLOCK/ATD_PRESCALER)
#define SAMPLE_TIME 16  /*Sample time en AD's cycle ATDCTL4*/
#define No_CONVERSIONS	8				 /*Numero de conversiones por secuencia ATDCTL3*/
#define No_BITS 10               /*Resolucion en bits de una conversion ATDCTL5*/

#define CONVERSION_TIME  (No_BITS+SAMPLE_TIME+2)/ATD_CLOCK * No_CONVERSIONS	 // 0.000112
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
byte ADC_Enable(void);

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
byte ADC_Disable(void);

/** ###################################################################
**     Abstract  :
**          Este archivo esta pensado para ingresar las constantes que  
**          deben ser usadas para obtener dentro de cierta 
**          cantidad de canales(CANTIDAD_CANALES), un tiempo determinado
**          de conversi�n.
**     Comment   :
**         Usa:
**             CANTIDAD_CANALES (Mydefines.h)
**              AD_2s						(Mydefines.h)
**              AD_1s						(Mydefines.h)
**              AD_500ms				(Mydefines.h)
**              AD_250ms				(Mydefines.h)
**     Contents  :
**         KNMEDCH		- Cantidad de mediciones para un canal
**         KDIV_AD		- Constante por la que se divide cada canal
**         DIV_TA			- Constante por la que se divide la temperatura ambiente
**     Reference  :
**          AD_TIME(en segundos) = CONVERSION_TIME*KNMEDCH*(CANTIDAD_CANALES+1) +0,04 (tiempo de grabacion)
**     mail      : marinon87@hotmail.com
** ###################################################################*/

/* La version de dos canales mide en cada ciclo 3 valores V1V2Vz en uno
y V1V2VTa en otro.

Se hacen  KNMEDCH = 4444 conjuntos de medicion de 8 veces cada valor 
y se hace el promedio.

La entrada es de -10 a +50 mV.
Como el AD trabaja solo con se�ales positivas se le coloca un offset de 0,58V

El maximo de la salida del ad acondicionada es 10000 cuentas para 50 mV

El rango total es 12000 cuentas (10k para positivo y 2k para negativo)
La ind. del inst es:
12000->10000
2000->0
0-> -2000

Si llegara justo al maximo que es para 10 bit = 1024 cuentas. Para el maximo de
 12000 hay que dividir por:

KDIV_AD = (KNMEDCH * 8 * 1024) / 12000 = 3033 

Como no estoy en el maximo, lo ajuste experimentalmente a 2900
Las constantes de medicion de temperatura ambiente se determinaron 
experimentalmente.
*/
#if CANTIDAD_CANALES==2
  #if _TIEMPO_AD_EN_MILISEGUNDOS==2000
    #define KNMEDCH     5714		 /*Numero de secuencias para obteber el resultado final*/

  #elif _TIEMPO_AD_EN_MILISEGUNDOS==1000
    #define KNMEDCH     2857		 /*Numero de secuencias para obteber el resultado final*/
  
  #elif _TIEMPO_AD_EN_MILISEGUNDOS==500
    #define KNMEDCH     1428		 /*Numero de secuencias para obteber el resultado final*/
  
  #elif _TIEMPO_AD_EN_MILISEGUNDOS==250
    #define KNMEDCH     714		 /*Numero de secuencias para obteber el resultado final*/
  
  #endif
  
#elif CANTIDAD_CANALES==1
  #if _TIEMPO_AD_EN_MILISEGUNDOS==2000
    #define KNMEDCH     2142		 /*Numero de secuencias para obteber el resultado final*/

  #elif _TIEMPO_AD_EN_MILISEGUNDOS==1000
  	#define KNMEDCH     4284		 /*Numero de secuencias para obteber el resultado final*/
  
  #elif _TIEMPO_AD_EN_MILISEGUNDOS==500
    #define KNMEDCH     2142		 /*Numero de secuencias para obteber el resultado final*/
  
  #elif _TIEMPO_AD_EN_MILISEGUNDOS==250
    #define KNMEDCH      1071		 /*Numero de secuencias para obteber el resultado final*/
  
  #endif
  
#elif CANTIDAD_CANALES==4
// #define KNMEDCH (_TIEMPO_AD_EN_MILISEGUNDOS-40)/(CANTIDAD_CANALES+1)/CONVERSION_TIME			 /*Numero de secuencias para obteber el resultado final*/
 #if _TIEMPO_AD_EN_MILISEGUNDOS==2000
    #define KNMEDCH    3428 	 /*Numero de secuencias para obteber el resultado final*/

  #elif _TIEMPO_AD_EN_MILISEGUNDOS==1000
  	#define KNMEDCH    1714			 /*Numero de secuencias para obteber el resultado final*/
  
  #elif _TIEMPO_AD_EN_MILISEGUNDOS==500
    #define KNMEDCH     857		 /*Numero de secuencias para obteber el resultado final*/
  
  #elif _TIEMPO_AD_EN_MILISEGUNDOS==250
    #define KNMEDCH     428		 /*Numero de secuencias para obteber el resultado final*/
  
  #endif

#endif   


#define KDIV			14305		 /* Divisor para cada canal*/


#define REAL_AD_TIME  CONVERSION_TIME*KNMEDCH*(CANTIDAD_CANALES+1)  //en segundos
/*
#if ADTIME<(REAL_AD_TIME*1000+40)
  #error El tiempo dado para la conversion es insuficiente
#endif
 */
/*
** ===================================================================
** The EnableTrigger method has been renamed to
** the EnableExtChanTrigger.
** This macro is here to keep project backward compatibility.
** ===================================================================
*/

#define ADC_DisableTrigger ADC_Stop
/*
** ===================================================================
** Now, the Stop method is used for disabling the trigger mode
** instead of the DisableTrigger.
** This macro is here to keep project backward compatibility.
** ===================================================================
*/

#pragma CODE_SEG __NEAR_SEG NON_BANKED     
__interrupt void ADC_Interrupt(void);
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
bool ADC_isread(byte chan);

/*
** ===================================================================
**     Method      :  ADC_getTA 
**
**     Description :
**         Devuelve el valor medido para la temperatura ambiente en decimas
**     de grado.
**     Parameters  : None
**     Returns     :
**         ---             _ Valor medido entre 10000 y -2000
** ===================================================================
*/
int ADC_getVal(byte chan);
/*
** ===================================================================
**     Method      :  ADC_getTA 
**
**     Description :
**         Devuelve el valor medido para la temperatura ambiente
**     Parameters  : None
**     Returns     :
**         ---             _ Valor medido
** ===================================================================
*/
#pragma INLINE
int ADC_getTA(void);
//int ADC_getADTA(void);
/*
** ===================================================================
**     Method      :  ADC_Interrupt (bean ADC)
**
**     Description :
**         This method is internal. It is used by Processor Expert
**         only.
** ===================================================================
*/

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
byte ADC_Start(void);


byte ADC_Select(char chan);
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

byte ADC_Stop(void);
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

void ADC_Init(void);
/*
** ===================================================================
**     Method      :  ADC_Init (bean ADC)
**
**     Description :
**         This method is internal. It is used by Processor Expert
**         only.
** ===================================================================
*/

#pragma CODE_SEG DEFAULT                                   

/* END ADC. */

#endif /* ifndef __ADC */
/*
** ###################################################################
**
**     This file was created by UNIS Processor Expert 2.95 [03.62]
**     for the Freescale HCS12 series of microcontrollers.
**
** ###################################################################
*/