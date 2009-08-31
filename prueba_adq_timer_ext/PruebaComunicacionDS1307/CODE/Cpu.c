/** ###################################################################
**     THIS BEAN MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename  : Cpu.C
**     Project   : Project_1
**     Processor : MC9S12GC32CFU16
**     Beantype  : MC9S12GC16_80
**     Version   : Bean 02.001, Driver 02.01, CPU db: 2.87.392
**     Datasheet : 9S12C128DGV1/D V01.05
**     Compiler  : CodeWarrior HC12 C Compiler
**     Date/Time : 05/05/2009, 05:03 p.m.
**     Abstract  :
**         This bean "MC9S12GC16_80" implements properties, methods,
**         and events of the CPU.
**     Settings  :
**
**     Contents  :
**         EnableInt   - void Cpu_EnableInt(void);
**         DisableInt  - void Cpu_DisableInt(void);
**         SetWaitMode - void Cpu_SetWaitMode(void);
**         SetStopMode - void Cpu_SetStopMode(void);
**
**     (c) Copyright UNIS, spol. s r.o. 1997-2007
**     UNIS, spol. s r.o.
**     Jundrovska 33
**     624 00 Brno
**     Czech Republic
**     http      : www.processorexpert.com
**     mail      : info@processorexpert.com
** ###################################################################*/

/* MODULE Cpu. */

#include "EI2C1.h"
#include "Inhr1.h"
#include "Inhr2.h"
#include "Events.h"
#include "Cpu.h"

#define CGM_DELAY  2047UL

#pragma DATA_SEG DEFAULT
#pragma CODE_SEG DEFAULT


/* Global variables */
volatile byte CCR_reg;                 /* Current CCR reegister */
#pragma CODE_SEG __NEAR_SEG NON_BANKED


/*
** ===================================================================
**     Method      :  Cpu_Cpu_Interrupt (bean MC9S12GC16_80)
**
**     Description :
**         The method services unhandled interrupt vectors.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
ISR(Cpu_Interrupt)
{
  asm(BGND);
}


#pragma CODE_SEG DEFAULT

/*
** ===================================================================
**     Method      :  Cpu_DisableInt (bean MC9S12GC16_80)
**
**     Description :
**         Disable maskable interrupts
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
/*
void Cpu_DisableInt(void)

**      This method is implemented as macro in the header module. **
*/

/*
** ===================================================================
**     Method      :  Cpu_EnableInt (bean MC9S12GC16_80)
**
**     Description :
**         Enable maskable interrupts
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
/*
void Cpu_EnableInt(void)

**      This method is implemented as macro in the header module. **
*/

/*
** ===================================================================
**     Method      :  Cpu_SetStopMode (bean MC9S12GC16_80)
**
**     Description :
**         Set low power mode - Stop mode.
**         For more information about the stop mode see
**         documentation of this CPU.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
/*
void Cpu_SetStopMode(void)

**      This method is implemented as macro in the header module. **
*/

/*
** ===================================================================
**     Method      :  Cpu_SetWaitMode (bean MC9S12GC16_80)
**
**     Description :
**         Set low power mode - Wait mode.
**         For more information about the wait mode see
**         documentation of this CPU.
**         Release from Wait mode: Reset or interrupt
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
/*
void Cpu_SetWaitMode(void)

**      This method is implemented as macro in the header module. **
*/

/*
** ===================================================================
**     Method      :  _EntryPoint (bean MC9S12GC16_80)
**
**     Description :
**         Initializes the whole system like timing and so on. At the end 
**         of this function, the C startup is invoked to initialize stack,
**         memory areas and so on.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
extern void _Startup(void);            /* Forward declaration of external startup function declared in file Start12.c */
#pragma CODE_SEG __NEAR_SEG NON_BANKED

#define INITRG_ADR  0x0011             /* Register map position register */

#pragma NO_FRAME
#pragma NO_EXIT
void _EntryPoint(void)
{
  /* ### MC9S12GC16_80 "Cpu" init code ... */
  /*  PE initialization code after reset */
  /* Initialization of the registers INITRG, INITRM, INITEE is done to protect them to be written accidentally later by the application */
  *(byte*)INITRG_ADR = 0;              /* Set the register map position */
  asm("nop");                          /* nop instruction */
  /* INITRM: RAM15=0,RAM14=0,RAM13=1,RAM12=1,RAM11=1,??=0,??=0,RAMHAL=1 */
  setReg8(INITRM, 57);                 /* Set the RAM map position */ 
  /* MISC: ??=0,??=0,??=0,??=0,EXSTR1=1,EXSTR0=1,ROMHM=0,ROMON=1 */
  setReg8(MISC, 13);                    
  /* PEAR: NOACCE=0,??=0,PIPOE=0,NECLK=0,LSTRE=0,RDWE=0,??=0,??=0 */
  setReg8(PEAR, 0);                     
  /*  System clock initialization */
  /* CLKSEL: PLLSEL=0,PSTP=0,SYSWAI=0,ROAWAI=0,PLLWAI=0,CWAI=0,RTIWAI=0,COPWAI=0 */
  setReg8(CLKSEL, 0);                  /* Select clock source from XTAL and set bits in CLKSEL reg. */ 
  /* PLLCTL: CME=1,PLLON=0,AUTO=1,ACQ=1,??=0,PRE=0,PCE=0,SCME=1 */
  setReg8(PLLCTL, 177);                /* Disable the PLL */ 
  /* SYNR: ??=0,??=0,SYN5=0,SYN4=0,SYN3=0,SYN2=0,SYN1=0,SYN0=0 */
  setReg8(SYNR, 0);                    /* Set the multiplier register */ 
  /* REFDV: ??=0,??=0,??=0,??=0,REFDV3=0,REFDV2=0,REFDV1=0,REFDV0=0 */
  setReg8(REFDV, 0);                   /* Set the divider register */ 
  /* PLLCTL: CME=1,PLLON=1,AUTO=1,ACQ=1,??=0,PRE=0,PCE=0,SCME=1 */
  setReg8(PLLCTL, 241);                 
  while(!CRGFLG_LOCK) {                /* Wait until the PLL is within the desired tolerance of the target frequency */
  }
  /* CLKSEL: PLLSEL=1 */
  setReg8Bits(CLKSEL, 128);            /* Select clock source from PLL */ 
  /*** End of PE initialization code after reset ***/
  __asm("jmp _Startup");               /* Jump to C startup code */
}

#pragma CODE_SEG DEFAULT
/*
** ===================================================================
**     Method      :  PE_low_level_init (bean MC9S12GC16_80)
**
**     Description :
**         Initializes beans and provides common register initialization. 
**         The method is called automatically as a part of the 
**         application initialization code.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
void PE_low_level_init(void)
{
  /* Common initialization of the CPU registers */
  /* PIEP: PIEP5=0,PIEP1=0 */
  clrReg8Bits(PIEP, 34);                
  /* PTP: PTP5=1,PTP1=1 */
  setReg8Bits(PTP, 34);                 
  /* PPSP: PPSP5=0,PPSP1=0 */
  clrReg8Bits(PPSP, 34);                
  /* PERP: PERP5=1,PERP1=1 */
  setReg8Bits(PERP, 34);                
  /* DDRP: DDRP5=0,DDRP1=0 */
  clrReg8Bits(DDRP, 34);                
  /* CRGINT: LOCKIE=0,SCMIE=0 */
  clrReg8Bits(CRGINT, 18);              
  /* VREGCTRL: LVIE=0 */
  clrReg8Bits(VREGCTRL, 2);             
  /* COPCTL: RSBCK=0 */
  clrReg8Bits(COPCTL, 64);              
  /* RDRIV: RDPE=0,RDPB=0,RDPA=0 */
  clrReg8Bits(RDRIV, 19);               
  /* RDRAD: RDRAD7=0,RDRAD6=0,RDRAD5=0,RDRAD4=0,RDRAD3=0,RDRAD2=0,RDRAD1=0,RDRAD0=0 */
  setReg8(RDRAD, 0);                    
  /* RDRJ: RDRJ7=0,RDRJ6=0 */
  clrReg8Bits(RDRJ, 192);               
  /* RDRM: RDRM5=0,RDRM4=0,RDRM3=0,RDRM2=0,RDRM1=0,RDRM0=0 */
  clrReg8Bits(RDRM, 63);                
  /* RDRP: RDRP7=0,RDRP6=0,RDRP5=0,RDRP4=0,RDRP3=0,RDRP2=0,RDRP1=0,RDRP0=0 */
  setReg8(RDRP, 0);                     
  /* RDRS: RDRS3=0,RDRS2=0,RDRS1=0,RDRS0=0 */
  clrReg8Bits(RDRS, 15);                
  /* RDRT: RDRT7=0,RDRT6=0,RDRT5=0,RDRT4=0,RDRT3=0,RDRT2=0,RDRT1=0,RDRT0=0 */
  setReg8(RDRT, 0);                     
  /* INTCR: IRQEN=0 */
  clrReg8Bits(INTCR, 64);               
  /* ### MC9S12GC16_80 "Cpu" init code ... */
  /* ### BitIO "Inhr1" init code ... */
  /* ### BitIO "Inhr2" init code ... */
  /* ###  "EI2C1" init code ... */
  EI2C1_Init();
  __EI();                              /* Enable interrupts */
}

/* END Cpu. */

/*
** ###################################################################
**
**     This file was created by UNIS Processor Expert 2.98 [03.98]
**     for the Freescale HCS12 series of microcontrollers.
**
** ###################################################################
*/