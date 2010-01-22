#include "Math.hpp"

VUINT16 Math::div_dec[5]={
  1,10,100,1000,10000  
};

VUINT16 Math::pow10(byte exponente){
  /*exponente esta entre 0 y 4*/
  return div_dec[exponente];  
}



