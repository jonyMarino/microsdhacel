#ifndef _BASETIEMPO_H
#define _BASETIEMPO_H


#include "TmDt1.h"

#include "RlxMTimer.h"


/*C++ 
class BaseTiempo:public TmDt1
{
 public:
   BaseTiempo(word Year,byte Month,byte Day,byte Hour,byte Min,byte secs,bool start);
   bool BaseTiempo_habilitada(void);
   void BaseTiempo_habilitar(bool habilitar);
   bool BaseTiempo_getConfigurado(void);

  private:
    void (*inc1Segundo)(void);
    int segundosAcumulados;
    struct RlxMTimer timer;
    bool configurado; 
}
*/
struct BaseTiempoClass{
  struct TmDt1Class super;
  void (*inc1Segundo)(void * _self);
};

struct BaseTiempo {
  struct TmDt1 super;
  int segundosAcumulados;
  struct RlxMTimer timer;
  bool configurado;
};

#define BASE_TIEMPO_CLASS_INITIALIZATION(description,name,super,contructor,destructor,differ,puto,getTime,setTime,getDate,setDate,inc1Segundo)\
  TMDT1_CLASS_INITIALIZATION(description,name,super,contructor,destructor,differ,puto,getTime,setTime,getDate,setDate),\
  inc1Segundo
  
extern const struct Class BaseTiempoClass;
extern const struct BaseTiempoClass BaseTiempo;

bool BaseTiempo_habilitada(void * _self);
void BaseTiempo_habilitar(void * _self,bool habilitar);

bool BaseTiempo_getConfigurado(void * _self);

#endif
