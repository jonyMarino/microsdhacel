#ifndef _SYSTEM_HPP
#define _SYSTEM_HPP


#ifdef DS1307
#include "BaseTiempoDS1307.h"
#define TIPO_BASE_TIEMPO BaseTiempoDS1307;
#else
#include "BaseTiempo.hpp"
#define TIPO_BASE_TIEMPO BaseTiempo
#endif 

class System{
  public:
    static void init();
    static void getDate(FechaTiempo::DATEREC& date);
    static void getTime(FechaTiempo::TIMEREC& time);
  private:  
    static TIPO_BASE_TIEMPO baseTiempo;
};


#endif