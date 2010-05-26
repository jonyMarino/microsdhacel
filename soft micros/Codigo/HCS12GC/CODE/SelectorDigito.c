#include "SelectorDigito.h"
#include "bits2ULN.h"
#include "bits5ULN.h"


void SelectorDigito_putVal(byte val){
  bits2ULN_PutVal(val);
  bits5ULN_PutVal(val);
}

void SelectorDigitoInf_putVal(byte val){
  bits2ULN_PutVal(0);
  bits5ULN_PutVal(val);
}

void SelectorDigitoSup_putVal(byte val){
  bits2ULN_PutVal(val);
  bits5ULN_PutVal(0);
}