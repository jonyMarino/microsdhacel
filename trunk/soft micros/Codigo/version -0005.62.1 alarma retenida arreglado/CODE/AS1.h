/** ###################################################################
**     THIS BEAN MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename  : AS1.H
**     Project   : cntr_26_07
**     Processor : MC9S12GC32CFU16
**     Beantype  : AsynchroSerial
**     Version   : Bean 02.433, Driver 01.17, CPU db: 2.87.392
**     Compiler  : CodeWarrior HC12 C Compiler
**     Date/Time : 23/09/2008, 10:04
**     Abstract  :
**         This bean "AsynchroSerial" implements an asynchronous serial
**         communication. The bean supports different settings of
**         parity, word width, stop-bit and communication speed,
**         user can select interrupt or polling handler.
**         Communication speed can be changed also in runtime.
**         The bean requires one on-chip asynchronous serial channel.
**     Settings  :
**         Serial channel              : SCI
**
**         Protocol
**             Init baud rate          : 9600baud
**             Width                   : 8 bits
**             Stop bits               : 1
**             Parity                  : none
**             Breaks                  : Disabled
**
**         Registers
**             Input buffer            : SCIDRL    [207]
**             Output buffer           : SCIDRL    [207]
**             Control register        : SCICR1    [202]
**             Mode register           : SCICR2    [203]
**             Baud setting reg.       : SCIBD     [200]
**             Special register        : SCISR1    [204]
**
**         Input interrupt
**             Vector name             : Vsci
**             Priority                : 1
**
**         Output interrupt
**             Vector name             : Vsci
**             Priority                : 1
**
**         Used pins:
**         ----------------------------------------------------------
**           Function | On package           |    Name
**         ----------------------------------------------------------
**            Input   |     63               |  PS0_RxD
**            Output  |     64               |  PS1_TxD
**         ----------------------------------------------------------
**
**
**
**     Contents  :
**         RecvChar - byte AS1_RecvChar(AS1_TComData *Chr);
**         SendChar - byte AS1_SendChar(AS1_TComData Chr);
**
**     (c) Copyright UNIS, spol. s r.o. 1997-2007
**     UNIS, spol. s r.o.
**     Jundrovska 33
**     624 00 Brno
**     Czech Republic
**     http      : www.processorexpert.com
**     mail      : info@processorexpert.com
** ###################################################################*/

#ifndef __AS1
#define __AS1

/* MODULE AS1. */

#include "Cpu.h"



#ifndef __BWUserType_AS1_TError
#define __BWUserType_AS1_TError
  typedef union {
    byte err;
    struct {
      bool OverRun  : 1;               /* Overrun error flag */
      bool Framing  : 1;               /* Framing error flag */
      bool Parity   : 1;               /* Parity error flag */
      bool RxBufOvf : 1;               /* Rx buffer full error flag */
      bool Noise    : 1;               /* Noise error flag */
      bool Break    : 1;               /* Break detect */
      bool LINSync  : 1;               /* LIN synchronization error */
      bool BitError  : 1;              /* Bit error flag - mismatch to the expected value happened. */
    } errName;
  } AS1_TError;                        /* Error flags. For languages which don't support bit access is byte access only to error flags possible. */
#endif

#ifndef __BWUserType_AS1_TComData
#define __BWUserType_AS1_TComData
  typedef byte AS1_TComData ;          /* User type for communication. Size of this type depends on the communication data witdh. */
#endif

#pragma DATA_SEG AS1_DATA
#pragma CODE_SEG AS1_CODE



byte AS1_RecvChar(AS1_TComData *Chr);
/*
** ===================================================================
**     Method      :  AS1_RecvChar (bean AsynchroSerial)
**
**     Description :
**         If any data is received, this method returns one
**         character, otherwise it returns an error code (it does
**         not wait for data). This method is enabled only if the
**         receiver property is enabled.
**         [Note:] Because the preferred method to handle error and
**         break exception in the interrupt mode is to use events
**         <OnError> and <OnBreak> the return value ERR_RXEMPTY has
**         higher priority than other error codes. As a consequence
**         the information about an exception in interrupt mode is
**         returned only if there is a valid character ready to be
**         read.
**     Parameters  :
**         NAME            - DESCRIPTION
**       * Chr             - Pointer to a received character
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_RXEMPTY - No data in receiver
**                           ERR_BREAK - Break character is detected
**                           (only when the <Interrupt service>
**                           property is disabled and the <Break
**                           signal> property is enabled)
**                           ERR_COMMON - common error occurred (the
**                           <GetError> method can be used for error
**                           specification)
** ===================================================================
*/

byte AS1_SendChar(AS1_TComData Chr);
/*
** ===================================================================
**     Method      :  AS1_SendChar (bean AsynchroSerial)
**
**     Description :
**         Sends one character to the channel. If the bean is
**         temporarily disabled (Disable method) SendChar method
**         only stores data into an output buffer. In case of a zero
**         output buffer size, only one character can be stored.
**         Enabling the bean (Enable method) starts the transmission
**         of the stored data. This method is available only if the
**         transmitter property is enabled.
**     Parameters  :
**         NAME            - DESCRIPTION
**         Chr             - Character to send
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_TXFULL - Transmitter is full
** ===================================================================
*/

#pragma CODE_SEG __NEAR_SEG NON_BANKED
__interrupt void AS1_Interrupt(void);
#pragma CODE_SEG AS1_CODE
/*
** ===================================================================
**     Method      :  AS1_Interrupt (bean AsynchroSerial)
**
**     Description :
**         The method services the receive interrupt of the selected 
**         peripheral(s) and eventually invokes the bean's event(s).
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/


void AS1_Init(void);
/*
** ===================================================================
**     Method      :  AS1_Init (bean AsynchroSerial)
**
**     Description :
**         Initializes the associated peripheral(s) and internal 
**         variables of the bean. The method is called automatically as a 
**         part of the application initialization code.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/


#pragma CODE_SEG DEFAULT
/* END AS1. */

/*
** ###################################################################
**
**     This file was created by UNIS Processor Expert 2.98 [03.98]
**     for the Freescale HCS12 series of microcontrollers.
**
** ###################################################################
*/

#endif /* ifndef __AS1 */