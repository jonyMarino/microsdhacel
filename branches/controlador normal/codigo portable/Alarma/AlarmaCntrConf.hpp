#ifndef _ALARMACNTRCONF_H
#define _ALARMACNTRCONF_H


#include "AlarmaConf.hpp"
#include "ConfLazoCntrAlCntr.hpp"

class AlarmaCntrConf : public AlarmaConf {
  private:
    ConfLazoCntrAlCntr lazoCntrAlConf;

};
#endif
