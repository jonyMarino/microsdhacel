#include "AdquisidorSimple.h"
#include "System.h"
#include "MessagesOut.h"
#include "Adquisidor.h"
#include "str_lib.h"

void AdquisidorSimple_defCtor(void * self);

const struct PlataformaEmbeddedClass AdquisidorSimple={
  &Class,
  "",
  &Termometro,
  sizeof(struct AdquisidorSimple),
  AdquisidorSimple_defCtor,
  Object_dtor,
  Object_differ,
  Object_puto,
  Termometro_mainLoop
};

#pragma CONST_SEG PARAMETERS_PAGE
volatile const struct AdqConf adquisidor_config={
  ADQ_DEFAULT_CONF
};
#pragma CONST_SEG DEFAULT


void enter_2num(int num , char * str){

  str[0]= num/10+'0';
  str[1]= num%10+'0'; 
}



void  AdquisidorSimple_actualizarTextos(void * _self){
  struct AdquisidorSimple * self=_self;
  
  if(Adq_getActualState(&self->adquisidor)==TRUE){
    self->mensaje[7]='S';
    self->mensaje[8]='i';
    self->mensaje[9]=' '; 
  }if(Adq_getActualState(&self->adquisidor)== 0){     //ESTADO ADQ_NO
    self->mensaje[7]='n';
    self->mensaje[8]='o';
    self->mensaje[9]=' ';  
  }if(Adq_getActualState(&self->adquisidor)==3){      //ESTADO ADQ_FULL
    self->mensaje[7]='F';
    self->mensaje[8]='U';
    self->mensaje[9]='L';
    self->mensaje[10]=' ';
    
     
  }
  
  if(Adq_isTimeSet(&self->adquisidor)){
    DATEREC date;
    TIMEREC tiempoRec;
    byte dia,mes;
    int anio,tiempo;
    
    Sys_getDate(&date);
    Sys_getTime(&tiempoRec);
    dia =date.Day;
    mes= date.Month;
    anio= date.Year;
    tiempo = tiempoRec.Hour*100+tiempoRec.Min;   
    
    
    
    enter_2num(dia,&self->mensaje[17]);
    self->mensaje[19]= '-';
    enter_2num(mes,&self->mensaje[20]);
    self->mensaje[22]= '-';
    enter_2num(anio%100,&self->mensaje[23]); 
 
    enter_2num(tiempo/100,&self->mensaje[31]);
    self->mensaje[33]='.';
    enter_2num(tiempo%100,&self->mensaje[34]);
    self->mensaje[36]=' '; 
    self->mensaje[37]=' ';  
  }else{
    memcpy(&self->mensaje[17],"no ing.",7);    
    memcpy(&self->mensaje[31],"no ing.",7);
  }
 
}


void AdquisidorSimple_constructor(void * _self,void * conf,struct ManejadorDePROM * flash){
 struct AdquisidorSimple * self= _self;
 
 Termometro_constructor(self,flash);
 newAlloced(&self->adquisidor,&Adquisidor,&adquisidor_config,(self->termometro).sensor);	

 newAlloced(&self->mensajes,MessageOut);
   								    //012345678901234567890123456789012345678						    
 strcpy(&self->mensaje,"EStAdo no. FEchA no ing.  horA no ing. ");
 self->textosMensajes= MessageOut_AddMessage(&self->mensajes,self->mensaje);
 AdquisidorSimple_actualizarTextos(self);
 newAlloced(&(self->timer),&RlxMTimer,(ulong)2000,AdquisidorSimple_actualizarTextos,_self);

}


void AdquisidorSimple_defCtor(void * self,va_list * args){
  AdquisidorSimple_constructor(self,va_arg(*args,void*),va_arg(*args,void*));  
}


char * AdquisidorSimple_getText(void * _self){
  struct AdquisidorSimple * self= _self;
   return self->mensaje;
}
