/* MODULE Comunicacion. */

#include "Cpu.h"
#include "Mydefines.h"
#include "AS1.h"
#include "trx.h"
#include "Adquisidor.h"
#include "cnfbox.h"
#include "boxes.h"
#include "TimerNew.h"
#include "Programador.h"
#include "IFsh10.h"
#include "Comunicacion.h"
#include "Timer.h"

#ifdef _NMODBUS

#ifdef jony_23_08

#define NUM_DIRS 30

#pragma CONST_SEG DEFAULT

typedef struct{
  word dir_v, dir_n;
}T_direccion;

/*ATENCION!!!!!!!: ordenar de forma creciente las dirs viejas*/
const T_direccion TablaDirs[NUM_DIRS]={
  71,0x1008,    /*Set Point1*/
  73,0x1020,    /*OF/UF*/
  74,0x1000,    /*ValProc*/
  108,0x1010,   /*Potencia Control*/
  109,0x1018,   /* Potencia AL*/
  119,268,      /*Segmento*/
  120,300,      /*Tie Seg*/
  46592,4,      /*Set Point1*/
  46594,12,     /*AL1*/
  46600,28,     /*AB1*/
  46602,36,     /*ABA1*/
  46604,188,    /*DR1*/
  46606,180,    /*IN1*/
  46608,164,    /*RS1*/
  46618,60,     /*Decimales*/
  46623,244,    /*ST1*/
  46624,252,    /*Programa*/
  46625,6,      /*Set Point2*/ 
  46626,0x101A, /*AL2*/
  46633,30,     /*AB2*/
  46635,38,     /*ABA2*/
  46637,182,	  /*IN2*/
  46639,190,	  /*DR2*/
  46641,166,	  /*RS2*/
  46656,246,	  /*ST2*/
  46658,16464,  // Aj 0 mv
  46660,16472,  // Aj gan mV
  46662,16842,  //Aj Temp Amb
  46664,16480,  // 0 Pt100  
  46668,16488,  // gan Pt100
  
};

#endif

#endif


unsigned short int calculate_crc(unsigned char *z_p,unsigned char z_message_length);


//////////////Comunicacion//////////
byte StepTx;  //Pasos en la transmisión
bool AS1_Tx;
static byte cantidad_mensajes;  // cantidad de mensajes a enviar sin el CRC
byte ASespera;
byte Step=0;
extern bool DSave;
byte msn[16];
byte msn_out[16];
word crc;
word Address,Data;
//////////////////////////////////
							
#ifdef _NMODBUS
/*  Funcion interna implementada para compatibilidad con el Soft del aparato viejo*/
word ConseguirDirNueva(word Addr){
  if (Addr<TablaDirs[0].dir_v || Addr>TablaDirs[NUM_DIRS-1].dir_v)
    return Addr;
  else{
  word l=0, r=NUM_DIRS-1,i;
    while((l < r) && (r - l > 1)){
      if(TablaDirs[l].dir_v==Addr)
        return TablaDirs[l].dir_n;
      else if (TablaDirs[r].dir_v==Addr)
        return TablaDirs[r].dir_n;
      else{
      i = (l + r) / 2;
       if (Addr > TablaDirs[i].dir_v)
         l = i;
       else
         if (Addr < TablaDirs[i].dir_v)
           r = i;
      else 
           return TablaDirs[i].dir_n;
      }
    }
    return Addr;
  }
}

word AdaptarVAlorIn(word Val,word Address){
  switch (Address){
    case 268:  /*numero de Segmento*/
      Val--;
  }
  return Val;
}

word AdaptarVAlorOut(word Val,word Address){
  switch(Address){
    case 60:									 /*Decimales*/
    			  
    			   switch(Val){
    			    case 0:Val=1;
    			          break;
    			    case 1:Val=0;
    			          break;
    			    case 2: Val = 10;
    			          break;
    			    case 3: Val = 11;	 
    			   }
    			   
      break;
    case 0x1010:			/*Potencias*/
    case 0x1012:
    case 0x1014:
    case 0x1016:
    case 0x1018:
    case 0x101A:
    case 0x101C:
    case 0x101E:
    		 Val=(int)((long)Val*255/1000);
    break;
    #ifdef programador
    case 300:	 /*TieSeg*/
      Val= SegundosSegmento[0]/60;
      break;
    #endif
    case 268:  /*numero de Segmento*/
      Val--;
  }
  
  return Val;
}
#endif

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

void ModBus_Recive(AS1_TComData dat)
{ byte i;
  
  msn[Step]=dat;
  switch(Step){
    
    case 0:    
      if (ASespera!=0 || msn[0]!= PRom[R_Id] || StepTx)
        break;
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
 					#ifdef _NMODBUS
 					 #ifdef _COM_VIEJA 
 					 Address=ConseguirDirNueva(Address);
 					 #endif
 					 if (msn[1]==3 || msn[1]==1){ //leer n palabras de 16 bits 
           word Address2;   
              if ( (COM_OFFSET+PARAMETROS *2)>=Address && Address>=COM_OFFSET)
                Address2 = (word)Parametros[(Address-COM_OFFSET)/2].Fdir;
              else
                Address2=Address;
              Data = *(word *) Address2 ;
              
              #ifdef _COM_VIEJA
                *(word *)&msn[4]=AdaptarVAlorOut(Data,Address);
              #else
                *(word *)&msn[4]=Data;
              #endif
              
              cantidad_mensajes=6;
           		AS1_Tx=TRUE;
           //   Timer_Run(1,&ASespera,UNICO_SET,ModBus_Send);
           //   trx_SetVal();
           //   AS1_SendChar(msn[0]); //empiezo envio
            
  				#else
  				 if (msn[1]==3 || msn[1]==4){ //leer n palabras de 16 bits
            if (msn[4]==0 && msn[5]==1)  
            { 
              
              msn[2]=msn[5]*2;
              if ( (COM_OFFSET+PARAMETROS *2)>=Address && Address>=COM_OFFSET)
                Address = (word)Parametros[(Address-COM_OFFSET)/2].Fdir;
              
              msn[3] = *(volatile byte *) Address ;
              msn[4] = *(volatile byte *)(Address+1) ;
              cantidad_mensajes=5;
              AS1_Tx=TRUE;
          //    Timer_Run(1,&ASespera,UNICO_SET,ModBus_Send);
           //   trx_SetVal();
           //   AS1_SendChar(msn[0]); //empiezo envio
            }
  				#endif
            #if FLASH_PARAMETROS_END < RAM_COMUNICACION_START
            #error revisar abajo
            #endif
           #ifdef _NMODBUS
            }else if (msn[1]==5||msn[1]==6){ //escribir una palabra de 16 bits
           #else
            }else if (msn[1]==6){
           #endif
              Data = *(word *)&msn[4];
              #ifdef _COM_VIEJA
              Data = AdaptarVAlorIn(Data,Address);
              #endif  
                if ( (COM_OFFSET+PARAMETROS *2)>=Address && Address>=COM_OFFSET){
                DSave=FALSE;
                Timer_Run(30,&DSave,UNICO_SET);
                Escribir(&Parametros[(Address-COM_OFFSET)/2],Data);
                }
                else if(Address >= RAM_COMUNICACION_START && Address <= RAM_COMUNICACION_END)
                *(volatile word*)Address =Data;													
                else if((Address >= FLASH_PARAMETROS_START && Address <= FLASH_PARAMETROS_END)
                #ifdef programador
                || (Address >= FLASH_PROGRAMADOR_START && Address <= FLASH_PROGRAMADOR_END)
								#endif
                ){
                DSave=FALSE;
                Timer_Run(30,&DSave,UNICO_SET);
                EscribirWord(Address,Data);
                } 
                cantidad_mensajes=6;
                AS1_Tx=TRUE;
              //  Timer_Run(1,&ASespera,UNICO_SET,ModBus_Send); // ASespera no tiene sentido, hay que modificar Timer_Run
             //   trx_SetVal();
             //   AS1_SendChar(msn[0]); //empiezo envio 
            
            }
            for(i=0;i<cantidad_mensajes;i++){
                msn_out[i]=msn[i];
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
void ModBus_Send(void)
{
 
if (StepTx == 0){// return;
 trx_SetVal();
 AS1_Tx=FALSE;
}

if (StepTx<cantidad_mensajes){
  
  if (AS1_SendChar(msn_out[StepTx])==ERR_OK) {
    
    StepTx++;
    if(StepTx==cantidad_mensajes) crc = calculate_crc(msn_out,cantidad_mensajes);
  }
} else if(StepTx==cantidad_mensajes) {
  if (AS1_SendChar(crc%256)==ERR_OK)
    StepTx++;
  
} else if(StepTx==cantidad_mensajes+1) { 											//CRC	 2
  if (AS1_SendChar(crc>>8)==ERR_OK){
   StepTx++; 
    }

} else if (StepTx==cantidad_mensajes+2) {
  //  if (AS1_GetTxComplete()){
    
    ASespera=3;
    AS1_Tx=FALSE;		//Termino el proceso de transmision
    StepTx=0;
    trx_ClrVal();
//		}

}/* else{		//out of bounds
    AS1_Tx=FALSE;
    StepTx=1;
    trx_ClrVal();
}

 */
}


/////////////////////////////////////////////////////////////////////////// 
 // Control del CRC para realizar las xor 

///////////////////////////////////////////////////////////////////////////
 #pragma CONST_SEG DEFAULT  

const unsigned int crc_control[]=	{

	0x0,  //0
	0xc0c1,  //1
	0xc181,  //2
	0x140,  //3
	0xc301,  //4
	0x3c0,  //5
	0x280,  //6
	0xc241,  //7
	0xc601,  //8
	0x6c0,  //9
	0x780,  //10
	0xc741,  //11
	0x500,  //12
	0xc5c1,  //13
	0xc481,  //14
	0x440,  //15
	0xcc01,  //16
	0xcc0,  //17
	0xd80,  //18
	0xcd41,  //19
	0xf00,  //20
	0xcfc1,  //21
	0xce81,  //22
	0xe40,  //23
	0xa00,  //24
	0xcac1,  //25
	0xcb81,  //26
	0xb40,  //27
	0xc901,  //28
	0x9c0,  //29
	0x880,  //30
	0xc841,  //31
	0xd801,  //32
	0x18c0,  //33
	0x1980,  //34
	0xd941,  //35
	0x1b00,  //36
	0xdbc1,  //37
	0xda81,  //38
	0x1a40,  //39
	0x1e00,  //40
	0xdec1,  //41
	0xdf81,  //42
	0x1f40,  //43
	0xdd01,  //44
	0x1dc0,  //45
	0x1c80,  //46
	0xdc41,  //47
	0x1400,  //48
	0xd4c1,  //49
	0xd581,  //50
	0x1540,  //51
	0xd701,  //52
	0x17c0,  //53
	0x1680,  //54
	0xd641,  //55
	0xd201,  //56
	0x12c0,  //57
	0x1380,  //58
	0xd341,  //59
	0x1100,  //60
	0xd1c1,  //61
	0xd081,  //62
	0x1040,  //63
	0xf001,  //64
	0x30c0,  //65
	0x3180,  //66
	0xf141,  //67
	0x3300,  //68
	0xf3c1,  //69
	0xf281,  //70
	0x3240,  //71
	0x3600,  //72
	0xf6c1,  //73
	0xf781,  //74
	0x3740,  //75
	0xf501,  //76
	0x35c0,  //77
	0x3480,  //78
	0xf441,  //79
	0x3c00,  //80
	0xfcc1,  //81
	0xfd81,  //82
	0x3d40,  //83
	0xff01,  //84
	0x3fc0,  //85
	0x3e80,  //86
	0xfe41,  //87
	0xfa01,  //88
	0x3ac0,  //89
	0x3b80,  //90
	0xfb41,  //91
	0x3900,  //92
	0xf9c1,  //93
	0xf881,  //94
	0x3840,  //95
	0x2800,  //96
	0xe8c1,  //97
	0xe981,  //98
	0x2940,  //99
	0xeb01,  //100
	0x2bc0,  //101
	0x2a80,  //102
	0xea41,  //103
	0xee01,  //104
	0x2ec0,  //105
	0x2f80,  //106
	0xef41,  //107
	0x2d00,  //108
	0xedc1,  //109
	0xec81,  //110
	0x2c40,  //111
	0xe401,  //112
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


unsigned short int calculate_crc(unsigned char *z_p,unsigned char z_message_length){

unsigned short int CRC= 0xffff;
unsigned short int next;

 while (z_message_length--){
   next = (unsigned short int)*z_p;
   CRC ^= next;
   CRC = crc_control[CRC%256]^(CRC/256);
   z_p++;
 }
 return CRC;
}