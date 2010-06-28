/** ###################################################################
**     THIS BEAN MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename  : Cpu.C
**     Project   : ADC_TEMP_VZ
**     Processor : MC9S08AC128CLK
**     Beantype  : MC9S08AC128_80
**     Version   : Bean 01.001, Driver 01.31, CPU db: 3.00.021
**     Datasheet : MC9S08AC128 Rev. 1 Draft E 08/2007
**     Compiler  : CodeWarrior HCS08 C Compiler
**     Date/Time : 26/11/2008, 14:35
**     Abstract  :
**         This bean "MC9S08AC128_80" contains initialization of the
**         CPU and provides basic methods and events for CPU core
**         settings.
**     Settings  :
**
**     Contents  :
**         EnableInt  - void Cpu_EnableInt(void);
**         DisableInt - void Cpu_DisableInt(void);
**
**     (c) Copyright UNIS, spol. s r.o. 1997-2008
**     UNIS, spol. s r.o.
**     Jundrovska 33
**     624 00 Brno
**     Czech Republic
**     http      : www.processorexpert.com
**     mail      : info@processorexpert.com
** ###################################################################*/

/* MODULE Cpu. */

#pragma MESSAGE DISABLE C4002 /* WARNING C4002: Result not used is ignored */

#include "AD1.h"
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "Events.h"
#include "Cpu.h"


/* Global variables */
volatile byte CCR_reg;                 /* Current CCR register */


/*
** ===================================================================
**     Method      :  Cpu_VicgInterrupt (bean MC9S08AC128_80)
**
**     Description :
**         This ISR services the 'Loss of lock' or the 'Loss of clock' 
**         interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
ISR(Cpu_VicgInterrupt)
{
  asm("LDA _ICGS1");
  ICGS1_ICGIF = 1;                     /* Clear ICG interrupt flag */
}

/*
** ===================================================================
**     Method      :  Cpu_Interrupt (bean MC9S08AC128_80)
**
**     Description :
**         The method services unhandled interrupt vectors.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
ISR(Cpu_Interrupt)
{
}



/*
** ===================================================================
**     Method      :  Cpu_DisableInt (bean MC9S08AC128_80)
**
**     Description :
**         Disables maskable interrupts
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
**     Method      :  Cpu_EnableInt (bean MC9S08AC128_80)
**
**     Description :
**         Enables maskable interrupts
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
**     Method      :  _EntryPoint (bean MC9S08AC128_80)
**
**     Description :
**         Initializes the whole system like timing and so on. At the end 
**         of this function, the C startup is invoked to initialize stack,
**         memory areas and so on.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
extern void _Startup(void);            /* Forward declaration of external startup function declared in file Start12.c */

#pragma NO_FRAME
#pragma NO_EXIT
void _EntryPoint(void)
{
  /* ### MC9S08AC128_80 "Cpu" init code ... */
  /*  PE initialization code after reset */
  /* Common initialization of the write once registers */
  /* SOPT: COPE=0,COPT=1,STOPE=0,??=1,??=0,??=0,??=1,??=1 */
  setReg8(SOPT, 0x53);                  
  /* SPMSC1: LVDF=0,LVDACK=0,LVDIE=0,LVDRE=1,LVDSE=1,LVDE=1,??=0,BGBE=0 */
  setReg8(SPMSC1, 0x1C);                
  /* SPMSC2: LVWF=0,LVWACK=0,LVDV=0,LVWV=0,PPDF=0,PPDACK=0,??=0,PPDC=0 */
  setReg8(SPMSC2, 0x00);                
  /* SMCLK: MPE=0,MCSEL=0 */
  clrReg8Bits(SMCLK, 0x17);             
  /*  System clock initialization */
  /* ICGC1: HGO=0,RANGE=1,REFS=0,CLKS1=1,CLKS0=1,OSCSTEN=1,LOCD=0,??=0 */
  setReg8(ICGC1, 0x7C);                 
  /* ICGC2: LOLRE=0,MFD2=0,MFD1=1,MFD0=1,LOCRE=0,RFD2=0,RFD1=0,RFD0=0 */
  setReg8(ICGC2, 0x30);                 
  ICGTRM = *(unsigned char*)0xFFBE;    /* Initialize ICGTRM register from a non volatile memory */
  while(!ICGS1_LOCK) {                 /* Wait */
  }
  /*** End of PE initialization code after reset ***/

  __asm   jmp _Startup ;               /* Jump to C startup code */

}

/*
** ===================================================================
**     Method      :  PE_low_level_init (bean MC9S08AC128_80)
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
  /* APCTL1: ADPC4=1,ADPC3=1,ADPC2=1 */
  setReg8Bits(APCTL1, 0x1C);            
  /* PTASE: PTASE7=0,PTASE6=0,PTASE5=0,PTASE4=0,PTASE3=0,PTASE2=0,PTASE1=0,PTASE0=0 */
  setReg8(PTASE, 0x00);                 
  /* PTBSE: PTBSE7=0,PTBSE6=0,PTBSE5=0,PTBSE4=0,PTBSE3=0,PTBSE2=0,PTBSE1=0,PTBSE0=0 */
  setReg8(PTBSE, 0x00);                 
  /* PTCSE: PTCSE6=0,PTCSE5=0,PTCSE4=0,PTCSE3=0,PTCSE2=0,PTCSE1=0,PTCSE0=0 */
  clrReg8Bits(PTCSE, 0x7F);             
  /* PTDSE: PTDSE7=0,PTDSE6=0,PTDSE5=0,PTDSE4=0,PTDSE3=0,PTDSE2=0,PTDSE1=0,PTDSE0=0 */
  setReg8(PTDSE, 0x00);                 
  /* PTESE: PTESE7=0,PTESE6=0,PTESE5=0,PTESE4=0,PTESE3=0,PTESE2=0,PTESE1=0,PTESE0=0 */
  setReg8(PTESE, 0x00);                 
  /* PTFSE: PTFSE7=0,PTFSE6=0,PTFSE5=0,PTFSE4=0,PTFSE3=0,PTFSE2=0,PTFSE1=0,PTFSE0=0 */
  setReg8(PTFSE, 0x00);                 
  /* PTGSE: PTGSE6=0,PTGSE5=0,PTGSE4=0,PTGSE3=0,PTGSE2=0,PTGSE1=0,PTGSE0=0 */
  clrReg8Bits(PTGSE, 0x7F);             
  /* PTHSE: PTHSE7=0,PTHSE6=0,PTHSE5=0,PTHSE4=0,PTHSE3=0,PTHSE2=0,PTHSE1=0,PTHSE0=0 */
  setReg8(PTHSE, 0x00);                 
  /* PTJSE: PTJSE7=0,PTJSE6=0,PTJSE5=0,PTJSE4=0,PTJSE3=0,PTJSE2=0,PTJSE1=0,PTJSE0=0 */
  setReg8(PTJSE, 0x00);                 
  /* PTADS: PTADS7=1,PTADS6=1,PTADS5=1,PTADS4=1,PTADS3=1,PTADS2=1,PTADS1=1,PTADS0=1 */
  setReg8(PTADS, 0xFF);                 
  /* PTBDS: PTBDS7=1,PTBDS6=1,PTBDS5=1,PTBDS4=1,PTBDS3=1,PTBDS2=1,PTBDS1=1,PTBDS0=1 */
  setReg8(PTBDS, 0xFF);                 
  /* PTCDS: ??=0,PTCDS6=1,PTCDS5=1,PTCDS4=1,PTCDS3=1,PTCDS2=1,PTCDS1=1,PTCDS0=1 */
  setReg8(PTCDS, 0x7F);                 
  /* PTDDS: PTDDS7=1,PTDDS6=1,PTDDS5=1,PTDDS4=1,PTDDS3=1,PTDDS2=1,PTDDS1=1,PTDDS0=1 */
  setReg8(PTDDS, 0xFF);                 
  /* PTEDS: PTEDS7=1,PTEDS6=1,PTEDS5=1,PTEDS4=1,PTEDS3=1,PTEDS2=1,PTEDS1=1,PTEDS0=1 */
  setReg8(PTEDS, 0xFF);                 
  /* PTFDS: PTFDS7=1,PTFDS6=1,PTFDS5=1,PTFDS4=1,PTFDS3=1,PTFDS2=1,PTFDS1=1,PTFDS0=1 */
  setReg8(PTFDS, 0xFF);                 
  /* PTGDS: ??=0,PTGDS6=1,PTGDS5=1,PTGDS4=1,PTGDS3=1,PTGDS2=1,PTGDS1=1,PTGDS0=1 */
  setReg8(PTGDS, 0x7F);                 
  /* PTHDS: PTHDS7=1,PTHDS6=1,PTHDS5=1,PTHDS4=1,PTHDS3=1,PTHDS2=1,PTHDS1=1,PTHDS0=1 */
  setReg8(PTHDS, 0xFF);                 
  /* PTJDS: PTJDS7=1,PTJDS6=1,PTJDS5=1,PTJDS4=1,PTJDS3=1,PTJDS2=1,PTJDS1=1,PTJDS0=1 */
  setReg8(PTJDS, 0xFF);                 
  /* ### Shared modules init code ... */
  /* ###  "AD1" init code ... */
 // AD1_Init();
  __EI();                              /* Enable interrupts */
}

/* Initialization of the CPU registers in FLASH */

/* NVPROT: FPS6=1,FPS5=1,FPS4=1,FPS3=1,FPS2=1,FPS1=1,FPS0=1,FPOPEN=1 */
const unsigned char NVPROT_INIT @0x0000FFBD = 0xFF;

/* NVOPT: KEYEN1=0,KEYEN0=1,??=1,??=1,??=1,??=1,SEC1=1,SEC0=0 */
const unsigned char NVOPT_INIT @0x0000FFBF = 0x7E;

/* END Cpu. */

/*
** ###################################################################
**
**     This file was created by UNIS Processor Expert 3.03 [04.07]
**     for the Freescale HCS08 series of microcontrollers.
**
** ###################################################################
*/
