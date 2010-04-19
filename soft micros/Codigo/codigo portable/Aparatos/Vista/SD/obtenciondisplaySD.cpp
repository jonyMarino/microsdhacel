#include "obtenciondisplay.hpp"
#include "FrenteSD.hpp"

OutputStream& getDisplay(uchar numDisplay){
  return *FrenteSD::getInstancia()->getDisplay(numDisplay);
}