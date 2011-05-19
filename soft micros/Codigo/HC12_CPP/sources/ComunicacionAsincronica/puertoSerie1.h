/** ###################################################################
**     THIS BEAN MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename  : AS1.H
**     Project   : cntr_26_07
**     Processor : MC9S12GC32CFU16
**     Beantype  : AsynchroSerial
**     Version   : Bean 02.285, Driver 01.12, CPU db: 2.87.320
**     Compiler  : Metrowerks HC12 C Compiler
**     Date/Time : 11/10/2007, 10:11
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
**         Used pins                   :
**             ----------------------------------------------------
**               Function | On package |    Name
**             ----------------------------------------------------
**                Input   |     63     |  PS0_RxD0
**                Output  |     64     |  PS1_TxD0
**             ----------------------------------------------------
**
**
**     Contents  :
**         RecvChar - byte AS1_RecvChar(AS1_TComData *Chr);
**         SendChar - byte AS1_SendChar(AS1_TComData Chr);
**
**     (c) Copyright UNIS, spol. s r.o. 1997-2004
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
#include "ModBus.hpp"



#ifndef __BWUserType_tItem
#define __BWUserType_tItem
  typedef struct {                     /* Item of the index table for possible baudrates */
    word div;                          /* divisior */
    byte val;                          /* values of the prescalers */
  } tItem;
#endif
#ifndef __BWUserType_AS1_TError
#define __BWUserType_AS1_TError
typedef union {
  byte err;
  struct {
    bool OverRun  : 1;                 /* OverRun error flag */
    bool Framing  : 1;                 /* Framing error flag */
    bool Parity   : 1;                 /* Parity error flag */
    bool RxBufOvf : 1;                 /* Rx buffer full error flag */
    bool Noise    : 1;                 /* Noise error flag */
    bool Break    : 1;                 /* Break detect */
  }errName;
} AS1_TError;
#endif

#ifndef __BWUserType_AS1_TComData
#define __BWUserType_AS1_TComData
  typedef byte AS1_TComData ;          /* User type for communication. Size of this type depends on the communication data witdh. */
#endif

#pragma DATA_SEG AS1_DATA                                            
#pragma CODE_SEG AS1_CODE                     

byte AS1_Enable(void);
/*
** ===================================================================
**     Method      :  AS1_Enable (bean AsynchroSerial)
**
**     Description :
**         Enables the bean - it starts the send and receive
**         functions. Events may be generated
**         ("DisableEvent"/"EnableEvent").
**     Parameters  : None
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
** ===================================================================
*/

byte AS1_Disable(void);
/*
** ===================================================================
**     Method      :  AS1_Disable (bean AsynchroSerial)
**
**     Description :
**         Disables the bean - it stops the send and receive
**         functions. No events will be generated.
**     Parameters  : None
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
** ===================================================================
*/

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
**         DMA mode:
**         If DMA controller is available on the selected CPU and
**         the receiver is configured to use DMA controller then
**         this method only sets the selected DMA channel. Then the
**         status of the DMA transfer can be checked using
**         GetCharsInRxBuf method. See an example of a typical usage
**         for details about the communication using DMA.
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
**                           ERR_COMMON - common error occurred (the
**                           GetError method can be used for error
**                           specification)
**                           DMA mode:
**                           If DMA controller is available on the
**                           selected CPU and the receiver is
**                           configured to use DMA controller then
**                           only ERR_OK, ERR_RXEMPTY, and ERR_SPEED
**                           error code can be returned from this
**                           method.
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
**         DMA mode:
**         If DMA controller is available on the selected CPU and
**         the transmitter is configured to use DMA controller then
**         this method only sets selected DMA channel. Then the
**         status of the DMA transfer can be checked using
**         GetCharsInTxBuf method. See an example of a typical usage
**         for details about communication using DMA.
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
**         This method is internal. It is used by Processor Expert
**         only.
** ===================================================================
*/


void AS1_Init(ModBus* _modbus);
/*
** ===================================================================
**     Method      :  AS1_Init (bean AsynchroSerial)
**
**     Description :
**         This method is internal. It is used by Processor Expert
**         only.
** ===================================================================
*/


#pragma CODE_SEG DEFAULT                                   
/* END AS1. */

/*
** ###################################################################
**
**     This file was created by UNIS Processor Expert 2.95.01 [03.62]
**     for the Freescale HCS12 series of microcontrollers.
**
** ###################################################################
*/

#endif /* ifndef __AS1 */
