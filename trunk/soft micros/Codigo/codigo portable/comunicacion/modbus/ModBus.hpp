#ifndef _MODBUS_HPP
#define _MODBUS_HPP

#include "NodoICModBus.hpp"
//#include "puertoSerie1.h"
#include "MethodTimer.hpp"
#include "PromBkp.hpp"

#pragma DATA_SEG ModBus_DATA                                            
#pragma CODE_SEG ModBus_CODE 
#pragma CONST_SEG DEFAULT

#define _COMP_OPTIONS 0

#define FUNCION_ESTATICA_INTERMEDIA_DE(clase,funcion) \
  void funcion(void);                             \
    static void funcion##Intermedia(void*_self){  \
    clase * self = (clase*)self;                \
    self->funcion;                              \
  }                                             
  
  

class ConfiguracionModBus{
  public:
    virtual int getId()=0;
};

class ModBus{
  public:
    ModBus(ConfiguracionModBus& configuracion,const struct Array/*<NodoICModBus>*/ *comProps,PromBkp*prom=NULL);
    
    /*
    ** ===================================================================
    **     Method      :  ModBus_Send
    **
    **     Description :
    **         llamar a esta funcion para enviar un mensaje por el puerto 
    **     serie
    ** ===================================================================
    */
    byte send(byte * data,byte cant);

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
    void onRxChar(byte dat);

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
    void onTxComplete(void);
    
    typedef struct {
      byte id; // numero en el byte 2 recibido
      byte (*onFuncion) (void * self,const byte *);  
    }T_OnRecive;
    
  private:
    class EscrituraDemorada{
      public:
        EscrituraDemorada(NodoICModBus& nodo,void * dir,uint dato);
        void escribir();
      private:
        NodoICModBus& nodo;
        void * dir;
        uint dato;
    };

    
    ConfiguracionModBus& configuracion;
    const struct Array/*<NodoICModBus>*/ *comProps;
    //EscrituraDemorada escrituraDemorada;
    EscrituraDemorada * pEscrituraDemorada;
    static byte cantMsjsOut;  // cantidad de mensajes a enviar sin el CRC
    word step;
    word address;
    word crc;
    bool asTx; 
    byte msj[16];
    struct Method& mOnTime;
    MethodTimer timer;
    static const unsigned int crcControl[256];
    static const T_OnRecive onRecive[6];
    void (*onSend)(void*);
    PromBkp * prom;
    
    
    void setOnSend(void (*pf)(void*));

    static byte dhacelRead(void*,byte * data);

    static byte modBusRead(void*,byte * data);

    static byte modBusWrite(void*,byte * data);
    
    word getAddressData(word address);
    
    byte writeAddress(word address,int dato);

    /*
    ** ===================================================================
    **    Function    : getCompilacion 
    **    Description : Devuelve las opciones de compilacion
    ** ===================================================================
    */
    byte getCompilacion(byte * data);
    
    static void onTimePass(void*);
    
    static unsigned short int calcularCrc(unsigned char *z_p,unsigned char z_message_length);

    FUNCION_ESTATICA_INTERMEDIA_DE(ModBus,sending);
    
    FUNCION_ESTATICA_INTERMEDIA_DE(ModBus, sendRead);
    FUNCION_ESTATICA_INTERMEDIA_DE(ModBus, sendNextRead);
    FUNCION_ESTATICA_INTERMEDIA_DE(ModBus, sendCRC);

    void escribirDatoEnCola(void);
    static void* escribirDatoEnColaIntermedia(void*);

};






#pragma DATA_SEG DEFAULT                                            
#pragma CODE_SEG DEFAULT 
#pragma CONST_SEG DEFAULT

#endif