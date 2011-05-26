#ifndef _BASE_TIMERS_HPP
#define _BASE_TIMERS_HPP

#include "OOC/util/lib_cpp/LinkedList.hpp"


class BaseTimers: public LinkedList{
  public:
    unsigned long getCuenta();
    virtual bool moveOut(void * timer);
    virtual void lockInc()=0;
    virtual void unlockInc()=0;
  protected:
    void actualizarTimers(void);
    void incrementar(unsigned int ms);    
  private:
    unsigned long cuenta;
    int index; 
};


#endif
