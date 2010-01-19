#include <stdio.h>
#include "Box.hpp"

void Box::printDescripcion(const char * str, OutputStream& os){
  if(numObjeto){
    char strTmp[30];
    sprintf(strTmp,"%s%d",str,numObjeto);
    os.write(strTmp);
  } else
      os.write(str);
}
