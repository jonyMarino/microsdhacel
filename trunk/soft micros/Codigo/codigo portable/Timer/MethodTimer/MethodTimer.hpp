#ifndef _METHOD_TIMER_HPP
#define _METHOD_TIMER_HPP

#include "stdtypes.h"
#include "Timer.hpp"
#include "Method.hpp"

#pragma DATA_SEG MethodTimer_DATA                                            
#pragma CODE_SEG MethodTimer_CODE 
#pragma CONST_SEG DEFAULT

class MethodTimer:public Timer{
  public:
    MethodTimer(ulong tiempo,struct Method& metodo);
    void setMetodo(struct Method& metodo);
    struct Method&  getMetodo();
  protected:
    void onTime();
  private:
    struct Method metodo;
};


#pragma DATA_SEG DEFAULT                                            
#pragma CODE_SEG DEFAULT 

#endif