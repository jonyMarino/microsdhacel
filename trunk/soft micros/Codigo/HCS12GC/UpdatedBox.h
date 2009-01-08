#ifndef _UPDATED_BOX_H
#define _UPDATED_BOX_H 

#include "ReadOnlyBox.h"
#include "Timer.h"

#pragma DATA_SEG UpdatedBox_DATA                                            
#pragma CODE_SEG UpdatedBox_CODE 
#pragma CONST_SEG DEFAULT

struct UpdatedBox {
    struct ReadOnlyBox _base;
    struct Timer timer;
};


struct BlockConstrUpdatedBox{
  struct BlockConstrReadOnlyBox base;
  uint time;    
};


extern  const struct BoxClass UpdatedBox;

#pragma DATA_SEG DEFAULT                                            
#pragma CODE_SEG DEFAULT 
#pragma CONST_SEG DEFAULT

#endif


