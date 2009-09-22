/** ###################################################################
**     Filename  : Event.C
**     Project   : contador_12_06_06
**     Processor : MC9S12GC16CFU16
**     Beantype  : Events
**     Version   : Driver 01.03
**     Compiler  : Metrowerks HC12 C Compiler
**     Date/Time : 01/09/2008, 11:31 a.m.
**     Abstract  :
**         This is user's event module.
**         Put your event handler code here.
**     Settings  :
**     Contents  :
**         AS1_OnRxChar     - void AS1_OnRxChar(void);
**         AS1_OnTxComplete - void AS1_OnTxComplete(void);
**
**     (c) Copyright UNIS, spol. s r.o. 1997-2004
**     UNIS, spol. s r.o.
**     Jundrovska 33
**     624 00 Brno
**     Czech Republic
**     http      : www.processorexpert.com
**     mail      : info@processorexpert.com
** ###################################################################*/
/* MODULE Event */


#include "Cpu.h"
#include "Event.h"
#include "Events.h"
#include "Comunicacion.h"

/*
** ===================================================================
**     Event       :  AS1_OnRxChar (module Event)
**
**     From bean   :  AS1 [AsynchroSerial]
**     Description :
**         This event is called after a correct character is
**         received. 
**         DMA mode:
**         If DMA controller is available on the selected CPU and
**         the receiver is configured to use DMA controller then
**         this event is disabled. Only OnFullRxBuf method can be
**         used in DMA mode.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void AS1_OnRxChar(void)
{
  /* Write your code here ... */
  AS1_TComData dat;
  //if(AS1_RecvChar(&dat)==ERR_OK)
    AS1_RecvChar(&dat);
    ModBus_Recive(dat);
}

/*
** ===================================================================
**     Event       :  AS1_OnTxComplete (module Event)
**
**     From bean   :  AS1 [AsynchroSerial]
**     Description :
**         This event indicates that the transmitter is finished
**         transmitting all data, preamble, and break characters and
**         is idle. It can be used to determine when it is safe to
**         switch a line driver (e.g. in RS-485 applications). This
**         event is available only if property <Transmitter > is
**         enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void AS1_OnTxComplete(void)
{
  /* Write your code here ... */
  ModBus_Send();
}

/* END Event */

/*
** ###################################################################
**
**     This file was created by UNIS Processor Expert 2.95.01 [03.62]
**     for the Freescale HCS12 series of microcontrollers.
**
** ###################################################################
*/
