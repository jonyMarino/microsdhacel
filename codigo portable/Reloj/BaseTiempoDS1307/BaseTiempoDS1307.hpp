#ifndef _BASE_TIEMPO_DS1307_HPP
#define _BASE_TIEMPO_DS1307_HPP


#include "FechaIncrementable.hpp"
#include "Timer/RlxMTimer/RlxMTimer.hpp"


class BaseTiempoDS1307:public FechaTiempo{
  public:
    BaseTiempoDS1307();
    virtual void getTiempo(TIMEREC *time);
    virtual void getFecha(DATEREC *date);
  protected:
    virtual void setTiempoValidado(byte hour,byte min,byte secs);
    virtual void setFechaValidada(word year,byte month,byte day);
  private:
    
    
};

#endif
