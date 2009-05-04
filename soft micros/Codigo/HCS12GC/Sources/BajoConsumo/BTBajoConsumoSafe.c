#include "BTBajoConsumoSafe.h"
#include "BTBajoConsumo_protected.h"
#include "IFshMem.h"
#include "PromBkp.h"
#include "IFsh10.h"

void BTBajoConsumoSafe_defConstructor(void * _self,va_list * args);

void BTBajoConsumoSafe_onRTI(void * _self);

const struct BTBajoConsumoClass BTBajoConsumoSafe = {
    BASE_TIEMPO_CLASS_INITIALIZATION(BTBajoConsumoClass,
                             BTBajoConsumoSafe,  
                             BTBajoConsumo,
                             BTBajoConsumoSafe_defConstructor,
                             Object_dtor,
                             Object_differ,
                             Object_puto,
                             BTBajoConsumo_GetTime,
                             BaseTiempo_setTime,
                             BTBajoConsumo_GetDate,
                             TmDt1_setFechaValidada,
                             BaseTiempo_getConfigurado,
                             BaseTiempo_incUnSegundo),
                             BTBajoConsumoSafe_onRTI  
};

extern const struct ManejadorMemoria * pFlash;
   
struct ManejadorMemBTSafe{
  word * actualAddr;
};

struct ManejadorMemBTSafeData{
  byte data[6];
};

bool ManejadorMemBTSafeData_isNul(void * _self){
  struct ManejadorMemBTSafeData * self = _self;
  struct ManejadorMemBTSafeData nulData;
  memset(&nulData,0xFF,sizeof(struct ManejadorMemBTSafeData));
  return !memcmp(self,&nulData,sizeof(struct ManejadorMemBTSafeData));  
}

bool ManejadorMemBTSafeData_nextPageJmp(void * _self){
  struct ManejadorMemBTSafe * self = _self;  
  if((((word)(self->actualAddr+(sizeof(struct ManejadorMemBTSafeData)+1)/2))&(PAGE_SIZE-1)) < (((word)self->actualAddr)&(PAGE_SIZE-1))) {
    /*if( ((word)self->actualAddr) < BT_BAJO_CONSUMO_SAFE_PAGES_START + PAGE_SIZE)
      self->actualAddr = (void*)(BT_BAJO_CONSUMO_SAFE_PAGES_START + PAGE_SIZE);
    else
      self->actualAddr = (void*)BT_BAJO_CONSUMO_SAFE_PAGES_START;
    */
    return TRUE;
  }
  return FALSE;
}

void ManejadorMemBTSafe_searchLastWritedAddr(void * _self,word addr){
  struct ManejadorMemBTSafe * self = _self;
  self->actualAddr = (void*)addr;
  while( (!ManejadorMemBTSafeData_isNul(self->actualAddr)) && !ManejadorMemBTSafeData_nextPageJmp(_self)){
    self->actualAddr += (sizeof(struct ManejadorMemBTSafeData)+1)/2; 
  }
}

void ManejadorMemBTSafe_constructor(void * _self){
  struct ManejadorMemBTSafe * self = _self;
  self->actualAddr = (void*)BT_BAJO_CONSUMO_SAFE_PAGES_START;
  if(ManejadorMemBTSafeData_isNul( self->actualAddr )){   
    if(ManejadorMemBTSafeData_isNul(self->actualAddr + PAGE_SIZE/2)) // las paginas no estan escritas
      return; 
    else
      ManejadorMemBTSafe_searchLastWritedAddr(_self,BT_BAJO_CONSUMO_SAFE_PAGES_START + PAGE_SIZE);  
  }else if( ManejadorMemBTSafeData_isNul(self->actualAddr+ PAGE_SIZE/2)){
      ManejadorMemBTSafe_searchLastWritedAddr(_self,BT_BAJO_CONSUMO_SAFE_PAGES_START);      
  }else{
    if( !ManejadorMemBTSafeData_isNul(self->actualAddr + (sizeof(struct ManejadorMemBTSafeData)+1)/2)){
      #warning quiza convenga manejar la flash en bajo consumo
      //PromBkp_borrarPagina(pFlash,self->actualAddr); //no se llego a borrar la pag 
      EraseSectorInternal(self->actualAddr); 
      self->actualAddr += PAGE_SIZE/2 + (sizeof(struct ManejadorMemBTSafeData)+1)/2;  
    }else{
      
      //PromBkp_borrarPagina(pFlash,self->actualAddr + PAGE_SIZE/2); //no se llego a borrar la pag  
      EraseSectorInternal(self->actualAddr + PAGE_SIZE/2 );
      self->actualAddr += (sizeof(struct ManejadorMemBTSafeData)+1)/2;
    } 
  }
}

bool ManejadorMemBTSafe_getLastData(void * _self, struct ManejadorMemBTSafeData * data){
  struct ManejadorMemBTSafe * self = _self;
  
  if( (word)self->actualAddr == BT_BAJO_CONSUMO_SAFE_PAGES_START){
    memcpy(data, (void*)(BT_BAJO_CONSUMO_SAFE_PAGES_START + PAGE_SIZE) , sizeof(struct ManejadorMemBTSafeData) );
  } else
    memcpy(data, self->actualAddr - (sizeof(struct ManejadorMemBTSafeData)+1)/2 , sizeof(struct ManejadorMemBTSafeData) );
  
  return !ManejadorMemBTSafeData_isNul(data);
  
}

void ManejadorMemBTSafe_setData(void * _self, const struct ManejadorMemBTSafeData * data){
  struct ManejadorMemBTSafe * self = _self;
  word deletePage = 0;
  
  if(ManejadorMemBTSafeData_nextPageJmp(_self)){
    if( ((word)self->actualAddr) < BT_BAJO_CONSUMO_SAFE_PAGES_START + PAGE_SIZE){
      deletePage = BT_BAJO_CONSUMO_SAFE_PAGES_START;
      self->actualAddr = (void*)(BT_BAJO_CONSUMO_SAFE_PAGES_START + PAGE_SIZE);
    
    }else{
      deletePage = BT_BAJO_CONSUMO_SAFE_PAGES_START + PAGE_SIZE;
      self->actualAddr = (void*)BT_BAJO_CONSUMO_SAFE_PAGES_START;
    }
  }
  WriteArray(self->actualAddr,0,sizeof(struct ManejadorMemBTSafeData),data);
  self->actualAddr += (sizeof(struct ManejadorMemBTSafeData)+1)/2;
  if(deletePage)
    EraseSectorInternal((void *)deletePage);
}


struct ManejadorMemBTSafe manejadorMem;

void BTBajoConsumoSafe_defConstructor(void * _self,va_list * args){
  struct BTBajoConsumoSafe * self = _self;
  struct ManejadorMemBTSafeData data;
  super_ctor(&BTBajoConsumoSafe,_self,args);
  
  ManejadorMemBTSafe_constructor(&manejadorMem);
  if(ManejadorMemBTSafe_getLastData(&manejadorMem,&data)){
    setFecha(_self,2000+data.data[0],data.data[1],data.data[2]);
    BaseTiempo_setTime(_self,data.data[3],data.data[4],data.data[5]);
  }
}

void BTBajoConsumoSafe_onRTI(void * _self){
  struct BTBajoConsumoSafe * self = _self;
  
  if(!(BTBajoConsumo_interrupcionesRTI(_self)%460)){ //aprox 1 min.
    DATEREC date;
    TIMEREC time;
    struct ManejadorMemBTSafeData data;
    BTBajoConsumo_GetDate(_self,&date);  
    BTBajoConsumo_GetTime(_self,&time);
    
    data.data[0]=date.Year-2000;
    data.data[1]=date.Month;
    data.data[2]=date.Day;
    data.data[3]=time.Hour;
    data.data[4]=time.Min;
    data.data[5]=time.Sec;
 
    
    ManejadorMemBTSafe_setData(&manejadorMem,&data);
  }
  BTBajoConsumo_onRTI(_self); 
}
