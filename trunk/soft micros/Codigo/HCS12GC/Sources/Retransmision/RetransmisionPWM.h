#ifndef _RETRANSMISION_PWM_H
#define _RETRANSMISION_PWM_H

#include "Retransmision.h"

#pragma DATA_SEG RetransmisionPWM_DATA                                            
#pragma CODE_SEG RetransmisionPWM_CODE 

struct RetransmisionPWM{
  struct Retransmision super;
};

extern const struct LazoClass RetransmisionPWM;

#pragma DATA_SEG DEFAULT                                            
#pragma CODE_SEG DEFAULT 

#endif