#ifndef _PLATAFORMA_EMBEDDED_HPP
#define _PLATAFORMA_EMBEDDED_HPP

#include "ThreadAttachable.hpp"

class PlataformaEmbedded{
  public:
    PlataformaEmbedded(){threads=&thread;}
    virtual void mainLoop(void);
    friend void main (void);
    static ThreadAttachable * threads;
  private:
    ThreadAttachable thread;
    //static ThreadAttachable * threads;
    friend void pthread_create(void * _self,void * attr,void*(*pf)(void*),void* args);
};


#endif