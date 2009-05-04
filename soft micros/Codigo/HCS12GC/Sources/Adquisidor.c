/*  MODULE:Adquisidor. 
**     Filename  : Adquisidor.C
**     Project   : Adquisidor
**     Processor : MC9S12GC32CFU16
**     Version   : 0.0.2
**     Compiler  : Metrowerks HC12 C Compiler
**     Date/Time : 19/03/2008, 11:59
**     Abstract  :
**           Guarda valores de GetterVisual o sensor
*/

#include <stdlib.h>
#include "PE_Types.h"
#include "stdtypes.h"
#include "Adquisidor.h"
#include "IFsh10.h"
#include "Grabacion.h"
#include "PromBkp.h"
#include "System.h"
#include "IFshMem.h"

#define SPECIAL_KEY 32000		 //indica que el siguiente Word es un special key

#define _START_BYTE              1
//#define _NEW_BYTE                2
#define _STOPPED_BYTE            3							
#define _POWER_DOWN_BYTE         4
#define _CONTINUE_NEXT_PAGE_BYTE 5
#define _MEM_FULL                6
#define _PREV_VAL_m1             7  //indica que el valor anterior fue un -1 para distingirlo de flash no grabada


void Adq_DefConstructor(void * self,va_list * args);
void Adq_Handler(void * self);
void Adq_OnErase(void * _self,word * Page);
void Adq_Escribir_Stop(void* _self);
void Adq_Escribir_NextPage(void* _self,word size);
void Adq_StopOnMemFull(void * self,word *nextPage);
void Adq_EraseOnMemFull(void * _self,word* nextPage);
byte Adq_SerchActualAddr(void * _self);
void Adq_Escribir_Powerdown(void* _self);
void Adq_Grabar_Parametros(void* _self);
void Adq_Escribir_Header(void * _self);

const struct Class Adquisidor={
  &Class,
  "",
  &Object,
  sizeof(struct Adquisidor),
  Adq_DefConstructor,
  NULL,
  NULL 
};


typedef struct{
  word start_byte;
  byte year;		// 00-99 -> 2000 - 2099
  byte month;
  byte day;
  byte hour;
  byte min;
  byte secs;
  word intervalo; 
}AdqHeader;

const char *const strs_AdqEstados[]={
      "no  ",									
			"Si  ",
			"HLt ",
			"FULL"
};

const char *const Adq_strategy_str[]={
      "ErASE",									
			"StoP"
};

void onDateTimeChange(void * _self){
  Adq_Stop(_self);
}

/*
** ===================================================================
**     Method      :  Adq_Constructor 
**    Description  :  Constructor del Objeto
** ===================================================================
*/
void Adq_Constructor(void * _self,struct AdqConf * conf,struct Sensor * sensor){
  struct Adquisidor * _ad = _self;
  
  //PromBkp_addPostBorrarListener(pFlash,Adq_OnErase,self);  
  _ad->_conf=conf;
  _ad->sensor = sensor;
  
  //addOnDateChageListener(&baseTiempo,onDateChange,self);

  if(conf->Estrategia==ADQ_ERASEMEM)
    _ad->pfMemFullStrategy=Adq_EraseOnMemFull ; 
  else
    _ad->pfMemFullStrategy=Adq_StopOnMemFull ; 
  
  _ad->Adq_Timer=new(&RlxMTimer,(ulong)Adq_getIntervalo(_self)*1000,Adq_Handler,_self);
  Timer_Stop(_ad->Adq_Timer);
	
	if(Adq_SerchActualAddr(_self)==_MEM_FULL)	 // Busca el indice para grabar parametros adquiridos
	{
	  _ad->Estado_Adquisicion = ADQ_FULL;  
	  _MANEJADOR_MEMORIA_SET_BYTE(pFlash,&_ad->_conf->Adquirir,0);		 // Poner la adquisición en no
	} 
	else if (_ad->_conf->Adquirir==TRUE) {		 // la adquisición quedo en si al apagarse el equipo?								  
	  Adq_Escribir_Powerdown(_self);  // Header que indica que hubo un corte de Energia durante la adquisición
	  _ad->Estado_Adquisicion = ADQ_HULT;// Cartel en HLT (hult) por corte de energia
	  _MANEJADOR_MEMORIA_SET_BYTE(pFlash,&_ad->_conf->Adquirir,0);		 // Poner la adquisición en no
  }else
    _ad->Estado_Adquisicion = ADQ_NO;  //no

}

/*
** ===================================================================
**     Method      :  Adq_DefConstructor 
**    Description :   Constructor por defecto
** ===================================================================
*/
void Adq_DefConstructor(void * self,va_list * args){
  Adq_Constructor(self,va_arg(*args,struct AdqConf *),va_arg(*args,struct Sensor *));  
}

/*
** ===================================================================
**     Method      :  Adq_Handler 
**    Type:        :  Private
**    Description  :  Manejador del Adquisidor
** ===================================================================
*/
void Adq_Handler(void * self){
  struct Adquisidor * _ad = self;
  
  if (_ad->Estado_Adquisicion==ADQ_YES){
    Adq_Grabar_Parametros(self);
  }

}

/*
** ===================================================================
**     Method      :  Adq_isTimeSet
**    Description  :  indica si se introdujo el tiempo
** ===================================================================
*/
bool Adq_isTimeSet(void *_self){
  struct Adquisidor * _ad = _self;
  
  return isConfigurado(&baseTiempo);   
}

/*
** ===================================================================
**     Method      :  Adq_Start
**    Description  :  Empieza la adquisicion (si es que la memoria no
**                    se encuentra en full)
** ===================================================================
*/
void Adq_Start(void *_self){
   struct Adquisidor * _ad = _self;
  
  if(_ad->Estado_Adquisicion==ADQ_FULL){
    #warning cambiar por: y llamar a un envento al termino del boorado
    //PromBkp_borrarPagina(pFlash,_ad->ActualAddr);
    EraseSectorInternal(_ad->ActualAddr);    
    
  }
  if(_ad->Estado_Adquisicion!=ADQ_YES){    
    Timer_setTime(_ad->Adq_Timer,((ulong)Adq_getIntervalo(_self))*1000);
    _ad->Estado_Adquisicion=ADQ_YES;
    _MANEJADOR_MEMORIA_SET_BYTE(pFlash,&_ad->_conf->Adquirir,1);
    Adq_Escribir_Header(_self);
  }
}




/*
** ===================================================================
**     Method      :  Adq_Stop 
**    Description  :  Detiene la adquisicion
** ===================================================================
*/
void Adq_Stop(void *_self){
  struct Adquisidor * _ad = _self;
  
 // if((BajoConsumo == TRUE)&&(estado == TRUE))    //BajoConsumo: true (esta en bajo consumo(BC))
 //   estado = TRUE;                               //             false (no esta en bajo consumo)
 // else                                           // estado: true (estaba adquiriendo, antes de entrar en BC)
 //   estado = FALSE;                              //         false (no estaba adquiriendo, antes de entrar en BC)
  
  if(_ad->Estado_Adquisicion==ADQ_YES){
    _ad->Estado_Adquisicion=ADQ_NO;
    _MANEJADOR_MEMORIA_SET_BYTE(pFlash,&_ad->_conf->Adquirir,0);
   
    // Adq_Handler(_self);         //nico  
    Adq_Escribir_Stop(_self); 
   
  }
}

/*
** ===================================================================
**     Method      :  Adq_StopOnMemFull		
**    Description  :  Estrategia 1 ante memoria llena
** ===================================================================
*/
void Adq_StopOnMemFull(void * _self,word* nextPage){
  struct Adquisidor * _ad = _self;
  
  WriteWord( _ad->ActualAddr  , SPECIAL_KEY);
  _ad->ActualAddr++;
  WriteWord( _ad->ActualAddr  , _MEM_FULL); 
  
  _ad->Estado_Adquisicion= ADQ_FULL;
  _MANEJADOR_MEMORIA_SET_BYTE(pFlash,&_ad->_conf->Adquirir,0);		 // Poner la adquisición en no
 
  _ad->ActualAddr=nextPage;
     
}

/*
** ===================================================================
**     Method      :  Adq_EraseOnMemFull
**    Description  :  Estrategia 2 ante memoria llena
** ===================================================================
*/
void Adq_EraseOnMemFull(void * _self,word* nextPage){
  struct Adquisidor * _ad = _self;
  PromBkp_borrarPagina(pFlash,nextPage);  
  Adq_Escribir_NextPage(_self,(word)nextPage);
  _ad->ActualAddr= nextPage;
}


/*
** ===================================================================
**     Method      :  Adq_OnErase
**    Description  :  Evento a llamar cuando se Borro la pagina
** ===================================================================
*/
void Adq_OnErase(void * _self,word * Page){
  struct Adquisidor * _ad = _self;
  if(_ad->pfMemFullStrategy==Adq_EraseOnMemFull)
    if(_ad->ActualAddr == Page)
      Adq_Escribir_Header(_self);  
}

/*
** ===================================================================
**     Method      :  Adq_SizeOfHeader 
**    Type         :  Private
**    Description  :  Devuelve el tamanio del encabezado
** ===================================================================
*/
word Adq_SizeOfHeader(void * _self){
  return sizeof(AdqHeader);
}
/*
** ===================================================================
**     Method      :  Adq_SizeOfWriteParams 
**    Type         :  Private
**    Description  :  Devuelve el tamanio de la escritura de parametros
** ===================================================================
*/
word Adq_SizeOfWriteParams(void * _self){
  return sizeof(word)*2;
}
/*
** ===================================================================
**     Method      :  Adq_CheckPageMem 
**    Description  :  Checkea si hay memoria en la pagina para grabar
**      max_next_size bytes, sino pasa a la siguiente pagina, si ésta 
**      esta escrita utiliza la estrategia elegida. 
** ===================================================================
*/
void Adq_CheckPageMem(void * self, word max_next_size){
  struct Adquisidor * _ad = self;
  byte Escnextpage_size= sizeof(word)*2;
  
  if( PAGE_SIZE-((word)_ad->ActualAddr&(PAGE_SIZE-1)) < max_next_size+Escnextpage_size){		
                            // No hay suficiente memoria en la pagina?
    word next_PageAddr = (((word)_ad->ActualAddr)&65024) + PAGE_SIZE;
    if(next_PageAddr >= (word)_ad->_conf->MemAddrEnd) // Memoria excedida
      next_PageAddr = (word)_ad->_conf->MemAddrStart;//vuelvo al inicio de la memoria
    if(*(word*)next_PageAddr!=0xFFFF)  // La siguiente pagina ya esta escrita
      (*(_ad->pfMemFullStrategy))(self,(word*)next_PageAddr);                  
    else{
      Adq_Escribir_NextPage(self,next_PageAddr);
      _ad->ActualAddr= (word*)next_PageAddr;
      Adq_Escribir_Header(self);
    }
  }
      
}


/*
** ===================================================================
**     Method      :  Adq_Escribir_Header 
**    Description  :  Escribe el encabezado en la direccion actual
** ===================================================================
*/
void Adq_OnWriteErr(void * _self,uchar err){
  struct Adquisidor * _ad = _self;
}


/*
** ===================================================================
**     Method      :  Adq_Escribir_Header 
**    Description  :  Escribe el encabezado en la direccion actual
** ===================================================================
*/
void Adq_Escribir_Header(void * _self){
  struct Adquisidor * _ad = _self;
  byte i;
  DATEREC Fecha;
  TIMEREC Tiempo;
  AdqHeader header;
  const byte header_WordSize = (Adq_SizeOfHeader(_self)+sizeof(word)/2)/sizeof(word);
  
  Sys_getDate(&Fecha);
  Sys_getTime(&Tiempo);
  
  header.start_byte= _START_BYTE;
  
  header.year = Fecha.Year-2000;
  header.month = Fecha.Month;
  header.day  = Fecha.Day;
  
  header.hour = Tiempo.Hour;
  header.min  = Tiempo.Min;
  header.secs = Tiempo.Sec;
  
  header.intervalo=Adq_getIntervalo(_self);
  
  for(i=0;i<header_WordSize;i++){
    byte err;
    err=WriteWord(_ad->ActualAddr  , *((word*)&header+i)); 
    _ad->ActualAddr++;
    if(err)
      Adq_OnWriteErr(_ad,err); 
  }
  
  Adq_Grabar_Parametros(_self); //Escribir el primer valor
  
  Adq_CheckPageMem(_self,Adq_SizeOfWriteParams(_self));  /*checkeo si 
                                                  queda memoria en la 
                                                  pagina para grabar 
                                                  los parametros
                                                  */
}

/*
** ===================================================================
**     Method      :  Adq_Grabar_Parametros 
**    Description  :  Escribe los parametros junto con el word de new
**                    en la direccion actual
** ===================================================================
*/
void Adq_Grabar_Parametros(void* _self) {
  struct Adquisidor * _ad = _self;


  int val= _Getter_getVal(_ad->sensor);
  byte i;
  
  WriteWord(_ad->ActualAddr,val); 
  _ad->ActualAddr++;
  
  if(val==SPECIAL_KEY){
        WriteWord(_ad->ActualAddr,val);  //si el valor es el de un key lo repite
        _ad->ActualAddr++;
  }

  if(val==-1){							//si el valor fue menos 1, lo indico
    WriteWord(_ad->ActualAddr,_PREV_VAL_m1); 
    _ad->ActualAddr++;   
  }
  
  Adq_CheckPageMem(_self,Adq_SizeOfWriteParams(_self));/*checkeo si 
                                                    queda memoria en
                                                    la pagina para
                                                    grabar mas 
                                                    parametros
                                                    */
}

/*
** ===================================================================
**     Method      :  Adq_Escribir_Powerdown 
**    Description  :  Escribe en la direccion actual, que hubo 
**                    una caida de energia
** ===================================================================
*/
void Adq_Escribir_Powerdown(void* _self){
  struct Adquisidor * _ad = _self;
  
  if(*(int*)(_ad->ActualAddr-1)==_POWER_DOWN_BYTE)  //powerdown ya esta escrito??
    return; 
  
 
  WriteWord(_ad->ActualAddr,SPECIAL_KEY);  //Power down word
  _ad->ActualAddr++;
  WriteWord(_ad->ActualAddr,_POWER_DOWN_BYTE);  //Power down word
  _ad->ActualAddr++;
  Adq_CheckPageMem(_self,
    Adq_SizeOfHeader(_self) + Adq_SizeOfWriteParams(_self));/*checkeo si 
                                                    queda memoria en
                                                    la pagina para
                                                    grabar el
                                                    header
                                                    */ 
}

/*
** ===================================================================
**     Method      :  Adq_Escribir_Stop 
**    Description  :  Escribe en la direccion actual, que se detuvo
**                   la adquisicion por orden del usuario
** ===================================================================
*/
void Adq_Escribir_Stop(void* _self){
  struct Adquisidor * _ad = _self;
  
    WriteWord(_ad->ActualAddr,SPECIAL_KEY);  //Power down word
  _ad->ActualAddr++;
  WriteWord(_ad->ActualAddr,_STOPPED_BYTE);  //Stop word
  _ad->ActualAddr++;
  Adq_CheckPageMem(_self,
    Adq_SizeOfHeader(_self) + Adq_SizeOfWriteParams(_self));/*checkeo si 
                                                    queda memoria en
                                                    la pagina para
                                                    grabar el
                                                    header
                                                    */ 
}

/*
** ===================================================================
**     Method      :  Adq_Escribir_NextPage 
**    Description  :  Escribe en la direccion actual, que 
** ===================================================================
*/
void Adq_Escribir_NextPage(void* _self,word addr){
  struct Adquisidor * _ad = _self;
  
    WriteWord(_ad->ActualAddr,SPECIAL_KEY);  //Power down word
  _ad->ActualAddr++;
  WriteWord(_ad->ActualAddr,_CONTINUE_NEXT_PAGE_BYTE);  //Power down word
  _ad->ActualAddr++;
  WriteWord(_ad->ActualAddr,addr);  //Power down word
}

/*
** ===================================================================
**     Method      :  Adq_getActualState
**    Description  :  Obtiene el estado del adquisidor (      "no  ",									
**			"Si  ",
**			"HLt ",
**			"FULL")
** ===================================================================
*/
int  Adq_getActualState(void * _self){
  struct Adquisidor * _ad = _self;
  return _ad->Estado_Adquisicion;
}

/*
** ===================================================================
**     Method      :  Adq_SetState
**    Description  :  Setea el estado del adquisidor (NO/YES)
** ===================================================================
*/
TError  Adq_SetState(void * _self, int val){
  struct Adquisidor * _ad = _self;
  byte err;
  

  err=_MANEJADOR_MEMORIA_SET_BYTE(pFlash,&_ad->_conf->Adquirir,val);
  if(!err){
    if(val==FALSE){
      Adq_Stop(_self);
    }else{
      Adq_Start(_self);
    }
  }
  return err;
}

/*
** ===================================================================
**     Method      :  Adq_getState
**    Description  :  Setea el estado del adquisidor (NO/YES)
** ===================================================================
*/
int  Adq_getState(void * _self){
  struct Adquisidor * _ad = _self;
  return _MANEJADOR_MEMORIA_GET_BYTE(pFlash,&_ad->_conf->Adquirir);
}

/*
** ===================================================================
**     Method      :  Adq_StateLimSup
**    Description  :  Limite Superior de estado
** ===================================================================
*/
int Adq_StateLimSup(void*_self){
  struct Adquisidor * self = _self;  
  
  if(self->Estado_Adquisicion == ADQ_FULL && Adq_getStrategy(self)!=ADQ_ERASEMEM)
    return 0;
  return 1;
}
/*
** ===================================================================
**     Method      :  Adq_StateLimInf
**    Description  :  Limite Inferior de estado
** ===================================================================
*/
int Adq_StateLimInf(void*_self){
  return 0;
}
/*
** ===================================================================
**     Method      :  Adq_getStateStr
**    Description  :  Obtiene el string de state
** ===================================================================
*/
char * Adq_getStateStr(byte num){
  return strs_AdqEstados[num];   
}
/*
** ===================================================================
**     Method      :  Adq_SetStrategy
**    Description  :  Setea la estrategia ante memoria llena
** ===================================================================
*/
TError  Adq_setStrategy(void * _self, int val){
  struct Adquisidor * _ad = _self;
  byte err;
  

  err=_MANEJADOR_MEMORIA_SET_BYTE(pFlash,&_ad->_conf->Estrategia,val);
  if(!err){
    if(val==ADQ_ERASEMEM)
      _ad->pfMemFullStrategy=Adq_EraseOnMemFull ; 
    else
      _ad->pfMemFullStrategy=Adq_StopOnMemFull ;          //ver
  }
  return err;
}

/*
** ===================================================================
**     Method      :  Adq_getState
**    Description  :  Obtiene la estrategia ante memoria llena
** ===================================================================
*/
int  Adq_getStrategy(void * _self){
  struct Adquisidor * _ad = _self;
  return _ad->_conf->Estrategia; 
}

/*
** ===================================================================
**     Method      :  Adq_LimSupStrategy
**    Description  :  Limite Superios del valor de estrategia
** ===================================================================
*/
int  Adq_LimSupStrategy(void * _self){
  return _MAX_VALUE_ADQ_STRATEGY;  
}
/*
** ===================================================================
**     Method      :  Adq_getStrStrategy
**    Description  :  Textos de estrategia
** ===================================================================
*/
char * Adq_getStrStrategy(uchar num){
  return Adq_strategy_str[num];  
}



/*
** ===================================================================
**     Method      :  Adq_setIntervalo
**    Description  :  Setea el intervalo de muestreo
** ===================================================================
*/
TError Adq_setIntervalo(void * _self,int val){
  struct Adquisidor * _ad = _self;  
  byte err= _MANEJADOR_MEMORIA_SET_WORD(pFlash,&_ad->_conf->intervalo,val);
  if(!err){
    Adq_Stop(_self);
    
    if(!_ad->Adq_Timer){      
      _ad->Adq_Timer=new(&RlxMTimer,((ulong)val)*1000,Adq_Handler,_self);
      if(!_ad->Adq_Timer)
        return; //error
    }else
      Timer_setTime(_ad->Adq_Timer,((ulong)val)*1000);
  }
  return err;
}


/*
** ===================================================================
**     Method      :  Adq_getIntervalo
**    Description  :  Obtiene el intervalo de muestreo
** ===================================================================
*/
int Adq_getIntervalo(void * _self){
  struct Adquisidor * _ad = _self;  
  
  return _MANEJADOR_MEMORIA_GET_WORD(pFlash,&(_ad->_conf->intervalo));
}
/*
** ===================================================================
**     Method      :  Adq_LimInfIntervalo
**    Description  :  Limite Inferior de Intervalo
** ===================================================================
*/
int Adq_LimInfIntervalo(void * _self){
  return 1;
}


/*
** ===================================================================
**     Method      :  Adq_BorrarPage
**    Description  :  Estando el _ADQUISIDOR en FULL,
**                    si se borra la pagina siguiente a la que se esta
**                    escribiendo, el estado del _ADQUISIDOR pasara de 
**                    "FULL" a "no  ". 
** ===================================================================
*/
TError Adq_ErasePage(void* _self, word * page){
  struct Adquisidor * _ad = _self;
  
  if(_ad->Estado_Adquisicion==ADQ_FULL){
    if( ((word)page&65024) == ((word)_ad->ActualAddr&65024)){
      _ad->ActualAddr=(word*)((word)page&65024);
      _ad->Estado_Adquisicion=ADQ_NO;  
    }
      PromBkp_borrarPagina(pFlash,(word)_ad->ActualAddr);
    return;
  }
  if( _ad->Estado_Adquisicion==ADQ_YES && ((word)page&65024) == ((word)_ad->ActualAddr&65024) )
    return ERR_VALUE;
  if(((word)page&65024) == ((word)_ad->ActualAddr&65024))
    *(word*)&_ad->ActualAddr = ((word)_ad->ActualAddr&65024);
  PromBkp_borrarPagina(pFlash,(word)page);  
  return ERR_OK;
  
}
				
/*
** ===================================================================
**     Method      :  Adq_ErasePages
**    Description  :  Borra todas las paginas del adquisidor 
** ===================================================================
*/
TError Adq_ErasePages(void* _self, word ok){
  struct Adquisidor * _ad = _self;
  
  if(ok){										
    word addr;
    for(addr=(word)_ad->_conf->MemAddrStart;addr<(word)_ad->_conf->MemAddrEnd;addr+=PAGE_SIZE){
      Adq_ErasePage(_ad,(word*)addr);  
    } 						 
  }
  return ERR_OK; 
}

/*
** ===================================================================
**     Method      :  Adq_BorrarPagina
**    Description  :  Obtiene la pagina que esta siendo usada y 
**                  no puede borrarse.
** ===================================================================
*/
int Adq_getPaginaActual(void* _self){
  struct Adquisidor * _ad = _self;
  return (int)_ad->ActualAddr;  
}

/*
** ===================================================================
**     Method      :  Adq_getPaginasStart
**    Description  :  Dirección donde comienzan las paginas
** ===================================================================
*/
int Adq_getPaginasStart(void* _self){
  struct Adquisidor * _ad = _self;
  return (word)_ad->_conf->MemAddrStart;
}

/*
** ===================================================================
**     Method      :  Adq_getPaginasEnd
**    Description  :  Direccion donde terminan las paginas
** ===================================================================
*/
int Adq_getPaginasEnd(void* _self){
  struct Adquisidor * _ad = _self;
  return (word)_ad->_conf->MemAddrEnd;
}


/*
** ===================================================================
**     Method      :  Adq_SerchActualPage
**    Description  :  Busca cual es la direccion para grabar actual 
** ===================================================================
*/
byte Adq_SerchActualAddr(void * _self){
  struct Adquisidor * _ad = _self;
  const byte header_WordSize = (Adq_SizeOfHeader(_self)+sizeof(word)/2)/sizeof(word);
  const byte Params_WordSize =(Adq_SizeOfWriteParams(_self)+sizeof(word)/2)/sizeof(word);
  
  _ad->ActualAddr= _ad->_conf->MemAddrStart;
  
  while(_ad->ActualAddr<_ad->_conf->MemAddrEnd){
    
    if(*_ad->ActualAddr==_START_BYTE)
      _ad->ActualAddr+=header_WordSize;  
    
    if(*_ad->ActualAddr==SPECIAL_KEY){
      _ad->ActualAddr++;
      if(*_ad->ActualAddr==_MEM_FULL){
        _ad->ActualAddr++; 
        return _MEM_FULL;
      }else if(*_ad->ActualAddr==_CONTINUE_NEXT_PAGE_BYTE){
        word next;
        _ad->ActualAddr++;
        next = (*_ad->ActualAddr);//dir of next page 
        if(*(word*)&_ad->ActualAddr>next)				//pegue la vuelta sin detenerme?
          return _MEM_FULL;
        //sino
        *(word*)&_ad->ActualAddr=next;
      }else
        _ad->ActualAddr++; 
    }
    else if(*_ad->ActualAddr==-1 && *(_ad->ActualAddr+1)!=_PREV_VAL_m1)  //FLASH no grabada??
      return 0; 
    else
      _ad->ActualAddr++;  
  }

}



