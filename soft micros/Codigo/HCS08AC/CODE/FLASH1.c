/** ###################################################################
**     THIS BEAN MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename  : FLASH1.C
**     Project   : ManejadorFLASH
**     Processor : MC9S08AC128CLK
**     Beantype  : Init_FLASH
**     Version   : Bean 01.037, Driver 01.09, CPU db: 3.00.021
**     Compiler  : CodeWarrior HCS08 C Compiler
**     Date/Time : 02/12/2008, 9:44
**     Abstract  :
**          This file implements the FLASH (IntFLASH) module initialization 
**          according to the Peripheral Initialization Bean settings, and defines
**          interrupt service routines prototypes. 
**     Settings  :
**          Bean name                                      : FLASH1
**          Device                                         : IntFLASH
**          Settings                                       : 
**          Clock settings                                 : 
**          Divide flash clock by 8                        : no
**          Clock Divider                                  : 1
**          Frequency (150kHz - 200kHz)                    : 20000 kHz
**          Protection import                              : 
**          Initialization                                 : 
**          Call Init method                               : yes
**     Contents  :
**         Init - void FLASH1_Init(void);
**
**     (c) Copyright UNIS, spol. s r.o. 1997-2008
**     UNIS, spol. s r.o.
**     Jundrovska 33
**     624 00 Brno
**     Czech Republic
**     http      : www.processorexpert.com
**     mail      : info@processorexpert.com
** ###################################################################*/

/* MODULE FLASH1. */

#include "FLASH1.h"
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

#define ERROR  1
#define LISTO  0
#define ErasePage   FCMD = 0X40;
#define WriteByte   FCMD = 0X20;
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
  /* FSTAT: FCBEF=0,FCCF=0,FPVIOL=1,FACCERR=1,??=0,FBLANK=0,??=0,??=0 */
  setReg8(FSTAT, 0x00);                /* Clear error flags */ 
  /* FCDIV: FDIVLD=0,PRDIV8=0,FDIV5=0,FDIV4=0,FDIV3=0,FDIV2=0,FDIV1=0,FDIV0=0 */
 
  setReg8(FCDIV, 0XCC);                /* Set clock divider */
    
  //FOPT = 0x42;
  FPROT_FPOPEN  = 1; //FLASH NO PROTEGIDA 
}



byte escrFlash (byte  * addr,byte data){
 // __DI(); 
 
 if(FSTAT_FACCERR){
  FSTAT_FACCERR =0;
  FCDIV= 0XCC;
 }
 *addr = data;

 //FCMD = 0X20;   // COMANDO DE ESCRITURA DE UN BYTE
 WriteByte
 FSTAT_FCBEF = 1;
 asm
  {
  NOP
  NOP
  NOP
  NOP

  }  
 
 if(FSTAT_FACCERR || FSTAT_FPVIOL){
   return ERROR;
 } else while(!FSTAT_FCCF);
      //FSTAT_FCBEF = 0;
      return LISTO;
 
}

 
 
byte borraPagFlash (byte * addr){
  
  //__DI() ; 
 /* asm
  {
  NOP
  NOP
  NOP
  NOP

  } */
 
 if(FSTAT_FACCERR){
  FSTAT_FACCERR =0;
  FCDIV= 0XCC;
 }
 *(byte*)(((word)addr)&(0xFE00)) = 0x00;
 
 //*(byte*)0Xc000 = 0Xff;
 
 
// FCMD = 0X40;   // COMANDO DE BORRADO DE UN PAG.
  
  ErasePage

  //*(byte*)0X1826 = 0X40;

 //if(FSTAT_FCCF)
  //FSTAT_FCCF = 0;
 
 FSTAT_FCBEF = 1;
 //__EI(); 

  
 asm
  {
  NOP
  NOP
  NOP
  NOP
  }
 
 

 if(FSTAT_FACCERR || FSTAT_FPVIOL){
   return ERROR;
 } else 
    while(!FSTAT_FCCF);
      //FSTAT_FCBEF = 0;
      return LISTO;
     
}


/* END FLASH1. */

/*
** ###################################################################
**
**     This file was created by UNIS Processor Expert 3.03 [04.07]
**     for the Freescale HCS08 series of microcontrollers.
**
** ###################################################################
*/