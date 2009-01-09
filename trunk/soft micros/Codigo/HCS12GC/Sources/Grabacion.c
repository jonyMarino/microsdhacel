#include <stdlib.h>
#include <limits.h>

#include "PE_Types.h"
#include "IFsh10.h"
#include "Timer.h"
#include "TI1.h"
#include "ClassADC.h"
#include "MethodContainer.h"
#include "LinkedList.h"
#include "GrabacionEvents.h"
#include "Grabacion.h"

				
void Grabacion_OnEraseEvents(uint ErasePage);

struct LinkedList EraseList;
struct Timer * ptimer=NULL;
word DisableCont=0; 

struct MethodContainer * Grab_MC=NULL;
  

static bool save; /* Ordena salvar el valor en la ram para copy a eeprom cuando set*/
word IndiceFlash[512/16]; /* Indice de parametros modificados*/
byte BackupArray[512];								/* Array for backup data from erased sector */

word PageAddr;

bool Fsh_to_save(void){
  return save;
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
  
  if (Addr & 1){
    /* Aligned address ? */
    byte err;
    err=EscribirByte(Addr+1,(byte)valor);
    if(err) return err;
    err=EscribirByte(Addr,(byte) (valor>>8));
    return err;
    //return ERR_NOTAVAIL;
  }

  if(*(word *)Addr!=valor){
    byte shift;
    
    if(PageAddr==0) 
      PageAddr=Addr&65024;
    else if (PageAddr!=(Addr&65024))
      return ERR_BUSY;      /* Todavia no se grabo la página en cola*/  
  
    *(word *)&BackupArray[(Addr&511)]= valor;
    shift=(Addr&511)%16;
    IndiceFlash[(Addr&511)/16]|= 1<<shift;	 //MSB
    IndiceFlash[(Addr&511)/16]|= 1<<(shift+1);	 //LSB
    save=TRUE;
  }
  return ERR_OK;
};

byte EscribirByte(word  Addr,byte valor){
  
                        
  if(*(byte *)Addr!=valor){
    if(PageAddr==0) 
      PageAddr=Addr&65024;
    else if (PageAddr!=(Addr&65024))
      return ERR_BUSY;      /* Todavia no se grabó la página en cola*/  
  
  
    BackupArray[(Addr&511)]= valor;
    IndiceFlash[(Addr&511)/16]|= 1<<((Addr&511)%16);
    save=TRUE;
  }
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
  word mask= 1<<((Addr&511)%16);
  word index=(Addr&511)/16;
  return (IndiceFlash[index]&mask)?TRUE:FALSE ;  
}


word IFsh10_getWord(word  Addr){
  if(!save || PageAddr!=(Addr&65024) ||   !(IFsh10_isInIndex(Addr) || IFsh10_isInIndex(Addr+1)) ) // con que el primero este para grabar alcanza
    return *(word *)Addr;
  else
    return *(word *)&BackupArray[(Addr&511)];
}

byte IFsh10_getByte(word  Addr){
  if(!save || PageAddr!=(Addr&65024) ||  !IFsh10_isInIndex(Addr) )
      return *(byte *)Addr;
  else 
      return BackupArray[(Addr&511)];
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

  for (a=0;a<(512/16);a++){
    for (i=0;i<16;i++){
      if (!(IndiceFlash[a]&1))
        BackupArray[a*16+i]=*(volatile byte*)(PageAddr+a*16+i);
    IndiceFlash[a]>>=1;
    }
  }
}
/*
** ===================================================================
**    Function    :  Grabacion_BorrarPag 
**    Description : 
** ===================================================================
*/
void Grabacion_BorrarPag(word Addr){
  if(Addr==0)
    return;
  LinkedList_add(&EraseList,(void*)Addr);
}

/*
** ===================================================================
**    Function    :  Grabacion_Init 
**    Description : 
** ===================================================================
*/
void Grabacion_Init(void){  
  newAllocObj(&EraseList,LinkedList);
}

/*
** ===================================================================
**    Function    :  Grabacion_Disable 
**    Description : 
** ===================================================================
*/
void Grabacion_Disable(void){
  DisableCont++;
  if(!DisableCont) //pego la vuelta?
    DisableCont=UINT_MAX;   
}

/*
** ===================================================================
**    Function    :  Grabacion_Enable 
**    Description : 
** ===================================================================
*/
void Grabacion_Enable(void){
  DisableCont--;
  if(DisableCont==UINT_MAX) //pego la vuelta?
    DisableCont=0;   
}

/*
** ===================================================================
**    Function    :  Grabacion_DelaySave 
**    Description : 
** ===================================================================
*/
void Grabacion_DelaySave(word time){
  if(!ptimer)
    ptimer=newObj(Timer,(ulong)time);
  else
    Timer_setTime(ptimer,(ulong)time);
}

/*
** ===================================================================
**    Function    :  Grabacion_save_ready 
**    Description : 
** ===================================================================
*/
bool Grabacion_save_ready(void){
  bool DelayFlag;
  
  Cpu_DisableInt();
  DelayFlag=(ptimer)?Timer_isfinish(ptimer):TRUE;
  if(ptimer && DelayFlag)
    deleteObj(&ptimer);
  Cpu_EnableInt();
  
  return (
  				#ifdef _ADC
          getState()==AD_WAITING 
          && 
          #endif
          ( Fsh_to_save() || LinkedList_Vacia(&EraseList)==FALSE)
          && DelayFlag
          && DisableCont==0);  
}

/*
** ===================================================================
**    Function    :  Grabacion_Handler 
**    Description : 
** ===================================================================
*/
void Grabacion_Handler(void){ 
  if( Grabacion_save_ready())
        TI1_SetPeriodMode(TI1_Pm_40ms); //Next interrupt is 40ms length
}

/*
** ===================================================================
**    Function    :  Grabacion_OnAble 
**    Description : 
** ===================================================================
*/
void Grabacion_OnAble(void){
  void* dato;
 
  if(Fsh_to_save()){    
    PreWrite();
    BackupSector();
    IFsh10_GrabarFlash(PageAddr,BackupArray);  //GRABACION EN LA FLASH
    save = FALSE;	 
    OnWrite();
  } else if (LinkedList_Eliminar_Primero(&EraseList,&dato)==LST_OK){
    (void) EraseSectorInternal((word)dato); 
    Grabacion_OnEraseEvents((word)dato);
  }
}

/*
** ===================================================================
**    Function    :  Grabacion_ToSave 
**    Description : 
** ===================================================================
*/
bool Grabacion_ToSave(void){
  return Fsh_to_save();  
}


/*
** ===================================================================
**    Function    :  Grabacion_OnEraseEvents 
**    Description : 
** ===================================================================
*/
void Grabacion_OnEraseEvents(uint ErasePage){
  struct MethodContainerIterator it;
  if(Grab_MC){
    MethodContainer_methodContainerIterator(Grab_MC,&it); 
    while(MethodContainerIterator_hasNext(&it)){    
      const struct Method* mo= MethodContainerIterator_next(Grab_MC);
      (*(Grab_OnErase)mo->pmethod)(mo->Obj,(word*)ErasePage); 
    }
  }
}

/*
** ===================================================================
**    Function    :  Grabacion_AddOnEraseEvent 
**    Description : 
** ===================================================================
*/
void Grabacion_AddOnEraseEvent(Grab_OnErase pmethod,void*Obj){
  if(!Grab_MC)
    Grab_MC=newObj(MethodContainer);
  MethodContainer_Add(Grab_MC,(void(*)(void*))pmethod,Obj);
}


