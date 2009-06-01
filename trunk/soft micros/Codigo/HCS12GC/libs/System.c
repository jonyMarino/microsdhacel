
#include "System.h"


#ifdef BAJOCONSUMO

#include "BTBajoConsumoSafe.h"

struct BTBajoConsumo baseTiempo;

void System_init(void){
  newAlloced(&baseTiempo,&BTBajoConsumo,2008,1,1,0,0,0,TRUE);
}

#elif defined(DS1307)

struct BaseTiempoDS1307 baseTiempo;
//struct RelojInternoPersistenciaDS1307 baseTiempo;

void System_init(void){
  newAlloced(&baseTiempo,&BaseTiempoDS1307);
 //newAlloced(&baseTiempo,&RelojInternoPersistenciaDS1307,2008,1,1,0,0,0,TRUE);
}

#else
#include "BTFechaPersistente.h"

#pragma CONST_SEG PARAMETERS_PAGE
volatile const struct BTFPConf bTConf={
  1,10,2008
};

#pragma CONST_SEG DEFAULT


struct BTFechaPersistente baseTiempo;

void System_init(void){
  newAlloced(&baseTiempo,&BTFechaPersistente,&bTConf);
}
#endif

void Sys_getDate(DATEREC * date){
  getFecha(&baseTiempo , date);
}

void Sys_getTime(TIMEREC * time){
  getTiempo(&baseTiempo , time);
}