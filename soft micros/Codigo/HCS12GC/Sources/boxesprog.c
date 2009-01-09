#include "Mydefines.h"
#include "cnfbox.h"
#ifdef _BUTTON_CHANEL_HMI 
#include "boxes_HMI2.h"
#endif
#include "boxes.h"
#include "Programador.h"
#include "PE_Types.h"
#include "boxesprog.h"
#include "friend_parametros.h"
#include "parametros.h"

#pragma CONST_SEG DEFAULT 
#pragma STRING_SEG DEFAULT

#ifdef _PROGRAMADOR
  const Numerico1 Program;
  const NumericoJumpCond Segmento;
  const TextualJumpCond Tipo_temp;
  const TextualJumpCond Tipo_Tolerancia_Gral;
  const Numerico1 Tolerancia_Gral;
  const Textual1 Cond_Emergencia_Gral;
  const TextualJumpCond Tipo_Segmento;
  const Textual1 Box_PrgOnEnd;
  #ifdef prog_viejo
    const NumericoJumpCond Temp_f;
    const NumericoJumpCond Temp_i;
    const Numerico1 Tiempo;
  #else
    const Numerico1 Temp_i;
    const NumericoJumpCond Temp_f;
    const NumericoJumpCond Tiempo;
  #endif
  
  const NumericoJumpCond Velocidad;
  const Numerico1 JMP_Programa;
  const Numerico1 Ciclos_Programa;
  const Textual1 Cond_Emergencia_JMP;
  const TextualJumpCond Tipo_Tolerancia;
  const NumericoJumpCond Tolerancia;
  #ifdef prog_viejo								 
    const TextualJumpCond Cond_Emergencia;
  #else    
    const Textual1 Cond_Emergencia;
  #endif

  

#endif

//int next_tiempo,next_tol,next_prog;
//int Lim_Segmento1;	 /* Para el prog nuevo, pantalla de ingreso de programa*/
			
/************************************/
/************************************/
/* PARAMETROS de Programador (nuevo)*/
/************************************/
/************************************/

/*Programa*/
/**********/
#ifndef prog_viejo
#ifdef _PROGRAMADOR		

const Numerico1 Program =	         //nombre variable
      {
      ProcNumerico1,			 /* funcion que procesa al box*/
      "PrG ",							   //nombre display
			&ParProgConf,						 /* direccion en la E2Prom */
			1,                     // numero de elementos
			0,									   //pos punto dec
			(PunteroF)&Segmento			 //enter rap
			};
			
PunteroF proximo_Seg(byte tecla){ 
  if(tecla=='r'){
    
    if(get_ValParametro(0,((TDato*)&ParSegConf))==1)    
      return (PunteroF)&Tipo_temp;
    return (PunteroF)&Tipo_Segmento;
  } else return NULL;
}; 

const NumericoJumpCond Segmento =	             //nombre variable
      {
        ProcNumJumpCond,						     /* funcion que procesa al box*/
        "SEG ",							         //nombre display
			  &ParSegConf,									     /* direccion en la E2Prom */
			  1,                  //Cantidad de elementos
			  0,									    		 //pos punto dec
			  proximo_Seg				 //enter rap
			};
			

/*****************************/
/*****************************/
/* Parte General (Segmento 0)*/
/*****************************/
/*****************************/

/*Tipo de Temperatura inicial*/
/*****************************/

static const char * TIPO_TEMP[2]={
      "SEt ",			 
      "AMb "									
};
PunteroF Tipo_temp_siguientes(byte tecla){ 
  if(tecla=='r'){
      if(get_Tti(0)==TEMP_INI_AMBIENTE)
        return (PunteroF)&Temp_i;
      return (PunteroF)&Tipo_Tolerancia_Gral;
  }else return NULL;
}
     
const TextualJumpCond Tipo_temp=
      {
      ProcTextJumpCond,						      /* funcion que procesa al box*/
			"tt  ",									      //nombre display
			&ParTtiConf,							/* direccion en la E2Prom - el EEProm Start, if FALSE no guarda valor*/
			1,
			TIPO_TEMP,
			Tipo_temp_siguientes
			};


/*Temperatura inicial*/
/*********************/

const Numerico1 Temp_i =	             //nombre variable
      {
      ProcNumerico1,						     /* funcion que procesa al box*/
			"t  i",							         //nombre display
      &ParTiConf,									     /* direccion en la E2Prom */
      1,
      #if CANTIDAD_CANALES == 1
        DECIMALES_CANAL1,											 //pos punto dec
      #else
			  0,									    		 //pos punto dec
      #endif
			(PunteroF)&Tipo_Tolerancia_Gral					 //enter rap,enter mant
			};	

/*Tipo de Tolerancia General*/
/****************************/

PunteroF TTol_Siguientes(byte tecla){ 
    if(tecla=='r'){
      byte ttol=(byte)get_TTolGral(0);     
      if(ttol==TTOL_OFF || ttol==TTOL_NO )
        return (PunteroF)&Cond_Emergencia_Gral;
      return (PunteroF)&Tolerancia_Gral;
    }
    return NULL;
}; 

const char * TEXTOS_TOLERANCIAS_GRAL[5]={
      "OFF ",
      "Lo  ",
      "Hi  ",
      "bAnd",
      "no  "									
};

const TextualJumpCond Tipo_Tolerancia_Gral=
      {
      ProcTextJumpCond,						/* funcion que procesa al box*/		
			"ttoL",								//nombre display
			&ParTTolGral,											/* direccion en la E2Prom - el EEProm Start*/
			1,
			TEXTOS_TOLERANCIAS_GRAL,             // Array donde estan los textos
			TTol_Siguientes					 //Proximos estados
			};			

/*Tolerancia General*/
/********************/

const Numerico1 Tolerancia_Gral =	             //nombre variable
      {
      ProcNumerico1,						     /* funcion que procesa al box*/      
			"toL ",							       //nombre display
      &ParTolGral,					 /* direccion en la E2Prom */
      1,
      #if CANTIDAD_CANALES == 1
        DECIMALES_CANAL1,					//pos punto dec
      #else														
			  0,									    	//pos punto dec
      #endif
			(PunteroF)&Cond_Emergencia_Gral				 //enter rap,enter mant
			};
			

/*Condicion de emergencia General*/
/*********************************/

const char * const TEXTOS_EMERGENCIA_GRAL[5]={		// Hay 3 condiciones de emergencia que utilizan 
			"cc  ",																// estos strings incluyendo este
			"rS  ",
			"rP  ",
			"EndP",
			"no  "
};


const Textual1 Cond_Emergencia_Gral=
      {
      CondEGralHandler,				/* funcion que procesa al box*/			
			"Emer",									//nombre display
			&ParCondEGral,											/* direccion en la E2Prom - el EEProm Start, if FALSE no guarda valor*/
			1,
			TEXTOS_EMERGENCIA_GRAL,             // Array donde estan los textos
			(PunteroF)&Tipo_Segmento					 //Proximos estados
			};			


/*****************************/
/*****************************/
/* Parte de segmentos        */
/*****************************/
/*****************************/



/*Tipo de Segmento   */
/*********************/

static const char * strs_tSegmentos[6]={
      "End ",
      "rMPt",
      "rMPV",									
			"MSt ",
			"SteP",
			"JMP "
			
};

PunteroF TSeg_Siguientes(byte tecla){ 
    if(tecla=='r'){
    T_Segmento tseg=(T_Segmento)get_TSeg(0);
      if(tseg== SEG_RMP_T || tseg== SEG_RMP_V ||tseg== SEG_STEP)
        return (PunteroF)&Temp_f;
      else if(tseg== SEG_MESETA)
        return (PunteroF)&Tiempo;
      else if(tseg== SEG_JMP)
        return (PunteroF)&JMP_Programa; 
      else if(tseg ==SEG_END)
        return (PunteroF)&Box_PrgOnEnd;
   
    }return NULL;   
}; 
const TextualJumpCond Tipo_Segmento=
      {
      ProcTextJumpCond,						/* funcion que procesa al box*/			
			"tiPo SEG    ",									//nombre display
			&ParTSeg,											/* direccion en la E2Prom - el EEProm Start, if FALSE no guarda valor*/
			1,
			strs_tSegmentos,             // Array donde estan los textos
			TSeg_Siguientes					 //Proximos estados
};

/*Condicion OnEnd     */
/*************************/
const char * strs_OnEnd[2]={
  "CnEc",
  "dESC"
};

const Textual1 Box_PrgOnEnd=
      {ProcTextual1,						/* funcion que procesa al box*/
      "OnEnd    ",								//nombre display
			&ParOnEnd,									/* direccion en la E2Prom - el EEProm Start, if FALSE no guarda valor*/
			1,
			strs_OnEnd,                 // Array donde estan los textos
			(PunteroF)&Program
			};

/*Temperatura final  */
/*********************/
PunteroF TempF_Siguientes(byte tecla){ 
    if(tecla=='r'){
    T_Segmento tseg=(T_Segmento)get_TSeg(0);
      if(tseg== SEG_RMP_T || tseg== SEG_STEP)
        return (PunteroF)&Tiempo;
  //  else if(tseg== SEG_RMP_V)
        return (PunteroF)&Velocidad;
    }return NULL;   
}; 
    
const NumericoJumpCond Temp_f =	             //nombre variable
      {
      ProcNumJumpCond,						/* funcion que procesa al box*/      
			"t  F",							  //nombre display
      &ParSegSP,					/* direccion en la E2Prom */
      1,
      #if CANTIDAD_CANALES == 1
        DECIMALES_CANAL1,			//pos punto dec
      #else
			  0,									  //pos punto dec
      #endif
			TempF_Siguientes					    //enter rap,enter mant
			};


/*Tiempo*/
/********/
PunteroF tiempo_siguiente(byte tecla){  
  
  if(tecla=='r'){   
    if (get_TTolGral(0)==TTOL_NO)
      return (PunteroF)&Tipo_Tolerancia;
    else if (get_CondEGral(0)==COND_NO)
      return (PunteroF)&Cond_Emergencia;
    
    return 	 (PunteroF)&Segmento;
  }
  return NULL;
}

const NumericoJumpCond Tiempo =	             //nombre variable
      {
      ProcNumJumpCond,						     /* funcion que procesa al box*/      
			"tEMP",							         //nombre display
			&ParTiempoSeg,									     /* direccion en la E2Prom */
			1,
			0,									    		 //pos punto dec
			tiempo_siguiente					 //enter rap
			};


/*Velocidad*/
/***********/
const NumericoJumpCond Velocidad =	     //nombre variable
      {ProcNumJumpCond,						 /* funcion que procesa al box*/      
			"VEL ",							       //nombre display
      &ParTiempoSeg,						 /* direccion en la E2Prom */
      1,
      PROG_PRESICION_VEL,  			 //pos punto dec
			tiempo_siguiente					 //enter rap,enter mant
			};

/*Salto a  sub-Programa*/
/***********************/
const Numerico1 JMP_Programa =	   //nombre variable
      {ProcNumerico1,						     /* funcion que procesa al box*/
			"PrGn",							         //nombre display
			&ParJumpPrg,							 /* direccion en la E2Prom */
			1,
			0,									    		 //pos punto dec
			(PunteroF)&Ciclos_Programa		 //enter rap
			};
			
/*Ciclos de Programa*/
/********************/
const Numerico1 Ciclos_Programa =	             //nombre variable
      {ProcNumerico1,						     /* funcion que procesa al box*/
			"CicL",							         //nombre display
			&ParTiempoSeg,									     /* direccion en la E2Prom */
			1,
			0,									    		 //pos punto dec 
			(PunteroF)&Segmento					 //enter rap,enter mant
			};

/*Tipo de Tolerancia */
/*********************/

PunteroF TTol_siguientes(byte tecla){
  if(tecla=='r'){
    if(get_TTol(0)==TTOL_OFF){
      if (get_CondEGral(0)==COND_NO)
        return (PunteroF)&Cond_Emergencia;
      return (PunteroF)&Segmento; 
    }
    return (PunteroF)&Tolerancia;
  }
  return NULL;
}

const TextualJumpCond Tipo_Tolerancia=
      {
      ProcTextJumpCond,				 /* funcion que procesa al box*/
			"ttoL",									 //nombre display
			&ParTTol,					 /* direccion en la E2Prom - el EEProm Start, if FALSE no guarda valor*/
			1,
			TEXTOS_TOLERANCIAS_GRAL, // Array donde estan los textos
			TTol_siguientes			   //Proximos estados
			};			


/*Tolerancia*/
/************/
PunteroF Tolerancia_Siguientes(byte tecla){
  if(tecla=='r'){   
    if (get_CondEGral(0)==COND_NO)
      return (PunteroF)&Cond_Emergencia;
    
    return 	 (PunteroF)&Segmento;
  }
  return NULL;
  
}

const NumericoJumpCond Tolerancia ={//nombre variable      
      ProcNumJumpCond,						     /* funcion que procesa al box*/      
			"toL ",							         //nombre display
      &ParTol,								/* direccion en la E2Prom */
      1,
      #if CANTIDAD_CANALES == 1
        DECIMALES_CANAL1,											 //pos punto dec
      #else
			  0,									    		 //pos punto dec
      #endif 
			Tolerancia_Siguientes					 //enter rap,enter mant
};
			

/*Condicion de Emergencia*/
/*************************/
const Textual1 Cond_Emergencia=
      {
      ProcTextual1,						/* funcion que procesa al box*/			
			"EMEr",									//nombre display
			&ParCondE,											/* direccion en la E2Prom - el EEProm Start, if FALSE no guarda valor*/
			1,
			TEXTOS_EMERGENCIA_GRAL,             // Array donde estan los textos
			(PunteroF)&Segmento					 //Proximos estados
			};

#endif

/************************************/
/************************************/
/* PARAMETROS de Programador (viejo)*/
/************************************/
/************************************/
#else

static byte programa_mostrado,segmento_mostrado;

/*Temperatura inicial*/
/*********************/
PunteroF TempI_siguiente(byte tecla){ 
  if(tecla=='r'){
    byte prog_interno=get_ProgConf(0)-1;
    
    Prg_set_TipoTempIni(TEMP_INI_SET,prog_interno);
    Prg_setTipoTolGral(TTOL_NO,prog_interno);
    Prg_set_CondEmerGral(COND_NO,prog_interno); 
    Prg_set_OnEnd(END_KEEPCONECTED,prog_interno);  
    return (PunteroF)&Cond_Emergencia;
  }return NULL;
}														
const NumericoJumpCond Temp_i =	            //nombre variable
      {ProcNumJmpCondProg,					/* funcion que procesa al box*/
      "1S 1",							          //nombre display
      &ParTemp_ini,								/* direccion en la E2Prom */
      1,
      #if CANTIDAD_CANALES == 1
        DECIMALES_CANAL1,							//pos punto dec
      #else
			  0,									    		 //pos punto dec
      #endif			
			TempI_siguiente				 //enter rap,enter mant
			};
			
/*Temperatura */
/**************/
PunteroF TempF_siguiente(byte tecla){ 
  if(tecla=='r'){
    set_SegConf(get_SegConf(0)+1,0);
    return (PunteroF)&Cond_Emergencia;
  }return NULL;
}
const NumericoJumpCond Temp_f =	         //nombre variable
      {ProcNumJmpCondProg,				 /* funcion que procesa al box*/
  		"1S 1",							         //nombre display
      &ParSegSP,								 /* direccion en la E2Prom */
      1,
      #if CANTIDAD_CANALES == 1
        DECIMALES_CANAL1,						 //pos punto dec
      #else
			  0,									    		 //pos punto dec
      #endif
			TempF_siguiente
};								

/*Condicion de Emergencia*/
/*************************/
const char * const strs_EMERGENCIA[5]={		// Hay 3 condiciones de emergencia que utilizan 
			"cc  ",																// estos strings incluyendo este
			"rS  ",
			"rP  ",
			"EndP",
			"End "
};


PunteroF CondE_siguiente(byte tecla){ 
  if(tecla=='r'){
    byte prog_conf=get_ProgConf(0);
    byte seg_conf=get_SegConf(0);
     

    if(get_CondE(0)==MAX_VALUE_COND+1 || seg_conf==MAX_SEGMENTOS){
      set_ProgConf(prog_conf+1,0);
      programa_mostrado++;
      set_SegConf(1,0);  // Primer Segmento
      segmento_mostrado=1;
      return (PunteroF)&Temp_i;
    }else{
      Prg_set_TipoSeg(SEG_RMP_T,prog_conf-1,seg_conf-1);   
      Prg_setTipoTol(TTOL_HI,prog_conf-1,seg_conf-1); 
      return (PunteroF)&Tiempo;
    }
  }return NULL;
};

const TextualJumpCond Cond_Emergencia=
      {ProcTxtJmpCondProg,						/* funcion que procesa al box*/
			"1E 1",									//nombre display
			&ParCondE,											/* direccion en la E2Prom - el EEProm Start, if FALSE no guarda valor*/
			1,
			strs_EMERGENCIA,             // Array donde estan los textos
			CondE_siguiente
			};
			
/*Tiempo*/
/********/
const Numerico1 Tiempo =	             //nombre variable
      {NumProgHandler,						     /* funcion que procesa al box*/
			"1t 1",							         //nombre display
      &ParTiempoSeg,									     /* direccion en la E2Prom */
			1,
			0,									    		 //pos punto dec
			(PunteroF)&Tolerancia					 //enter rap,enter mant
};

/*Tolerancia*/
/************/
PunteroF Tol_siguiente(byte tecla){
  if(tecla=='r'){
    segmento_mostrado++;
    return  (PunteroF)&Temp_f;					 //enter rap,enter mant
  }return NULL;
}

const NumericoJumpCond Tolerancia =	             //nombre variable
      {
      ProcNumJmpCondProg,						     /* funcion que procesa al box*/
			"1d 1",							         //nombre display
      &ParTol,									     /* direccion en la E2Prom */
      1,
      #if CANTIDAD_CANALES == 1
        DECIMALES_CANAL1,											 //pos punto dec
      #else
			  0,									    		 //pos punto dec
      #endif
			Tol_siguiente
			};


void Reset_ProgSegMostrados(void){
  programa_mostrado=1; 
  segmento_mostrado=1; 
}

byte ConfPrg_getSegMostrado(void){
  return segmento_mostrado;
}

byte ConfPrg_getProgMostrado(void){
  return programa_mostrado;
}


#endif