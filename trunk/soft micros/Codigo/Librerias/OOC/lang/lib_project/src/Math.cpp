#include "Math.hpp"

const unsigned int Math::div_dec[5]={
  1,10,100,1000,10000  
};

unsigned int Math::pow10(byte exponente){
  /*exponente esta entre 0 y 4*/
  return div_dec[exponente];  
}



