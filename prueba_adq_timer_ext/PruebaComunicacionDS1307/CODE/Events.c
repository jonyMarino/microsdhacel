/** ###################################################################
**     Filename  : Events.C
**     Project   : Project_1
**     Processor : MC9S12GC32CFU16
**     Beantype  : Events
**     Version   : Driver 01.04
**     Compiler  : CodeWarrior HC12 C Compiler
**     Date/Time : 05/05/2009, 05:03 p.m.
**     Abstract  :
**         This is user's event module.
**         Put your event handler code here.
**     Settings  :
**     Contents  :
**         EI2C1_OnRxChar - void EI2C1_OnRxChar(void);
**         EI2C1_OnTxChar - void EI2C1_OnTxChar(void);
**         EI2C1_OnNACK   - void EI2C1_OnNACK(void);
**
**     (c) Copyright UNIS, spol. s r.o. 1997-2007
**     UNIS, spol. s r.o.
**     Jundrovska 33
**     624 00 Brno
**     Czech Republic
**     http      : www.processorexpert.com
**     mail      : info@processorexpert.com
** ###################################################################*/
/* MODULE Events */


#include "Cpu.h"
#include "Events.h"

#pragma CODE_SEG DEFAULT
word contador=0;
/*
** ===================================================================
**     Event       :  EI2C1_OnRxChar (module Events)
**
**     From bean   :  EI2C1 [SW_I2C]
**     Description :
**         Called when a correct character is received. In the SLAVE
**         mode, this event is not called if the bean receives the
**         first byte with slave address and R/W bit.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void EI2C1_OnRxChar(void)
{
  /* Write your code here ... */
 contador++;
}

/*
** ===================================================================
**     Event       :  EI2C1_OnTxChar (module Events)
**
**     From bean   :  EI2C1 [SW_I2C]
**     Description :
**         Called when a correct character is sent. In MASTER mode,
**         this event is not called if the bean sends the first byte
**         with slave address and R/W bit.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void EI2C1_OnTxChar(void)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  EI2C1_OnNACK (module Events)
**
**     From bean   :  EI2C1 [SW_I2C]
**     Description :
**         In the MASTER mode, this event is called when an invalid
**         slaves acknowledgement occurs during communication transfer.
**         If the acknowledge polling is provided (MASTER mode only), i.
**         e., the <Acknowledge polling trials> property value is
**         higher than one, this event is called only when no trial is
**         successful. In the SLAVE mode, this event is called when a
**         master sends an acknowledgement instead of no
**         acknowledgement at the end of the last byte transfer.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void EI2C1_OnNACK(void)
{
  /* Write your code here ... */
}

/* END Events */

/*
** ###################################################################
**
**     This file was created by UNIS Processor Expert 2.98 [03.98]
**     for the Freescale HCS12 series of microcontrollers.
**
** ###################################################################
*/
