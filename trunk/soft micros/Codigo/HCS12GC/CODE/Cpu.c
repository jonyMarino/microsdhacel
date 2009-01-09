/** ###################################################################
**     THIS BEAN MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename  : Cpu.C
**     Project   : cntr_26_07
**     Processor : MC9S12GC32CFU16
**     Beantype  : MC9S12GC16_80
**     Version   : Bean 01.006, Driver 01.19.02, CPU db: 2.87.320
**     Datasheet : 9S12C128DGV1/D V01.05
**     Compiler  : Metrowerks HC12 C Compiler
**     Date/Time : 11/10/2007, 10:11
**     Abstract  :
**         This bean "MC9S12GC16_80" implements properties, methods,
**         and events of the CPU.
**     Settings  :
**
**     Contents  :
**         EnableInt  - void Cpu_EnableInt(void);
**         DisableInt - void Cpu_DisableInt(void);
**
**     (c) Copyright UNIS, spol. s r.o. 1997-2004
**     UNIS, spol. s r.o.
**     Jundrovska 33
**     624 00 Brno
**     Czech Republic
**     http      : www.processorexpert.com
**     mail      : info@processorexpert.com
** ###################################################################*/

/* MODULE Cpu. */

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
#include "O2.h"
#include "O4.h"
#include "O6.h"
#include "O7.h"
#include "test.h"
#include "In2.h"
#include "In1.h"
#include "Events.h"
#include "Cpu.h"

#define CGM_DELAY  2047UL

#pragma DATA_SEG DEFAULT                                  

/* Global variables */
volatile byte CCR_reg;                 /* Current CCR reegister */
byte CpuMode = HIGH_SPEED;             /* Current speed mode */

/*
** ===================================================================
**     Method      :  Cpu_Delay100US (bean MC9S12GC16_80)
**
**     Description :
**         This method realizes software delay. The length of delay
**         is at least 100 microsecond multiply input parameter
**         [us100]. As the delay implementation is not based on real
**         clock, the delay time may be increased by interrupt
**         service routines processed during the delay. The method
**         is independent on selected speed mode.
**     Parameters  :
**         NAME            - DESCRIPTION
**         us100           - Number of 100 us delay repetitions.
**                         - The value of zero results in maximal 
**                           delay of approx. 6.5 seconds.
**     Returns     : Nothing
** ===================================================================
*/
#pragma NO_ENTRY
#pragma NO_EXIT
#pragma MESSAGE DISABLE C5703
void Cpu_Delay100US(word us100)
{
  /* Total irremovable overhead: 13 cycles */
  /* ldd:  2 cycles overhead (load parameter into register) */
  /* jsr:  4 cycles overhead (call this function) */
  /* rts:  7 cycles overhead (return from this function) */

  asm {
    loop:
    /* 100 us delay block begin */

    /*
     * Delay
     *   - requested                  : 100 us @ 16MHz,
     *   - possible                   : 1600 c, 100000 ns
     *   - without removable overhead : 1597 c, 99812.5 ns
     */
    pshd                               /* (2 c: 125 ns) backup D */
    ldd #530                           /* (2 c: 125 ns) number of iterations */
    label0:
    dbne d, label0                     /* (3 c: 187.5 ns) repeat 530x */
    puld                               /* (3 c: 187.5 ns) restore D */

    /* 100 us delay block end */
    dbne d, loop                       /* us100 parameter is passed via D register */
    rts                                /* return from subroutine */
  }
}

#pragma CODE_SEG DEFAULT
/*
** ===================================================================
**     Method      :  Cpu_Interrupt (bean MC9S12GC16_80)
**
**     Description :
**         This method is internal. It is used by Processor Expert
**         only.
** ===================================================================
*/
#pragma CODE_SEG __NEAR_SEG NON_BANKED     

ISR(Cpu_Interrupt)
{
  #ifndef NDEBUG
  asm{
    BGND
  }
  #endif
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
#pragma INLINE
void PLL_Init(void){
      /* PLLCTL: CME=0,PLLON=1,AUTO=1,ACQ=1,??=0,PRE=1,PCE=0,SCME=0 */
      PLLCTL = 116;
      while(!CRGFLG_LOCK) {};              /* Wait */
      CLKSEL_PLLSEL = 1;                   /* Select clock source from PLL */

}

/*
** ===================================================================
**     Method      :  _EntryPoint (bean MC9S12GC16_80)
**
**     Description :
**         This method is internal. It is used by Processor Expert
**         only.
** ===================================================================
*/
extern void _Startup(void);            /* Forward declaration of external startup function declared in file Start12.c */
#pragma CODE_SEG __NEAR_SEG NON_BANKED     

#define INITRG_ADR  0x0011             /* Register map position register */

#pragma NO_FRAME
#pragma NO_EXIT
void _EntryPoint(void)
{
  /*** ### MC9S12GC32CFU16 "Cpu" init code ... ***/
  /*** PE initialization code after reset ***/
  /* Initialization of the registers INITRG, INITRM, INITEE is done to protect them to be written accidentally later by the application */
  *(byte*)INITRG_ADR = 0;              /* Set the register map position */
  asm("nop");                          /* nop instruction */
  INITRM=16;                           /* Set the RAM map position */
  /* MISC: ??=0,??=0,??=0,??=0,EXSTR1=1,EXSTR0=1,ROMHM=0,ROMON=1 */
  MISC=13;
  /* PEAR: NOACCE=0,??=0,PIPOE=0,NECLK=1,LSTRE=0,RDWE=0,??=0,??=0 */
  PEAR=16;
  CLKSEL = 64;                         /* Select clock source from XTAL and set bits in CLKSEL reg. */
  PLLCTL_PLLON = 0;                    /* Disable the PLL */
  SYNR = 1;                           /* Set the multiplier register */
  REFDV = 0;                           /* Set the divider register */
  PLL_Init();
  /*** End of PE initialization code after reset ***/
  __asm("jmp _Startup");               /* Jump to C startup code */
}

#pragma CODE_SEG DEFAULT                                   

/*
** ===================================================================
**     Method      :  PE_low_level_init (bean MC9S12GC16_80)
**
**     Description :
**         This method is internal. It is used by Processor Expert
**         only.
** ===================================================================
*/
void PE_low_level_init(void)
{
  /* Common initialization of the CPU registers */
  /* PORTA: BIT7=0,BIT6=0,BIT5=0,BIT4=0,BIT3=0,BIT2=0,BIT1=0,BIT0=0 */
  setReg8(PORTA, 0);                    
  /* PUCR: PUPEE=0,PUPAE=0 */
  clrReg8Bits(PUCR, 1);                
  /* DDRA: BIT7=1,BIT6=1,BIT5=1,BIT4=1,BIT3=1,BIT2=1,BIT1=1,BIT0=1 */
  setReg8(DDRA, 255);  
  /* PORTB: BIT7=0,BIT6=0,BIT5=0,BIT4=0,BIT3=0,BIT2=0,BIT1=0,BIT0=0 */
  setReg8(PORTB, 0);                    
  /* DDRB: BIT7=1,BIT6=1,BIT5=1,BIT4=1,BIT3=1,BIT2=1,BIT1=1,BIT0=1 */
  setReg8(DDRB, 255);                                                  
  /* PTM: PTM5=0,PTM4=0,PTM3=0,PTM2=0,PTM1=0,PTM0=0 */
  clrReg8Bits(PTM, 63);                 
  /* WOMM: WOMM5=0,WOMM4=0,WOMM3=0,WOMM2=0,WOMM1=0,WOMM0=0 */
  clrReg8Bits(WOMM, 63);                
  /* DDRM: DDRM5=1,DDRM4=1,DDRM3=1,DDRM2=1,DDRM1=1,DDRM0=1 */
  setReg8Bits(DDRM, 63);                
  /* PIEJ: PIEJ7=0,PIEJ6=0 */
  clrReg8Bits(PIEJ, 192);               
  /* PTJ: PTJ7=0,PTJ6=0 */
  clrReg8Bits(PTJ, 192);                
  /* PERJ: PERJ7=0,PERJ6=0 */
  clrReg8Bits(PERJ, 192);               
  /* DDRJ: DDRJ7=1,DDRJ6=1 */
  setReg8Bits(DDRJ, 192);               
  /* PTS: PTS2=0 */
  clrReg8Bits(PTS, 4);                  
  /* WOMS: WOMS2=0 */
  clrReg8Bits(WOMS, 4);                 
  /* DDRS: DDRS2=1 */
  setReg8Bits(DDRS, 4);                 
  /*Agregado*/      
  /* PTT: PTT6=0,PTT5=0,PTT4=0,PTT3=0,PTT2=0,PTT1=0 */
  clrReg8Bits(PTT, 126);                
  /* PERT: PERT3=0,PERT2=0 */
  clrReg8Bits(PERT, 12);                
  /* DDRT: DDRT6=1,DDRT5=1,DDRT4=1,DDRT3=1,DDRT2=1,DDRT1=1 */
  setReg8Bits(DDRT, 126); 
  /*fin Agregado*/              
  /* PEAR: RDWE=0 */
  clrReg8Bits(PEAR, 4);                 
  /* DDRE: BIT2=0 */
  clrReg8Bits(DDRE, 4);                 
  /* COPCTL: WCOP=0,RSBCK=1,CR2=1,CR1=1,CR0=1 */
  clrSetReg8Bits(COPCTL, 128, 71);      
  /* TSCR1: TEN=0,TSWAI=1,TSFRZ=1,TFFCA=0 */
  clrSetReg8Bits(TSCR1, 144, 96);       
  /* OC7M: OC7M0=0 */
  clrReg8Bits(OC7M, 1);                 
  /* TCTL2: OM1=0,OL1=0,OM0=0,OL0=0 */
  clrReg8Bits(TCTL2, 15);               
  /* TCTL1: OM6=0,OL6=0,OM5=0,OL5=0,OM4=0,OL4=0 */
  clrReg8Bits(TCTL1, 63);               
  /* TCTL4: EDG2B=0,EDG2A=0 */
  //clrReg8Bits(TCTL4, 48);                       
  /* TIOS:IOS7=1,IOS6=1,IOS5=1,IOS4=1,IOS2=1,IOS1=1,IOS0=1 */
  setReg8Bits(TIOS, 255);         
  /* TTOV: TOV7=0,TOV6=0,TOV5=0,TOV4=0,TOV3=0,TOV2=0,TOV1=0,TOV0=0 */
  setReg8(TTOV, 0);               
  /* TSCR2: TCRE=0,PR2=1,PR1=0,PR0=1 */
  clrSetReg8Bits(TSCR2, 10, 5);         
  /* TFLG1: C7F=1,C6F=1,C5F=1,C4F=1,C3F=1,C2F=1,C1F=1,C0F=1 */
  setReg8(TFLG1, 255);                  
  /* PTT: PTT6=0,PTT5=0,PTT4=0,PTT1=0 */
  //clrReg8Bits(PTT, 114);                
  /* DDRT: DDRT6=1,DDRT5=1,DDRT4=1,DDRT1=1 */
  //setReg8Bits(DDRT, 114);               
  /* PIEP: PIEP7=0,PIEP5=0,PIEP3=0,PIEP1=0 */
  clrReg8Bits(PIEP, 170);               
  /* PTP: PTP7=0,PTP5=0,PTP3=0,PTP1=0 */
  clrReg8Bits(PTP, 170);                
  /* PERP: PERP7=0,PERP5=0,PERP3=0,PERP1=0 */
  clrReg8Bits(PERP, 170);               
  /* DDRP: DDRP7=1,DDRP5=1,DDRP3=1,DDRP1=1 */
  setReg8Bits(DDRP, 170);               
  /* ATDDIEN: IEN3=1,IEN2=1,IEN1=1,IEN0=1 */
  setReg8Bits(ATDDIEN, 15);             
  /* PTAD: PTAD1=0,PTAD0=0 */
  clrReg8Bits(PTAD, 3);                 
  /* PERAD: PERAD1=0,PERAD0=0 */
  clrReg8Bits(PERAD, 3);                
  /* DDRAD: DDRAD1=1,DDRAD0=1 */
  setReg8Bits(DDRAD, 3);                                
  /* PWMCTL: PSWAI=0,PFRZ=0 */
  clrReg8Bits(PWMCTL, 12);              
  /* PWMSDN: PWMIF=0,PWMIE=0,PWMRSTRT=0,PWMLVL=0,??=0,PWM5IN=0,PWM5INL=0,PWM5ENA=0 */
  setReg8(PWMSDN, 0);                   
  /* ### MC9S12GC16_80 "Cpu" init code ... */
  /* ### ByteIO "Display1" init code ... */
  /* ### BitsIO "bits5ULN" init code ... */
  /* ### BitsIO "bits2ULN" init code ... */
  /* ### BitIO "trx" init code ... */
  /* ### BitsIO "PTSL" init code ... */
  /* ### BitIO "PWSN" init code ... */
  /* ### InputPin "PUL" init code ... */
  /* ###  WatchDog "WDog1" init code ... */
  /* ### Asynchro serial "AS1" init code ... */
  DDRS &= ~1;
  PTS |= 2;
  DDRS |= 2;
  /* ### Init_ADC "ADC1" init code ... */
  ADC1_Init();
  /* ### Init_FLASH "FLASH1" init code ... */
  FLASH1_Init();
  /* ### TimerInt "TI1" init code ... */
  TI1_Init();
  /* TSCR1: TEN=1 TSWAI= 1*/
  setReg8Bits(TSCR1, 192);              
  INTCR_IRQEN = 0;                     /* Disable the IRQ interrupt. IRQ interrupt is enabled after CPU reset by default. */
  __EI();                              /* Enable interrupts */
}

/* END Cpu. */

/*
** ###################################################################
**
**     This file was created by UNIS Processor Expert 2.95.01 [03.62]
**     for the Freescale HCS12 series of microcontrollers.
**
** ###################################################################
*/
