#ifndef _DISPLAY_SD_HPP
#define _DISPLAY_SD_HPP

#include <stdtypes.h>
#include "PE/include/PE_Types.h"
#include "OOC/ooc/lib_cpp/OutputStream.hpp"
#include "Vista/Display/Display.hpp"

class DisplaySD:public Display{
  public:
    DisplaySD(byte*_puerto);
    void write(const char* str);
    void write(int i);
    
  private:
    
    friend class FrenteCustomSD;   
};

#endif
