#ifndef _IPWM_H
#define _IPWM_H


#include "ISalida.hpp"

class IPWM : public ISalida {
  public:
  virtual unsigned char setPeriodo(int period);

  virtual int getPeriodo();

};
#endif
