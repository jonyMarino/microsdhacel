#ifndef _BASE_TIEMPO_HPP
#define _BASE_TIEMPO_HPP


#include "FechaIncrementable.hpp"
#include "Timer/RlxMTimer/RlxMTimer.hpp"


class BaseTiempo:public FechaIncrementable{
  public:
    BaseTiempo(word anio,byte mes,byte dia,byte hora,byte min,byte segs);
  private:
    int segundosAcumulados;
    RlxMTimer timer;
    bool configurado;
    static void incUnSegundo(void * );
};

#endif
