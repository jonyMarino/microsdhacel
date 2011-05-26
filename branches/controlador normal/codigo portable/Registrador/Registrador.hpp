#ifndef _REGISTRADOR_HPP
#define _REGISTRADOR_HPP



#include <stdtypes.h>
#include "PE/include/PE_Types.h"
#include "Timer/RlxMTimer/RlxMTimer.hpp"
#include "FshTypeSizes.h"
#include "OOC/util/lib_cpp/Array.h"


class ConfiguracionRegistrador{
  public:
    virtual byte getAdquirir()=0;
    virtual void setAdquirir(byte)=0;
    virtual int getIntervalo()=0;
    virtual void setIntervalo(int)=0;              
};

class ElementoRegistrable{
  public:
     typedef enum{
      TXT,
      NUMERICO,
      REAL
     }Tipo;
     virtual const char * serializar(int& tamanio)=0;
     virtual const char * getDescripcion()=0;
     virtual Tipo getTipo()=0;
};

class Registrador{
  public:
    typedef enum{
      NO,
      SI,
      HULT,
      FULL  
    }Estado;
        
    Registrador(const struct Array& serializables,ConfiguracionRegistrador& configuracion);
    void start();
    void stop();
    Estado getEstado();
    bool getAdquirir();
    void setAdquirir(bool);
    int getIntervalo();
    void setIntervalo(int);           
  protected:
    void setEstado(Estado);
    virtual void registrar()=0;
    const struct Array& getSerializables();
  private:
    //bool isTimeSet(void);
    const struct Array& serializables;
    ConfiguracionRegistrador& configuracion;
    bool grabando;
    Estado estado;
    RlxMTimer timer;    
    //Texto txt;
    static void onTime(void*);
    
};

#endif
