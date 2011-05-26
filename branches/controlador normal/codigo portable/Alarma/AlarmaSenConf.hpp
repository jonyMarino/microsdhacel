#ifndef _ALARMASENCONF_H
#define _ALARMASENCONF_H


#include "ConfLazoCntrlAlSen.hpp"
#include "AlarmaConf.hpp"

class AlarmaSenConf : public AlarmaConf {
  private:
    ConfLazoCntrlAlSen lazoCntrAlConf;

};
#endif
