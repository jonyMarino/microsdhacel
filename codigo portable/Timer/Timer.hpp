#ifndef _TIMER_HPP
#define _TIMER_HPP

#include <stdtypes.h>
#include "Timer/BaseTimers.hpp"

class Timer{
  public:
    Timer(ulong tiempo);
    /*
    ** ===================================================================
    **     Method      :  Timer_Destruct 
    **    Description : Metodo para destruir el Timer
    ** ===================================================================
    */
    ~Timer();
    /*
    ** ===================================================================
    **     Method      :  setBaseTimer 
    **    Description : setea la entrada de ticks del timer
    ** ===================================================================
    */
    void setBaseTimer(BaseTimers * base);
    /*
    ** ===================================================================
    **     Method      :  TimerComp 
    **    Description : Compara el valor del timer contra el ultimo valor de
    **    la cuenta
    ** ===================================================================
    */
    void comparar();
    /*
    ** ===================================================================
    **     Method     : isFinished 
    **    Description : Indica si ya termino la cuenta
    ** ===================================================================
    */
    uchar isFinished();
    /*
    ** ===================================================================
    **     Method      :  Timer_getCuenta 
    **    Description : Regresa la cuenta actual que se resetea al llegar al tiempo
    ** ===================================================================
    */
    ulong getCuenta();
    /*
    ** ===================================================================
    **     Method      :  Timer_Restart 
    **    Description : Reinicia la cuenta del tiempo
    ** ===================================================================
    */
    void restart();
    /*
    ** ===================================================================
    **     Method      :  Timer_setTime 
    **    Description : Setea un tiempo nuevo y reinicia la cuenta del tiempo
    ** ===================================================================
    */
    void setTime(ulong tiempo);
    /*
    ** ===================================================================
    **     Method      :  Timer_getTime 
    **    Description : Obtiene el tiempo a alcanzar
    ** ===================================================================
    */
    ulong getTime();
    /*
    ** ===================================================================
    **     Method     :  stop 
    **    Description : Detiene la cuenta del timer
    ** ===================================================================
    */
    void stop();
    
    static void  setBaseTimerDefault(BaseTimers& b);
  protected:
    virtual void onTime();  
  private:
    ulong next_cuenta;
    ulong tiempo;
    uchar of;
    BaseTimers * baseTimer;
    static BaseTimers *baseTimerDefault;
};

#endif