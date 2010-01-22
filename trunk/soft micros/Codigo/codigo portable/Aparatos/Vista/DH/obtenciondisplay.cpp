#include "obtenciondisplay.hpp"
#include "FrenteDH.hpp"

OutputStream& getDisplay(uchar numDisplay){
  return *FrenteDH::getInstancia()->getDisplay(numDisplay);
}