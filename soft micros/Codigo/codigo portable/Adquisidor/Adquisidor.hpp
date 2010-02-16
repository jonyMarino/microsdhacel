#ifndef _ADQUISIDOR_HPP
#define _ADQUISIDOR_HPP



#include <stdtypes.h>
#include "PE/include/PE_Types.h"
#include "Timer/RlxMTimer/RlxMTimer.hpp"
#include "FshTypeSizes.h"
#include "OOC/util/lib_cpp/Array.h"

/*Se encarga de ir guardando datos en la flash vacia, en caso de llenarse tiene 2 estrategias: ignorar las proximas escrituras o borrar la siguiente pagina para seguir escribiendo*/
class EstrategiaFlash{
  public:
    EstrategiaFlash(void * primerPagina,void* ultimaPagina);
    
    typedef enum{
      ERASENEXT,
      STOP
    }Estrategia;
    void setEstrategia(Estrategia);
    Estrategia getEstrategia();
    /*
    ** ===================================================================
    **     Method      :  borrarTodo
    **    Description  :  Borra todas las paginas de la flash manejada 
    ** ===================================================================
    */
    void borrarTodo();
  private:
    Estrategia estrategia;
    word * ActualAddr;					          //Direccion actual donde grabar los datos 
    word * OlderPageAddr;
    void (*pfMemFullStrategy)(void*,word*);	/* puntero a funcion del metodo que 
                                        ejecuta la estrategia de memoria llena  
                                        */ 
    void * primerPagina;
    void * ultimaPagina;
    
    void borrarPagina(word * page);
    /*
    ** ===================================================================
    **     Method      :  Adq_BorrarPagina
    **    Description  :  Obtiene la pagina que esta siendo usada y 
    **                  no puede borrarse.
    ** ===================================================================
    */
    void* getPaginaActual();                                    
};

class ConfiguracionAdquisidor{
  public:
    virtual bool getAdquirir()=0;
    virtual void setAdquirir(bool)=0;
    virtual int getIntervalo()=0;
    virtual void setAdquirir(int)=0;    
    virtual EstrategiaFlash::Estrategia getEstrategia()=0;
    virtual void setEstrategia(EstrategiaFlash::Estrategia)=0;              
};

class Adquisidor{
  public:
    typedef enum{
      NO,
      SI,
      HULT,
      FULL  
    }Estado;
    class ElementoAdquirible{
      public:
         virtual const char * serializar(int& tamanio)=0;
         virtual const char * getDescripcion()=0;
         virtual byte getTipo()=0;
    };
    
    Adquisidor(const struct Array& serializables,ConfiguracionAdquisidor& configuracion);
    void start();
    void stop();
    Estado getEstado();
    bool getAdquirir();
    void setAdquirir(bool);
    int getIntervalo();
    void setAdquirir(int);    
    EstrategiaFlash::Estrategia getEstrategia();
    void setEstrategia(EstrategiaFlash::Estrategia);              

  private:
    typedef struct{
      word start_byte;
      byte year;		// 00-99 -> 2000 - 2099
      byte month;
      byte day;
      byte hour;
      byte min;
      byte secs;
      word intervalo; 
    }TEncabezado;
    const struct Array& serializables;
    ConfiguracionAdquisidor& configuracion;
    bool grabando;
    Estado estado;
    RlxMTimer timer;
    
    static void onTime(void*);
    void escribirStop();
    void escribirPowerdown();
    word sizeOfHeader();
    word sizeOfWriteParams();
};

#endif
