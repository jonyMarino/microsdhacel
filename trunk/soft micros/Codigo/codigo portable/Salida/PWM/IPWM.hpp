#ifndef _IPWM_H
#define _IPWM_H


#include "ISalida.hpp"

class IPWM : public ISalida {
  public:
  virtual unsigned char setPeriodo(int period) = 0;

  virtual int getPeriodo() = 0;

};
#endif
