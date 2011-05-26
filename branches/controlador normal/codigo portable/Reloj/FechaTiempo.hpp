#ifndef _FECHA_TIEMPO_HPP
#define _FECHA_TIEMPO_HPP

#include "PE/include/PE_Types.h"

class FechaTiempo{
  public:
    typedef struct { /* It contains actual number of hours, minutes, seconds and hundreths of seconds. */
      byte Hour; /* hours (0 - 23) */
      byte Min; /* minutes (0 - 59) */
      byte Sec; /* seconds (0 - 59) */
    } TIMEREC;


    typedef struct { /* It contains actual year, month, and day description. */
      word Year; /* years (1998 - 2099) */
      byte Month; /* months (1 - 12) */
      byte Day; /* days (1 - 28/31) */
    } DATEREC;
    
    virtual void getTiempo(TIMEREC *time)=0;
    virtual void getFecha(DATEREC *date)=0;
    byte setTiempo(byte hour,byte min,byte secs);
    byte setFecha(word year,byte month,byte day);
    static bool isTiempoValido(byte hora,byte min,byte segs);
    static bool isFechaValida(word anio,byte mes,byte dia);
    static byte getMaximoDiaDelMes(word Year,byte Month);
    
  protected:
    virtual void setTiempoValidado(byte hour,byte min,byte secs)=0;
    virtual void setFechaValidada(word year,byte month,byte day)=0;
};
  
#endif