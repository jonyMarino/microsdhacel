#include "BTFechaPersistente.h"
#include "System.h"

#pragma CONST_SEG PARAMETERS_PAGE
volatile const struct BTFPConf bTConf={
  1,10,2008
};

#pragma CONST_SEG DEFAULT


struct BTFechaPersistente baseTiempo;

void System_init(void){
  newAlloced(&baseTiempo,&BTFechaPersistente,&bTConf);
}

void Sys_getDate(DATEREC * date){
  getDate(&baseTiempo , date);
}

void Sys_getTime(TIMEREC * time){
  getTime(&baseTiempo , time);
}