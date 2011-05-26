#ifndef _THREAD_ATACHABLE_HPP
#define _THREAD_ATACHABLE_HPP

#include "MethodContainer.hpp"
#include "OOC/lang/reflect/lib_cpp/Method.hpp"

class ThreadAttachable:public MethodContainer{
  public:
    ThreadAttachable(){}
    void adjuntar(struct Method * method);
    void executeThreads();
    
    class ThreadAttacher{
      public:
        ThreadAttacher(ThreadAttachable*);
        void adjuntar(struct Method * method);
      private:
        ThreadAttachable * threadAdjuntable;
    };
    
    ThreadAttacher * getAdjuntador();
    
  private:
    friend class ThreadAttacher; 
  
};


#endif