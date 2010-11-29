/** ###################################################################
**     THIS BEAN MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename  : Vectors.C
**     Project   : ADC_TEMP_VZ
**     Processor : MC9S08AC128CLK
**     Version   : Bean 01.001, Driver 01.31, CPU db: 3.00.021
**     Compiler  : CodeWarrior HCS08 C Compiler
**     Date/Time : 26/11/2008, 14:35
**     Abstract  :
**         This bean "MC9S08AC128_80" contains initialization of the
**         CPU and provides basic methods and events for CPU core
**         settings.
**     Settings  :
**
**
**     (c) Copyright UNIS, spol. s r.o. 1997-2008
**     UNIS, spol. s r.o.
**     Jundrovska 33
**     624 00 Brno
**     Czech Republic
**     http      : www.processorexpert.com
**     mail      : info@processorexpert.com
** ###################################################################*/


#include "Cpu.h"
#include "AD1.h"
extern near void _EntryPoint(void);

void (* near const _vect[])() @0xFF9C = { /* Interrupt vector table */
         Cpu_Interrupt,                /* Int.no.  0 Vspi2 (at FF9C)                 Unassigned */
         Cpu_Interrupt                 /* Int.no.  1 Vtpm3ovf (at FF9E)              Unassigned */
};

void (* near const _vect2[])() @0xFFC0 = { /* Interrupt vector table */
         Cpu_Interrupt,                /* Int.no. 18 Vtpm3ch1 (at FFC0)              Unassigned */
         Cpu_Interrupt,                /* Int.no. 19 Vtpm3ch0 (at FFC2)              Unassigned */
         Cpu_Interrupt,                /* Int.no. 20 Vrti (at FFC4)                  Unassigned */
         Cpu_Interrupt,                /* Int.no. 21 Viic1 (at FFC6)                 Unassigned */
         AD1_Interrupt,                /* Int.no. 22 Vadc1 (at FFC8)                 Used */
         Cpu_Interrupt,                /* Int.no. 23 Vkeyboard1 (at FFCA)            Unassigned */
         Cpu_Interrupt,                /* Int.no. 24 Vsci2tx (at FFCC)               Unassigned */
         Cpu_Interrupt,                /* Int.no. 25 Vsci2rx (at FFCE)               Unassigned */
         Cpu_Interrupt,                /* Int.no. 26 Vsci2err (at FFD0)              Unassigned */
         Cpu_Interrupt,                /* Int.no. 27 Vsci1tx (at FFD2)               Unassigned */
         Cpu_Interrupt,                /* Int.no. 28 Vsci1rx (at FFD4)               Unassigned */
         Cpu_Interrupt,                /* Int.no. 29 Vsci1err (at FFD6)              Unassigned */
         Cpu_Interrupt,                /* Int.no. 30 Vspi1 (at FFD8)                 Unassigned */
         Cpu_Interrupt,                /* Int.no. 31 Vtpm2ovf (at FFDA)              Unassigned */
         Cpu_Interrupt,                /* Int.no. 32 Vtpm2ch5 (at FFDC)              Unassigned */
         Cpu_Interrupt,                /* Int.no. 33 Vtpm2ch4 (at FFDE)              Unassigned */
         Cpu_Interrupt,                /* Int.no. 34 Vtpm2ch3 (at FFE0)              Unassigned */
         Cpu_Interrupt,                /* Int.no. 35 Vtpm2ch2 (at FFE2)              Unassigned */
         Cpu_Interrupt,                /* Int.no. 36 Vtpm2ch1 (at FFE4)              Unassigned */
         Cpu_Interrupt,                /* Int.no. 37 Vtpm2ch0 (at FFE6)              Unassigned */
         Cpu_Interrupt,                /* Int.no. 38 Vtpm1ovf (at FFE8)              Unassigned */
         Cpu_Interrupt,                /* Int.no. 39 Vtpm1ch5 (at FFEA)              Unassigned */
         Cpu_Interrupt,                /* Int.no. 40 Vtpm1ch4 (at FFEC)              Unassigned */
         Cpu_Interrupt,                /* Int.no. 41 Vtpm1ch3 (at FFEE)              Unassigned */
         Cpu_Interrupt,                /* Int.no. 42 Vtpm1ch2 (at FFF0)              Unassigned */
         Cpu_Interrupt,                /* Int.no. 43 Vtpm1ch1 (at FFF2)              Unassigned */
         Cpu_Interrupt,                /* Int.no. 44 Vtpm1ch0 (at FFF4)              Unassigned */
         Cpu_VicgInterrupt,            /* Int.no. 45 Vicg (at FFF6)                  Used */
         Cpu_Interrupt,                /* Int.no. 46 Vlvd (at FFF8)                  Unassigned */
         Cpu_Interrupt,                /* Int.no. 47 Virq (at FFFA)                  Unassigned */
         Cpu_Interrupt,                /* Int.no. 48 Vswi (at FFFC)                  Unassigned */
         _EntryPoint                   /* Int.no. 49 Vreset (at FFFE)                Reset vector */
};

/*
** ###################################################################
**
**     This file was created by UNIS Processor Expert 3.03 [04.07]
**     for the Freescale HCS08 series of microcontrollers.
**
** ###################################################################
*/