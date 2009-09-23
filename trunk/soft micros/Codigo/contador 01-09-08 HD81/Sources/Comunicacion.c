/* MODULE Comunicacion. */

#include "Cpu.h"
#include "Mydefines.h"
#include "AS1.h"
#include "trx.h"
#include "Comunicacion.h"
#include "Adquisidor.h"

unsigned short int calculate_crc(unsigned char *z_p,unsigned char z_message_length);

//extern const byte Pot_2[8];
//////////////Comunicacion//////////
byte StepTx=0;  //Pasos en la transmisión
bool RSave, AS1_Tx;
static byte cantidad_mensajes;  // cantidad de mensajes a enviar sin el CRC
byte ASespera;
byte Step=0;
word RSave_espera;
byte msn[16];
word crc;
word Address,Data;
//////////////////////////////////

/*
** ===================================================================
**     Event       :  AS1_OnRxChar (module Events)
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
/*Variables FLASH*/
extern word BackupArray[256],SavedAddress;
extern byte IndiceFlash[255/8+1];

extern const long Id;  
  switch(Step){
    
    case 0:if (ASespera==0 && msn[0]!= (byte)Id) break;         //Id 
    case 1:
    case 2:
    case 3: //Address 2
    case 4:
      		 Step++;
      		 break;
    case 5:
      		 Step++;
      		 crc = calculate_crc(msn,6);
      		 break;
    case 6:Step++;  // primer CRC
      		 if ((crc%256)!=msn[6])
			     Step=0;
           break;
    case 7: if ((crc/256)!=msn[7]){
            Step=0;
            break; 
             }// segundo CRC
            
      
 
           Address = *((word *)&msn[2]);
 					 if (msn[1]==3 || msn[1]==4){ //leer n palabras de 16 bits
            if (msn[4]==0 && msn[5]==1)  
            { 
              msn[2]=msn[5]*2;
              msn[3] = *(volatile byte *) Address ;
              msn[4] = *(volatile byte *)(Address+1) ;
              cantidad_mensajes=5;
              AS1_Tx=TRUE; //enviar
            }
  
            #if FLASH_PARAMETROS_END < RAM_COMUNICACION_START
            #error revisar abajo
            #endif
            } else if (msn[1]==6){ //escribir una palabra de 16 bits
              Data = *((word *)&msn[4]);
              if (Address <= RAM_COMUNICACION_END)
                *(volatile word*) Address = Data;													
              else if(Address <=FLASH_PARAMETROS_END){
                if(RSave == FALSE) SavedAddress = Address&65024;
                if(SavedAddress==(Address&65024) && !(Address&1)){
                  BackupArray[(Address&511)/2]= Data;
                  IndiceFlash[(Address&511)/32]|=(1<<(((Address&511)/2)%16));
								  RSave_espera = 10;
                  RSave = TRUE;
                  cantidad_mensajes=6;
                  AS1_Tx=TRUE; //enviar 
                }
              }
            }
            Step=0;
  }
   ASespera=3;  
}

/*
** ===================================================================
**     Event       :  AS1_OnTxChar (module Events)
**
**     From bean   :  AS1 [AsynchroSerial]
**     Description :
**         This event is called after a character is transmitted.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void AS1_TxChar(void)
{
 
if (StepTx == 0 && ASespera != 0) return;
else trx_SetVal();

if (StepTx<cantidad_mensajes){
  
  if (AS1_SendChar(msn[StepTx])==ERR_OK) {
    
    StepTx++;
    if(StepTx==cantidad_mensajes) crc = calculate_crc(msn,cantidad_mensajes);
  }
} else if(StepTx==cantidad_mensajes) {
  if (AS1_SendChar(crc%256)==ERR_OK)
    StepTx++;
  
} else if(StepTx==cantidad_mensajes+1) { 											//CRC	 2
  if (AS1_SendChar(crc>>8)==ERR_OK){
   StepTx++; 
    }

} else if (StepTx==cantidad_mensajes+2) {
    if (AS1_GetTxComplete()){
    
 //   ASespera=3;
    AS1_Tx=FALSE;		//Termino el proceso de transmision
    StepTx=0;
    trx_ClrVal();
		}

} else{		//out of bounds
    AS1_Tx=FALSE;
    StepTx=0;
    trx_ClrVal();
}


}


/*
** ===================================================================
**     Method      :  Calculo del CRC
**
**     Description :
**         This method is internal. It is used by Processor Expert
**         only.
** ===================================================================
*/


unsigned short int calculate_crc(unsigned char *z_p,unsigned char z_message_length){

unsigned short int CRC= 0xffff;
unsigned short int next;
unsigned short int carry;
unsigned short int n;

while (z_message_length--){
  next = (unsigned short int)*z_p;
  CRC ^= next;
  for (n=0; n<8 ; n++){
    carry = CRC & 1;
    CRC >>= 1;
    if (carry) {
      CRC ^= 0xA001;
    }
  }
  z_p++;
 }
 return CRC;

}