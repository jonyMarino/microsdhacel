/** ###################################################################
**     THIS BEAN MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename  : Vectors.C
**     Project   : cntr_26_07
**     Processor : MC9S12GC32CFU16
**     Version   : Bean 01.006, Driver 01.19.02, CPU db: 2.87.320
**     Compiler  : Metrowerks HC12 C Compiler
**     Date/Time : 11/10/2007, 10:11
**     Abstract  :
**         This bean "MC9S12GC16_80" implements properties, methods,
**         and events of the CPU.
**     Settings  :
**
**
**     (c) Copyright UNIS, spol. s r.o. 1997-2004
**     UNIS, spol. s r.o.
**     Jundrovska 33
**     624 00 Brno
**     Czech Republic
**     http      : www.processorexpert.com
**     mail      : info@processorexpert.com
** ###################################################################*/


#include "Cpu.h"
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
#include "TI1.h"
#ifdef _PWM
  #include "utils_pwm_timer.h"
#endif
#include "O2.h"
#include "O4.h"
#include "O6.h"
#include "O7.h"
#include "test.h"
#include "In2.h"
#include "In1.h"

#define dummyInterrupt(n) \
__interrupt void Cpu_Interrupt##n(void) \
{                     \
  asm("BGND");        \
}
         
dummyInterrupt(0)
dummyInterrupt(1)
dummyInterrupt(2)
dummyInterrupt(3)
dummyInterrupt(4)
dummyInterrupt(5)
dummyInterrupt(6)
dummyInterrupt(7)
dummyInterrupt(8)
dummyInterrupt(9)
dummyInterrupt(10)
dummyInterrupt(11)
dummyInterrupt(12)
dummyInterrupt(13)
dummyInterrupt(14)
dummyInterrupt(15)
dummyInterrupt(16)
dummyInterrupt(17)
dummyInterrupt(41)
dummyInterrupt(43)
dummyInterrupt(47)
dummyInterrupt(48)
dummyInterrupt(49)
dummyInterrupt(50)
dummyInterrupt(51)
dummyInterrupt(52)
dummyInterrupt(53)
dummyInterrupt(54)
dummyInterrupt(55)
dummyInterrupt(56)


#ifdef _TI2ms
  #include "timer_interrupt_2ms.h"
#endif

#ifdef _RTI
  #include "ManejadorRTI_private.h"
#endif
 
#ifdef _ADC
  #define  Int41 ADC_Interrupt
#else
  #define  Int41 Cpu_Interrupt41
#endif  
				 
#ifdef _COM
  #define  Int43 AS1_Interrupt
#else
  #define  Int43 Cpu_Interrupt43
#endif 	

#ifdef _PWM
  #ifndef _TI7
    #define  Int48 PWM7_Interrupt
  #endif
  #define  Int49 PWM6_Interrupt
  #define  Int50 PWM5_Interrupt
  #define  Int51 PWM4_Interrupt
  #ifndef _TI3
    #define  Int52 PWM3_Interrupt
  #endif
  #ifndef _CAPT2
    #define  Int53 PWM2_Interrupt
  #endif
  #define  Int54 PWM1_Interrupt
  #ifndef _TI
    #define  Int55 PWM0_Interrupt  
  #endif
#endif 

#ifdef _TI
  #define Int55 TI1_Interrupt
#endif 	

#ifdef _TI3
  #define Int52 TI1_Interrupt
#endif 

#ifdef _TI7
    #define Int48 TI1_Interrupt
#elif defined(_TI2ms)
    #define Int48 timer_interrupt_2ms_Interrupt 
#endif

#ifdef _RTI
  #define Int56 ManejadorRTI_onRTIInterrupt		
#else
  #define Int56 Cpu_Interrupt56
#endif	  

#ifdef _CAP
  #include "Cap1.h"
  #define Int47 Cap1_IntOverflow              /* Interrupt no. 47 (Used) - ivVtimovf, address 0xFFDE  */
  #define Int48 Cap1_Interrupt                /* Interrupt no. 48 (Used) - ivVtimch7, address 0xFFE0  */ 
  #define Int53 Cpu_Interrupt53 
#elif defined(_CAPT2)
  #include "CapPT2.h"
  #define Int53 CapPT2_Interrupt
  #define Int47 CapPT2_IntOverflow              /* Interrupt no. 47 (Used) - ivVtimovf, address 0xFFDE  */
#else
  #ifndef Int53 
    #define Int53 Cpu_Interrupt53 
  #endif
  #define Int47 Cpu_Interrupt47
#endif 

#ifndef Int48
  #define Int48 Cpu_Interrupt48
#endif

#ifndef Int49
  #define Int49 Cpu_Interrupt49
#endif

#ifndef Int50
  #define Int50 Cpu_Interrupt50
#endif 

#ifndef Int51
  #define Int51 Cpu_Interrupt51
#endif 

#ifndef Int52
  #define Int52 Cpu_Interrupt52
#endif 

#ifndef Int54
  #define Int54 Cpu_Interrupt54
#endif 
   
#ifndef Int55
  #define Int55 Cpu_Interrupt55
#endif 


typedef void (*near tIsrFunc)(void);
const tIsrFunc _vect[] @0xFF80 = {     /* Interrupt table */
        Cpu_Interrupt,                 /* 0 Default (unused) interrupt, address 0xFF80 */
        Cpu_Interrupt,                 /* 1 Default (unused) interrupt, address 0xFF82 */
        Cpu_Interrupt,                 /* 2 Default (unused) interrupt, address 0xFF84 */
        Cpu_Interrupt,                 /* 3 Default (unused) interrupt, address 0xFF86 */
        Cpu_Interrupt,                 /* 4 Default (unused) interrupt, address 0xFF88 */
        Cpu_Interrupt,                 /* 5 Default (unused) interrupt, address 0xFF8A */
        Cpu_Interrupt,                 /* 6 Default (unused) interrupt, address 0xFF8C */
        Cpu_Interrupt,                 /* 7 Default (unused) interrupt, address 0xFF8E */
        Cpu_Interrupt,                 /* 8 Default (unused) interrupt, address 0xFF90 */
        Cpu_Interrupt,                 /* 9 Default (unused) interrupt, address 0xFF92 */
        Cpu_Interrupt,                 /* 10 Default (unused) interrupt, address 0xFF94 */
        Cpu_Interrupt,                 /* 11 Default (unused) interrupt, address 0xFF96 */
        Cpu_Interrupt,                 /* 12 Default (unused) interrupt, address 0xFF98 */
        Cpu_Interrupt,                 /* 13 Default (unused) interrupt, address 0xFF9A */
        Cpu_Interrupt,                 /* 14 Default (unused) interrupt, address 0xFF9C */
        Cpu_Interrupt,                 /* 15 Default (unused) interrupt, address 0xFF9E */
        Cpu_Interrupt,                 /* 16 Default (unused) interrupt, address 0xFFA0 */
        Cpu_Interrupt,                 /* 17 Default (unused) interrupt, address 0xFFA2 */
        Cpu_Interrupt,                 /* 18 Default (unused) interrupt, address 0xFFA4 */
        Cpu_Interrupt,                 /* 19 Default (unused) interrupt, address 0xFFA6 */
        Cpu_Interrupt,                 /* 20 Default (unused) interrupt, address 0xFFA8 */
        Cpu_Interrupt,                 /* 21 Default (unused) interrupt, address 0xFFAA */
        Cpu_Interrupt,                 /* 22 Default (unused) interrupt, address 0xFFAC */
        Cpu_Interrupt,                 /* 23 Default (unused) interrupt, address 0xFFAE */
        Cpu_Interrupt,                 /* 24 Default (unused) interrupt, address 0xFFB0 */
        Cpu_Interrupt,                 /* 25 Default (unused) interrupt, address 0xFFB2 */
        Cpu_Interrupt,                 /* 26 Default (unused) interrupt, address 0xFFB4 */
        Cpu_Interrupt,                 /* 27 Default (unused) interrupt, address 0xFFB6 */
        Cpu_Interrupt,                 /* 28 Default (unused) interrupt, address 0xFFB8 */
        Cpu_Interrupt,                 /* 29 Default (unused) interrupt, address 0xFFBA */
        Cpu_Interrupt,                 /* 30 Default (unused) interrupt, address 0xFFBC */
        Cpu_Interrupt,                 /* 31 Default (unused) interrupt, address 0xFFBE */
        Cpu_Interrupt,                 /* 32 Default (unused) interrupt, address 0xFFC0 */
        Cpu_Interrupt,                 /* 33 Default (unused) interrupt, address 0xFFC2 */
        Cpu_Interrupt,                 /* 34 Default (unused) interrupt, address 0xFFC4 */
        Cpu_Interrupt,                 /* 35 Default (unused) interrupt, address 0xFFC6 */
        Cpu_Interrupt,                 /* 36 Default (unused) interrupt, address 0xFFC8 */
        Cpu_Interrupt,                 /* 37 Default (unused) interrupt, address 0xFFCA */
        Cpu_Interrupt,                 /* 38 Default (unused) interrupt, address 0xFFCC */
        Cpu_Interrupt,                 /* 39 Default (unused) interrupt, address 0xFFCE */
        Cpu_Interrupt,                 /* 40 Default (unused) interrupt, address 0xFFD0 */
        Int41,                          /* Interrupt no. 41 (Used) - ivVatd0, address 0xFFD2  */
        Cpu_Interrupt,                 /* 42 Default (unused) interrupt, address 0xFFD4 */
        Int43,                 /* Interrupt no. 43 (Used) - ivVsci, address 0xFFD6  */
        Cpu_Interrupt,                 /* 44 Default (unused) interrupt, address 0xFFD8 */
        Cpu_Interrupt,                 /* 45 Default (unused) interrupt, address 0xFFDA */
        Cpu_Interrupt,                 /* 46 Default (unused) interrupt, address 0xFFDC */
        Int47,                 /* 47 Default (unused) interrupt, address 0xFFDE */
        Int48,                 /* 48 Default (unused) interrupt, address 0xFFE0 */
        Int49,                /* Interrupt no. 49 (Used) - ivVtimch6, address 0xFFE2  */
        Int50,                /* Interrupt no. 50 (Used) - ivVtimch5, address 0xFFE4  */
        Int51,                /* Interrupt no. 51 (Used) - ivVtimch4, address 0xFFE6  */
        Int52,                 /* 52 Default (unused) interrupt, address 0xFFE8 */
        Int53,                 /* Interrupt no. 53 (Used) - ivVtimch2, address 0xFFEA  */
        Int54,                 /* Interrupt no. 54 (Used) - ivVtimch1, address 0xFFEC  */
        Int55,                 /* Interrupt no. 55 (Used) - ivVtimch0, address 0xFFEE  */
        Int56,                 /* 56 Default (unused) interrupt, address 0xFFF0 */
        Cpu_Interrupt,                 /* 57 Default (unused) interrupt, address 0xFFF2 */
        Cpu_Interrupt,                 /* 58 Default (unused) interrupt, address 0xFFF4 */
        Cpu_Interrupt,                 /* 59 Default (unused) interrupt, address 0xFFF6 */
        Cpu_Interrupt,                 /* 60 Default (unused) interrupt, address 0xFFF8 */
        _EntryPoint,                   /* Interrupt no. 61 (Used) - ivVcop, address 0xFFFA  */
        Cpu_Interrupt,                 /* 62 Default (unused) interrupt, address 0xFFFC */
        _EntryPoint                    /* Reset vector, address 0xFFFE */
   }; 
/*                                                                                 
** ###################################################################
**
**     This file was created by UNIS Processor Expert 2.95.01 [03.62]
**     for the Freescale HCS12 series of microcontrollers.
**
** ###################################################################
*/
