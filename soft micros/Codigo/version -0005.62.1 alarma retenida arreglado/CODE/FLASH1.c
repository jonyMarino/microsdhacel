/** ###################################################################
**     THIS BEAN MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename  : FLASH1.C
**     Project   : cntr_26_07
**     Processor : MC9S12GC32CFU16
**     Beantype  : Init_FLASH
**     Version   : Bean 01.143, Driver 01.07, CPU db: 2.87.392
**     Compiler  : CodeWarrior HC12 C Compiler
**     Date/Time : 23/09/2008, 10:04
**     Abstract  :
**          This file implements the FLASH (IntFLASH) 
**          module initialization according to the Peripheral Initialization 
**          Bean settings, and defines interrupt service routines prototypes.
**          Features :
**          Each block in the Flash module can be read, programmed or erased
**          concurrently.
**          Automated program and erase algorithm.
**          Interrupts on Flash command completion and command buffer empty.
**          Fast sector erase and word program operation.
**          2-stage command pipeline
**          Flexible protection scheme for protection against accidental
**          program or erase.
**          Single power supply program and erase.
**          Security feature.
**     Settings  :
**          Bean name                                      : FLASH1
**          Device                                         : IntFLASH
**          Prescaler by 8                                 : no
**          Clock Divider                                  : 41
**          Frequency (150kHz - 200kHz)                    : 190.47 kHz
**          Register Bank Select                           : Bank 0
**          Flash Protection Open                          : yes
**          Protection of Higher Address range             : 16 kB
**          Protection of Lower Address range              : Disabled
**          Interrupt                                      : Vflash
**          Complete interrupt                             : Disabled
**          Empty interrupt                                : Disabled
**          Interrupt priority                             : minimal priority
**          ISR name                                       : 
**          Call Init in CPU init. code                    : yes
**     Contents  :
**         Init - void FLASH1_Init(void);
**
**     (c) Copyright UNIS, spol. s r.o. 1997-2007
**     UNIS, spol. s r.o.
**     Jundrovska 33
**     624 00 Brno
**     Czech Republic
**     http      : www.processorexpert.com
**     mail      : info@processorexpert.com
** ###################################################################*/

/* MODULE FLASH1. */
#include "FLASH1.h"

/*
** ===================================================================
**     Method      :  FLASH1_Init (bean Init_FLASH)
**
**     Description :
**         This method initializes registers of the FLASH module
**         according to this Peripheral Initialization Bean settings.
**         Call this method in user code to initialize the module.
**         By default, the method is called by PE automatically; see
**         "Call Init method" property of the bean for more details.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void FLASH1_Init(void)
{
  /* FCNFG: CBEIE=0,CCIE=0,KEYACC=0,??=0,??=0,??=0,??=0,??=0 */
  setReg8(FCNFG, 0);                   /* Select the flash block #0 */ 
  /* FSTAT: CBEIF=0,CCIF=0,PVIOL=1,ACCERR=1,??=0,BLANK=0,??=0,??=0 */
  setReg8(FSTAT, 48);                  /* Clear error flags PVIOL and ACCERR */ 
  /* FPROT: FPOPEN=1,NV6=1,FPHDIS=0,FPHS1=1,FPHS0=1,FPLDIS=1,FPLS1=1,FPLS0=1 */
  setReg8(FPROT, 223);                 /* Set protection of flash block #0 */ 
  /* FCLKDIV: FDIVLD=0,PRDIV8=0,FDIV5=1,FDIV4=0,FDIV3=1,FDIV2=0,FDIV1=0,FDIV0=0 */
  setReg8(FCLKDIV, 40);                 
}

/* END FLASH1. */

/*
** ###################################################################
**
**     This file was created by UNIS Processor Expert 2.98 [03.98]
**     for the Freescale HCS12 series of microcontrollers.
**
** ###################################################################
*/
