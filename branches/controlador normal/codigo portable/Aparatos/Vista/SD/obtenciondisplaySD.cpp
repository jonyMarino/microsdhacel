#include "obtenciondisplay.hpp"
#include "FrenteSD.hpp"

OutputStream& getDisplay(uchar numDisplay){
  if(numDisplay<=1)
    return *FrenteSD::getInstancia()->getDisplaySD(numDisplay);
  else
    return *FrenteSD::getInstancia()->getDisplay(numDisplay/3);
}