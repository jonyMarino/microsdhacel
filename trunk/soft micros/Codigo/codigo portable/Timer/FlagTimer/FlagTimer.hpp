#ifndef _FLAG_TIMER_HPP
#define _FLAG_TIMER_HPP

#include "stdtypes.h"
#include "Timer/Timer.hpp"


typedef void(*pfunction)(void);
/*  Definicion del Timer*/

class FlagTimer:public Timer{
  public:
    FlagTimer(ulong time);
    void reset();
    inline bool getFlag()const{return flag;};
  protected:
    virtual void onTime();
  private:
    bool flag;
};

#endif 