#ifndef _RELAXED_M_TIMER_HPP
#define _RELAXED_M_TIMER_HPP

#include "Timer/MethodTimer/MethodTimer.hpp"
#include "OOC/util/lib_cpp/LinkedList.hpp"

#pragma DATA_SEG RlxMTimer_DATA                                            
#pragma CODE_SEG RlxMTimer_CODE 
#pragma CONST_SEG DEFAULT

struct RlxMTimer:public MethodTimer{
  public:
    RlxMTimer(ulong tiempo,struct Method& metodo);
    RlxMTimer(ulong tiempo,Method::pMethod metodo,void*obj);
    ~RlxMTimer();
  protected:
    void onTime();  
  private:
    bool execute;
    static LinkedList * rlxMTCont; 
    static void* handler(void * self); 
};



#pragma DATA_SEG DEFAULT                                            
#pragma CODE_SEG DEFAULT 

#endif