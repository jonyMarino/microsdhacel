/* MODULE modbus. */

#include "Cpu.h"
#include "modbus.hpp"
#include "stddef.h"
#include "puertoSerie1.h"
#include "trx.h"
#include "Thread.h"

#pragma DATA_SEG ModBus_DATA                                            
#pragma CODE_SEG ModBus_CODE 
#pragma CONST_SEG DEFAULT



/* EscrituraDemorada se encarga de guardar las variables para grabar el dato en el thread y no en la interrupcion, lo que traeria problemas*/
ModBus::EscrituraDemorada::EscrituraDemorada(NodoICModBus& _nodo,void * _dir,uint _dato):nodo(_nodo),dir(_dir),dato(_dato){}

void ModBus::EscrituraDemorada::escribir(){
  nodo.setDato(dir,dato);
}
        

static const ModBus::T_OnRecive ModBus::onRecive[6]={
/*  #ifdef _N_MODBUS
    1,dhacelRead,
    3,dhacelRead,
  #else
    3,modBusRead,
    4,modBusRead, 
  #endif  
  #ifdef _N_MODBUS
    5,modBusWrite,
    6,modBusWrite,
  #else
    6,modBusWrite,
  #endif
    8,readCompilacion,
  */
  0,NULL    //NO SACAR: Indican el Final
};


static void* ModBus::escribirDatoEnColaIntermedia(void*_self){
  ModBus * self = (ModBus *)_self;
  self->escribirDatoEnCola();
  return NULL;  
}

/*										 
** ===================================================================
**     Function    : ModBus 
**     Description :
**         Inicializacion de la comunicacion
** ===================================================================
*/
ModBus::ModBus(ConfiguracionModBus& conf,const struct Array/*<NodoICModBus>*/ *_comProps,PromBkp*_prom):configuracion(conf),comProps(_comProps),prom(_prom),timer(3,mOnTime),step(0),pEscrituraDemorada(NULL){
  timer.stop();
  AS1_Init(*this);
  mOnTime.pmethod= onTimePass;
  mOnTime.obj = this;
  void*thread;
  pthread_create(&thread,NULL,escribirDatoEnColaIntermedia,this);
}

/*										 
** ===================================================================
**     Function    : escribirDatoEnCola 
**     Description :
**         Llamada desde el thread
** ===================================================================
*/
#warning especificacion: main loop debe tardar como maximo 1 recive + 1 send + 3 ms	(15 ms a 9600 baud)
void ModBus::escribirDatoEnCola(){
  if(pEscrituraDemorada){
    if(prom)
      prom->demorarGrabado(30);
    pEscrituraDemorada->escribir();
    delete pEscrituraDemorada;
    pEscrituraDemorada = NULL;
  }
}

/*										 
** ===================================================================
**     Event       :  AS1_OnRxChar (module Events)
**     Description :
**         Este Evento es llamado despues de que pasaron 3 ms sin 
**    recibir ningun valor. Por lo que prepara al módulo para recibir
**    un nuevo mensaje.
** ===================================================================
*/

static void ModBus::onTimePass(void*_self){
  ModBus *self = (ModBus*)_self;
  self->step=0;
  self->timer.stop();
}

/*
** ===================================================================
**     Event       :  AS1_OnTxComplete (module Events)
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
void ModBus::onTxComplete(void)
{
  /* Write your code here ... */
  (*onSend)(this);
}

void ModBus::setOnSend(void (*pf)(void*)){  
  *onSend=pf;
}
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

void ModBus::onRxChar(byte dat)
{
  byte i;
  word crc;
  
  
  msj[step]=dat;
  switch(step){
    
    case 0:if (msj[0]!= configuracion.getId() || !timer.isFinished() ){
      timer.restart();
      break;         //Id 
    }
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
      		 step++;
      		 timer.restart(); // ckeckeo que no pasen 3ms    		 
      		 break;
    case 7: 
    			step = 0;
          timer.restart();// ckeckeo que no pasen 3ms    			
          crc = calcularCrc(msj,6);
          if ( (crc%256)!=msj[6] || (crc/256)!=msj[7] ){
              break; 
          }
        
					
					for(i=0;onRecive[i].onFuncion!=NULL;i++){
					  if(onRecive[i].id==msj[1]){
					    (*onRecive[i].onFuncion)(this,msj);
					    break;  
					  }
					}
 			
  }
    
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

void ModBus::sending()
{  
  if (step == 0)
    trx_SetVal();

  if (step<cantMsjsOut){
    
    if (AS1_SendChar(msj[step])==ERR_OK) 
        step++;
  } else if(step==cantMsjsOut) {  
    //  Timer_Restart(&comu_timer);// ckeckeo que no pasen 3ms
      asTx=FALSE;		//Termino el proceso de transmision
      step=0;
      trx_ClrVal();
  }
}

/*
** ===================================================================
**     Method      :  ModBus_Send
**
**     Description :
**         llamar a esta funcion para enviar un mensaje por el puerto 
**     serie
** ===================================================================
*/
byte ModBus::send(byte * data,byte cant){
  byte i;
  word crc;
  
  if(asTx)
    return ERR_BUSY;
  
  for(i=0;i<cant;i++)
    msj[i]=data[i];  
  
  crc = calcularCrc(msj,cant);
  msj[i]= crc%256;  // a los siguientes 2 bytes les agrego el crc
  msj[i+1]= crc/256;  // a los siguientes 2 bytes les agrego el crc
  
  cantMsjsOut=cant+2;
  asTx=TRUE;
  
  setOnSend(sendingIntermedia);
  sending();//Puede ser demasiado rapido llamar a esta funcion aca, verificar
  
  return ERR_OK;
}

/*
** ===================================================================
**     Method      :  getAddressData
**
**     Description :
**         obtiene el valor de esa direccion
** ===================================================================
*/
word ModBus::getAddressData(word address){
  byte i;  
  byte count = Array_count(comProps);
    
    if(address&1)                    //no soporta direcciones impares
      return *(word*)address;
    
    
    for(i=0;i<count;i++){	
      NodoICModBus * nodo = (NodoICModBus *)Array_get(comProps,i);															
      if(nodo->contieneDireccion((void*)address))
        return nodo->getDato((void*)address);
    }
    if(i==count)				// no es la dir de un parametro?
      return *(word*)address;
}

/*
** ===================================================================
**     Method      :  writeAddress
**
**     Description :
**         Escribe dato en address, que corresponde a algun nodo
** ===================================================================
*/
byte ModBus::writeAddress(word address,int dato){
  byte i; 
  byte count = Array_count(comProps);
    
  for(i=0;i<count;i++){	
      NodoICModBus * nodo = (NodoICModBus *)Array_get(comProps,i);																	
      if( nodo->contieneDireccion((void*)address) ){
        if(nodo->isEscribible()){         
          if(pEscrituraDemorada)
            return 1; //cambiar : error no alcanzo el tiempo
          /*pEscrituraDemorada =*/ new ModBus::EscrituraDemorada(*nodo,(void*)address,dato);
          return ERR_OK;       
        }
      }
  }
}


byte ModBus::modBusRead(void * _self,byte * data){
    ModBus * self = (ModBus *) _self;
    
    if (data[4]!=0 || data[5]==0)
      return ERR_VALUE;
    self->address=*((word *)&data[2]);
    data[2]=data[5]*2;
 
    self->setOnSend(sendReadIntermedia);
    self->sendRead();
    
    return ERR_OK;
}


void ModBus::sendRead(void){
    byte byteOut = msj[step];
    
    if (step == 0){
      crc = 0xffff;
      trx_SetVal();
    }
    
    if (AS1_SendChar(msj[step])==ERR_OK){
        //actualizo el valor del crc a enviar
        crc ^= byteOut;
        crc = crcControl[crc%256]^(crc/256);
        step++;
        if(step>2){
          step = 0;
          setOnSend(sendNextReadIntermedia);
        }
    }
}


void ModBus::sendNextRead(void){
  static word wordOut;
  byte byteOut;
  
  if ((step&1) == 0){
    wordOut = getAddressData(address);
    address+=2;
    byteOut = *((byte *)&wordOut);
  }else{
    byteOut = *( ((byte *)&wordOut) +1  ); 
  }
    
    
  if (AS1_SendChar(byteOut)==ERR_OK){          
      //actualizo el valor del crc a enviar
      crc ^= byteOut;
      crc = crcControl[crc%256]^(crc/256);
      
      step++;
      if(step==msj[2]){
          step = 0;
          setOnSend(sendCRCIntermedia);  
      }
  }
}

void ModBus::sendCRC(void){
  switch(step){
    case 0:
      if (AS1_SendChar(crc%256)==ERR_OK){     
        step++; 
      }
      break;
    case 1:
      if (AS1_SendChar(crc/256)==ERR_OK){     
        step++; 
      }
      break;
    case 2:
      asTx=FALSE;		//Termino el proceso de transmision
      step=0;
      trx_ClrVal();
      break;      
  }
}

byte ModBus::modBusWrite(void * _self,byte * data){
    ModBus * self = (ModBus *) _self;
    
    word Address=*((word *)&data[2]);
    int Data = *(int *)&data[4];
 		byte err;
 		
    err= self->writeAddress(Address,Data);
    if(err)
      return err;
    
    return self->send(data,6); 
           
}

byte ModBus::dhacelRead(void * _self,byte * data){
  ModBus * self = (ModBus *) _self;
      
  word Address=*((word *)&data[2]);

  *((word *)&data[4])= self->getAddressData(Address); 

  return self->send(data,6);
}


/*
** ===================================================================
**    Function    : com_Recognize 
**    Description : Devuelve las opciones de compilacion
** ===================================================================
*/
byte ModBus::getCompilacion(byte * data){
  *(long*)&data[2]=_COMP_OPTIONS;
  send(data,6);  
  return 0;
}




/////////////////////////////////////////////////////////////////////////// 
 // Control del CRC para realizar las xor 

///////////////////////////////////////////////////////////////////////////
 #pragma CONST_SEG DEFAULT  

const unsigned int ModBus::crcControl[256]=	{

	0x0,    //0
	0xc0c1, //1
	0xc181, //2
	0x140,  //3
	0xc301, //4
	0x3c0,  //5
	0x280,  //6
	0xc241, //7
	0xc601, //8
	0x6c0,  //9
	0x780,  //10
	0xc741, //11
	0x500,  //12
	0xc5c1, //13
	0xc481, //14
	0x440,  //15
	0xcc01, //16
	0xcc0,  //17
	0xd80,  //18
	0xcd41, //19
	0xf00,  //20
	0xcfc1, //21
	0xce81, //22
	0xe40,  //23
	0xa00,  //24
	0xcac1, //25
	0xcb81, //26
	0xb40,  //27
	0xc901, //28
	0x9c0,  //29
	0x880,  //30
	0xc841, //31
	0xd801, //32
	0x18c0, //33
	0x1980, //34
	0xd941, //35
	0x1b00, //36
	0xdbc1, //37
	0xda81, //38
	0x1a40, //39
	0x1e00, //40
	0xdec1, //41
	0xdf81, //42
	0x1f40, //43
	0xdd01, //44
	0x1dc0, //45
	0x1c80, //46
	0xdc41, //47
	0x1400, //48
	0xd4c1, //49
	0xd581, //50
	0x1540, //51
	0xd701, //52
	0x17c0, //53
	0x1680, //54
	0xd641, //55
	0xd201, //56
	0x12c0, //57
	0x1380, //58
	0xd341, //59
	0x1100, //60
	0xd1c1, //61
	0xd081, //62
	0x1040, //63
	0xf001, //64
	0x30c0, //65
	0x3180, //66
	0xf141, //67
	0x3300, //68
	0xf3c1, //69
	0xf281, //70
	0x3240, //71
	0x3600, //72
	0xf6c1, //73
	0xf781, //74
	0x3740, //75
	0xf501, //76
	0x35c0, //77
	0x3480, //78
	0xf441, //79
	0x3c00, //80
	0xfcc1, //81
	0xfd81, //82
	0x3d40, //83
	0xff01, //84
	0x3fc0, //85
	0x3e80, //86
	0xfe41, //87
	0xfa01, //88
	0x3ac0, //89
	0x3b80, //90
	0xfb41, //91
	0x3900, //92
	0xf9c1, //93
	0xf881, //94
	0x3840, //95
	0x2800, //96
	0xe8c1, //97
	0xe981, //98
	0x2940, //99
	0xeb01, //100
	0x2bc0, //101
	0x2a80, //102
	0xea41, //103
	0xee01, //104
	0x2ec0, //105
	0x2f80, //106
	0xef41, //107
	0x2d00, //108
	0xedc1, //109
	0xec81, //110
	0x2c40, //111
	0xe401, //112
	0x24c0,  //113
	0x2580,  //114
	0xe541,  //115
	0x2700,  //116
	0xe7c1,  //117
	0xe681,  //118
	0x2640,  //119
	0x2200,  //120
	0xe2c1,  //121
	0xe381,  //122
	0x2340,  //123
	0xe101,  //124
	0x21c0,  //125
	0x2080,  //126
	0xe041,  //127
	0xa001,  //128
	0x60c0,  //129
	0x6180,  //130
	0xa141,  //131
	0x6300,  //132
	0xa3c1,  //133
	0xa281,  //134
	0x6240,  //135
	0x6600,  //136
	0xa6c1,  //137
	0xa781,  //138
	0x6740,  //139
	0xa501,  //140
	0x65c0,  //141
	0x6480,  //142
	0xa441,  //143
	0x6c00,  //144
	0xacc1,  //145
	0xad81,  //146
	0x6d40,  //147
	0xaf01,  //148
	0x6fc0,  //149
	0x6e80,  //150
	0xae41,  //151
	0xaa01,  //152
	0x6ac0,  //153
	0x6b80,  //154
	0xab41,  //155
	0x6900,  //156
	0xa9c1,  //157
	0xa881,  //158
	0x6840,  //159
	0x7800,  //160
	0xb8c1,  //161
	0xb981,  //162
	0x7940,  //163
	0xbb01,  //164
	0x7bc0,  //165
	0x7a80,  //166
	0xba41,  //167
	0xbe01,  //168
	0x7ec0,  //169
	0x7f80,  //170
	0xbf41,  //171
	0x7d00,  //172
	0xbdc1,  //173
	0xbc81,  //174
	0x7c40,  //175
	0xb401,  //176
	0x74c0,  //177
	0x7580,  //178
	0xb541,  //179
	0x7700,  //180
	0xb7c1,  //181
	0xb681,  //182
	0x7640,  //183
	0x7200,  //184
	0xb2c1,  //185
	0xb381,  //186
	0x7340,  //187
	0xb101,  //188
	0x71c0,  //189
	0x7080,  //190
	0xb041,  //191
	0x5000,  //192
	0x90c1,  //193
	0x9181,  //194
	0x5140,  //195
	0x9301,  //196
	0x53c0,  //197
	0x5280,  //198
	0x9241,  //199
	0x9601,  //200
	0x56c0,  //201
	0x5780,  //202
	0x9741,  //203
	0x5500,  //204
	0x95c1,  //205
	0x9481,  //206
	0x5440,  //207
	0x9c01,  //208
	0x5cc0,  //209
	0x5d80,  //210
	0x9d41,  //211
	0x5f00,  //212
	0x9fc1,  //213
	0x9e81,  //214
	0x5e40,  //215
	0x5a00,  //216
	0x9ac1,  //217
	0x9b81,  //218
	0x5b40,  //219
	0x9901,  //220
	0x59c0,  //221
	0x5880,  //222
	0x9841,  //223
	0x8801,  //224
	0x48c0,  //225
	0x4980,  //226
	0x8941,  //227
	0x4b00,  //228
	0x8bc1,  //229
	0x8a81,  //230
	0x4a40,  //231
	0x4e00,  //232
	0x8ec1,  //233
	0x8f81,  //234
	0x4f40,  //235
	0x8d01,  //236
	0x4dc0,  //237
	0x4c80,  //238
	0x8c41,  //239
	0x4400,  //240
	0x84c1,  //241
	0x8581,  //242
	0x4540,  //243
	0x8701,  //244
	0x47c0,  //245
	0x4680,  //246
	0x8641,  //247
	0x8201,  //248
	0x42c0,  //249
	0x4380,  //250
	0x8341,  //251
	0x4100,  //252
	0x81c1,  //253
	0x8081,  //254
	0x4040,  //255
};
/*
** ===================================================================
**     Method      :  Calculo del CRC
**
**     Description :
**         This method is internal. It is used by Processor Expert
**         only.
** ===================================================================
*/


static unsigned short int ModBus::calcularCrc(unsigned char *z_p,unsigned char z_message_length){

unsigned short int CRC= 0xffff;
unsigned short int next;

 while (z_message_length--){
   next = (unsigned short int)*z_p;
   CRC ^= next;
   CRC = crcControl[CRC%256]^(CRC/256);
   z_p++;
 }
 return CRC;
}