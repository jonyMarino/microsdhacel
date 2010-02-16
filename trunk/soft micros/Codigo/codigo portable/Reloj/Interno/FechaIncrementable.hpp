#ifndef _FECHA_INCREMENTABLE_HPP
#define _FECHA_INCREMENTABLE_HPP


#include "FechaTiempo.hpp"
                

  
class FechaIncrementable:public FechaTiempo{  
  public:
    FechaIncrementable(word anio,byte mes,byte dia,byte hora,byte min,byte segs);
    virtual void getTiempo(TIMEREC *time);
    virtual void getFecha(DATEREC *date);
  protected:
    void incrementar(dword segundos);
    virtual void setTiempoValidado(byte hour,byte min,byte secs);
    virtual void setFechaValidada(word year,byte month,byte day);
  private:
    byte cntDia;                    /* Day counter */
    byte cntMes;                    /* Month counter */
    word cntAnio;                   /* Year Counter */
    dword totalHthL;                
};


#endif 

