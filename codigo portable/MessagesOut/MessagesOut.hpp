#ifndef _MESSAGES_OUT_HPP
#define _MESSAGES_OUT_HPP


#include <stdtypes.h>
#include "OOC/util/lib_cpp/DobleList.hpp"
#include "OOC/util/lib_cpp/NodoDoble.hpp"

class MessagesOut{
  public:
    typedef NodoDoble * Message;
    Message addMessage(const char * str);
    uchar deleteMessage(Message msj);
    char * getMessage(uint _msj_num);  
  private:
    DobleList lst;

};

#endif