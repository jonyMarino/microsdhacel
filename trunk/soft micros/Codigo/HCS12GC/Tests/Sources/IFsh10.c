/** ###################################################################
**     Filename  : IFsh10.C
**     Project   : Controlador
**     Processor : MC9S12GC32CFU16
**     Beantype  : IntFLASH
**     Version   : 0.0.2
**     Compiler  : Metrowerks HC12 C Compiler
**     Date/Time : 20/03/2008, 16:20
**     Abstract  :
**         This bean "IntFLASH" implements an access to internal FLASH.
**         The bean support reading/writing data into FLASH, erasing of 
**         selected sector.
**         The bean supports events if the write interrupt is supported.
**         The bean supports following modes of write operations:
**           - Write - writing without any test.
**           - Destructive write - sector is erased if necessary.
**           - Safe write - user event is invoked to save and resore data
**                          from the current sector.
**         The bean requires on-chip FLASH memory (not used/allocated by 
**         other beans).
**     Settings  :
**         Total FLASH memory size       : 32KB
**         Interrupt service             : Disabled
**         Write method                  : Safe write (with save & erase)
**         Buffer Type                   : Implemented by the bean
**         Wait in RAM                   : yes
**     Contents  :
**         SetWordFlash - byte IFsh10_SetWordFlash(dword Addr,word Data);
**
**     (c) Copyright UNIS, spol. s r.o. 1997-2004
**     UNIS, spol. s r.o.
**     Jundrovska 33
**     624 00 Brno
**     Czech Republic
**     http      : www.processorexpert.com
**     mail      : info@processorexpert.com
** ###################################################################*/


/* MODULE IFsh10. */

#include "IFsh10.h"

#pragma DATA_SEG IFsh10_DATA                                            
#pragma CODE_SEG IFsh10_CODE                     

/* Global variables */
#pragma CONST_SEG DEFAULT
static bool save; /* Ordena salvar el valor en la ram para copy a eeprom cuando set*/
word IndiceFlash[512/16]; /* Indice de parametros modificados*/
byte BackupArray[512];								/* Array for backup data from erased sector */

word PageAddr;
static byte WaitInRAMcode[]={
 0x1E, 0x01, 0x05, 0x20, 0x05,         /* BRSET _FSTAT,#32,*+10 */
 0x1F, 0x01, 0x05, 0x10, 0x03,         /* BRCLR _FSTAT,#16,*+8 */
 0xC6, 0x09,                           /* LDAB  #9 */
 0x3D,                                 /* RTS */
 0x1F, 0x01, 0x05, 0x40, 0xFB,         /* BRCLR _FSTAT,#64,*+0 */
 0x3D                                  /* RTS */
};

bool Fsh_to_save(void){
  return save;
}
/*
** ===================================================================
**     Method      :  WriteWord (bean IntFLASH)
**
**     Description :
**         This method is internal. 
** ===================================================================
*/
byte WriteWord(word Addr,word Data16)
{
  byte err;

  EnterCritical();                     /* Enter critical section */
  FSTAT = 48;                        /* Clear all flags */
   if (FSTAT_CBEIF == 0) {              /* Is command buffer full ? */
    ExitCritical();                    /* Exit critical section */
    return ERR_BUSY;                   /* If yes then error */
  }
  *(volatile word *) Addr = Data16;    /* Array address and program data */
  FCMD = 32;                           /* Word program command */
  FSTAT = 128;                         /* Clear flag command buffer empty */
  asm {                                /* Jump to Wait in RAM code */
    CLRB
    JSR WaitInRAMcode
    STAB err
  }
  ExitCritical();                      /* Exit critical section */
  if (err)
    return ERR_NOTAVAIL;               /* Return error code if previous operation finished not correctly */
  if (*(volatile word *) Addr != Data16) /* Was attempt to write data to the given address errorneous? */
    return ERR_VALUE;                  /* If yes then error */
 return ERR_OK;                        /* OK */
}


/*
** ===================================================================
**     Method      :  RestoreSector (bean IntFLASH)
**
**     Description :
**         This method is internal. 
** ===================================================================
*/
byte WriteArray(word Addr,word From, word To, word* Array)
{
  byte err;
  word i;

  EnterCritical();                     /* Enter critical section */
  FSTAT = 48;                        /* Clear all flags */
  for (i = From; i < To; i+=2)
  {
    *(volatile word *) (Addr+i) = Array[i/2];
    FCMD = 32;                         /* Word program command */
    FSTAT = 128;                       /* Clear flag command buffer empty */
    asm {                              /* Jump to Wait in RAM code */
      CLRB
      JSR WaitInRAMcode
      STAB err
    }
    if (err) {
      ExitCritical();                  /* Exit critical section */
      return ERR_NOTAVAIL;             /* Return error code if previous operation finished not correctly */
    }
    if (*(volatile word *) (Addr+i) != Array[i/2]) { /* Was attempt to write data to the given address errorneous? */
      ExitCritical();                  /* Exit critical section */
      return ERR_VALUE;                /* If yes then error */
    }
  }
  ExitCritical();                      /* Exit critical section */
  return ERR_OK;                       /* OK */
}

/*
** ===================================================================
**     Method      :  EraseSectorInternal (bean IntFLASH)
**
**     Description :
**         This method is internal. 
** ===================================================================
*/
byte EraseSectorInternal(word Addr)
{
  byte err;

  EnterCritical();                     /* Enter critical section */
  FSTAT = 48;                          /* Clear all flags */
  if (FSTAT_CBEIF == 0) {              /* Is command buffer full ? */
    ExitCritical();                    /* Exit critical section */
    return ERR_BUSY;                   /* If yes then error */
  }
  *(volatile word *) (Addr & 65024) = IFsh10_DummyData; /* Write eny word to FLASH buffer */
  FCMD = 64;                           /* Initiate Sector Erase commamd */
  FSTAT = 128;                         /* Clear flag command buffer empty */
  asm {                                /* Jump to Wait in RAM code */
    CLRB
    JSR WaitInRAMcode
    STAB err
  }
  ExitCritical();                      /* Exit critical section */
  if (err)
    return err;                        /* Return error code if previous operation finished not correctly */
  return ERR_OK;                       /* OK */

}

/*
** ===================================================================
**     Method      :  BackupSector (bean IntFLASH)
**
**     Description :
**         This method is internal.
** ===================================================================
*/

void BackupSector() {
byte i,a;

Cpu_DisableInt();
  for (a=0;a<(512/16);a++){
    for (i=0;i<16;i++){
      if (!(IndiceFlash[a]&1))
        BackupArray[a*16+i]=*(volatile byte*)(PageAddr+a*16+i);
    IndiceFlash[a]>>=1;
    }
  }
Cpu_EnableInt();
}

/*
void BackupSector(word Addr,byte* Backup){
word i;
  for (i=0;i<512;i=i+2)
    Backup[i]=;
}	 */

/*
** ===================================================================
**     Method      :  IFsh10_SetWordsParametros (bean IntFLASH)
**
**     Description :
**         Write word to address in FLASH.
**     Parameters  :
**         NAME            - DESCRIPTION
**         Addr            - Address to FLASH.
**         Data            - Data to write.
**     Returns     :
**         ---             - Error code, possible codes:
**                           - ERR_OK - OK
**                           - ERR_NOTAVAIL - Desired program/erase
**                           operation is not available
**                           - ERR_VALUE - Read value is not equal to
**                           written value
**                           - ERR_SPEED - This device does not work
**                           in the active speed mode
**                           - ERR_BUSY - Device is busy
** ===================================================================
*/
byte IFsh10_GrabarFlash(void)
{
  byte err;
   if (PageAddr & 1)                        /* Aligned address ? */
    return ERR_NOTAVAIL;
   if (FSTAT_CCIF == 0)                 /* Is previous command complete ? */
    return ERR_BUSY;                   /* If yes then error */
	 BackupSector();                      /* Backup sector */
	// EnterDatainBackup(Addr,Data,BackupArray,Indice,CantidadBytes);       /* pongo los valores del Pram en sus lugares */
   err=EraseSectorInternal(PageAddr);     /* Erase sector */
    if(err)
      return(err);                     /* Return error code if previous operation finished not correctly */
   err = WriteArray(PageAddr,0,512,(word*)BackupArray); /* Restore sector */
   PageAddr=0;                        /* Se puede volver a mandar a grabar*/ 
    if (err)
      return err;                      /* Previous operation was error ? */
 	 save = FALSE;
 	 return ERR_OK;
}

/*
** ===================================================================
**     Method      :  IFsh10_SetWordsArray (bean IntFLASH)
**
**     Description :
**         Write word to address in FLASH.
**     Parameters  :
**         Addr            - Address to FLASH.
**         Data            - Address of Array of Data to write.
**         Cantidad        - Amount words to write
**     Returns     :
**         ---             - Error code, possible codes:
**                           - ERR_OK - OK
**                           - ERR_NOTAVAIL - Desired program/erase
**                           operation is not available
**                           - ERR_VALUE - Read value is not equal to
**                           written value
**                           - ERR_SPEED - This device does not work
**                           in the active speed mode
**                           - ERR_BUSY - Device is busy
** ===================================================================
*/
byte EscribirWord(word  Addr,int valor){
  
  *(word *)Addr=valor;
  return ERR_OK;	
};

byte EscribirByte(word  Addr,byte valor){
  
                          
//  if (Addr<0x4000)
//    return ERR_RANGE;
  *(byte *)Addr=valor;
  return ERR_OK;		
};


/*
** ===================================================================
**    Function    : IFsh10_isInIndex 
**    Description : Se fija si esa direccionde memoria esta en el index
**    , la direccion debe pertenecer al PageAddress
** ===================================================================
*/
bool IFsh10_isInIndex(word Addr){
  return FALSE;
}


word IFsh10_getWord(word  Addr){
    return *(word *)Addr;
}

byte IFsh10_getByte(word  Addr){
      return *(byte *)Addr;
}

/* END IFsh10. */


/*
** ###################################################################
**
**     This file was created by UNIS Processor Expert 2.95 [03.62]
**     for the Freescale HCS12 series of microcontrollers.
**
** ###################################################################
*/
