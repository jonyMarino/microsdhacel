#include "System.hpp"


#ifdef DS1307
#include "BaseTiempoDS1307.h"
BaseTiempoDS1307 System::baseTiempo();
#else
#include "BaseTiempo.hpp"
BaseTiempo System::baseTiempo(2010,1,1,0,0,0);
#endif 

void System::init(){
}

void System::getDate(FechaTiempo::DATEREC& date){
  baseTiempo.getFecha(&date);
}

void System::getTime(FechaTiempo::TIMEREC& time){
  baseTiempo.getTiempo(&time);
}
