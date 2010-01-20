#ifndef _METHOD_TIMER_HPP
#define _METHOD_TIMER_HPP

#include "stdtypes.h"
#include "Timer/Timer.hpp"
#include "./OOC/lang/reflect/lib_cpp/Method.hpp"

#pragma DATA_SEG MethodTimer_DATA                                            
#pragma CODE_SEG MethodTimer_CODE 
#pragma CONST_SEG DEFAULT

class MethodTimer:public Timer{
  public:
    MethodTimer(ulong tiempo,const struct Method& metodo);
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