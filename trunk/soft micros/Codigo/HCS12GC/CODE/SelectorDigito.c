#include "SelectorDigito.h"
#include "bits2ULN.h"
#include "bits5ULN.h"


void SelectorDigito_putVal(byte val){
  bits5ULN_PutVal(val);
  bits2ULN_PutVal(val);  
}

