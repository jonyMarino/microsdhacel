#include "Mydefines.h"
#include "display.h"
#include "cnfbox.h"
#include "IFsh10.h"
#include "Timer.h"
#include "Sensores.h"
#include "Math.h"
#ifdef _COLADA_CALIENTE
  #include "ControlCC.h"
#else
  #include "Control.h"
#endif
#include "Programador.h"

#if SEG_END !=0
  #error se va a tener que inicializar los programas en nada[0]=SEG_END
#endif

#define INTERNAL_NO_PROGRAMA -1 

#pragma CONST_SEG PARAMETERS_PAGE
volatile const int iPrograma[CANTIDAD_SAL_CONTROL]={
INTERNAL_NO_PROGRAMA
};
#pragma CONST_SEG DEFAULT

//#define  segmento  Programa[programa_ingresado].Segmento[segmento_ingresado]
//#define  general   Programa[programa_ingresado].Gral 


//extern int ValFinal[]; //Variable Proceso

bool pendiente_negativa; //Determina la pendiente para el tipo rampa velocidad
void Prog_ActualizarSetPoints(void);
void ActualizarSetPointPrograma(byte canal);
/////Guardar ante corte//////
byte ProgramaActual[CANTIDAD_SAL_CONTROL];				//Programa actualmente corriendo, es distinto de PRom[R_Programa], ya que el tipo de segmento JUMP lo puede modificar
byte SegmentoActual[CANTIDAD_SAL_CONTROL];				//Segmento corriendo del programa actual,
dword SegundosSegmento[CANTIDAD_SAL_CONTROL];			//Segundos transcurridos en el segmento actual
t_prog_state Prog_State[CANTIDAD_SAL_CONTROL];    //Estado del Programa(Stop o Running)

struct{																						//Esta estructura contiene la info para recuperar el programa luego de un JUMP (Se verifica ante un END)
byte Programa;																		//(Programa al cual volver)+1, si es cero no se vuelve a ningun programa. Se verifica en End
byte Segmento;																		//Segmento al cual volver->Es un Jump
int Ciclos;																			//Ciclos de repeticion del programa. Se ejecuta en End
}ProgramReturn[CANTIDAD_SAL_CONTROL][MAX_PROGRAMAS];
////////////////////////
int SetPointPrograma[CANTIDAD_SAL_CONTROL];				//Set Point del Programa actual
int SegmentoMostrado[CANTIDAD_SAL_CONTROL];
static int TemperaturaAnterior[CANTIDAD_SAL_CONTROL];		//Temperatura que habia al comenzar el segmento

#ifdef _PROGRAMADOR

TSegmentos SegVal[CANTIDAD_SAL_CONTROL];					//Valores temporales para correr el segmento actual

const TProgramas  Programa[MAX_PROGRAMAS] @(FLASH_PROGRAMADOR_START)={		 //Programas guardados en FLASH
#if defined( PROG_SIMPLE_RSTP)
END_DISCONECT,  // ON_END
rP,  //condicion_emer
OFF,  //tipo_tolerancia
0,  //temperatura_inicial
0,  //tolerancia
AMb,  //tipo_temperatura_inicial

//Tipo          ce  tt    ºC     tol    tiempo	
  SEG_RMP_V,    cc,  Lo,  10,     0,      5,
  SEG_MESETA,   cc,  Lo,  10,     0,      1,

  SEG_END,      cc,  Lo,  10,     0,      5,
#else
END_KEEPCONECTED,  // ON_END
COND_NO,  //condicion_emer
TTOL_NO,  //tipo_tolerancia
0,  //temperatura_inicial
0,  //tolerancia
0,  //tipo_temperatura_inicial

//Tipo          ce  tt  ºC   tol tiempo  
  SEG_RMP_T,   COND_CONTINUE,  TTOL_LOW,  50,  0,  1,
  SEG_RMP_T,   COND_CONTINUE,  TTOL_LOW,  50,  0,  1,
  SEG_RMP_T,   COND_CONTINUE,  TTOL_LOW,  50,  0,  1,
  SEG_RMP_T,   COND_CONTINUE,  TTOL_LOW,	 10,  0,  1,
  SEG_END,COND_END_PROG+1,  0, 100,  	2,  1,
  SEG_END ,   0,  0,    0,    0,  0,
  SEG_END ,   0,  0,    0,    0,  0,
  SEG_END ,   0,  0,    0,    0,  0,
  SEG_END ,   0,  0,    0,    0,  0,
  SEG_END ,   0,  0,    0,    0,  0,
  SEG_END ,   0,  0,    0,    0,  0,
  SEG_END ,   0,  0,    0,    0,  0,
  SEG_END ,   0,  0,    0,    0,  0,
  SEG_END ,   0,  0,    0,    0,  0,
  SEG_END ,   0,  0,    0,    0,  0,
  SEG_END ,   0,  0,    0,    0,  0,
  SEG_END ,   0,  0,    0,    0,  0,
  SEG_END ,   0,  0,    0,    0,  0,
  SEG_END ,   0,  0,    0,    0,  0,
  SEG_END ,   0,  0,    0,    0,  0,
  SEG_END ,   0,  0,    0,    0,  0,
  SEG_END ,   0,  0,    0,    0,  0,
  SEG_END ,   0,  0,    0,    0,  0,
  SEG_END ,   0,  0,    0,    0,  0,
  SEG_END,    0,  0,    0,    0,  0,
  SEG_END,    0,  0,    0,    0,  0,
  SEG_END,    0,  0,    0,    0,  0,
  0,    0,  0,    0,    0,    //relleno de página
END_KEEPCONECTED,  // ON_END
COND_NO,  //condicion_emer
TTOL_NO,  //tipo_tolerancia
0,  //temperatura_inicial
0,  //tolerancia
0,  //tipo_temperatura_inicial

//Tipo            ce  tt  ºC     tol tiempo
  SEG_MESETA ,    COND_CONTINUE,  TTOL_OFF,    0,    0,  1,
  SEG_RMP_V,      COND_CONTINUE,  TTOL_OFF,    0,    0,100,
  SEG_MESETA,     COND_CONTINUE,  TTOL_OFF,    0,    0,  1,
  SEG_RMP_T,      COND_CONTINUE,  TTOL_OFF,   10,    0,  1		 
#endif
};


///////////////////Se fija si el Segmento es END//////////
#pragma INLINE
static bool is_End(byte program, byte segment){
 return Programa[program].Segmento[segment].tipo_segmento==SEG_END;
}

void Prog_Init(void){
byte i;  
  for(i=0;i<CANTIDAD_SAL_CONTROL;i++){
    ProgramaActual[i]=255; 
 		if (iPrograma[i]!=INTERNAL_NO_PROGRAMA){
 		  ReestablecerPrograma(i);
			//Pongo el Limite del Segmento para ese canal
//			Lim_Segmento2[i]=get_Lim_Seg(PRom[R_Programa+i]);
//			#ifdef prog_viejo
//      Lim_Segmento2[chan]++;
//      #endif
    }
  }    
  TimerRun(1000,NULL,CONTINUO_SET,Prog_ActualizarSetPoints); 

}

///////////////////Se fija si se termino de ejecutar el programa//////////
bool isProgFinish(byte chan){
byte p,s;
  p= ProgramaActual[chan];
  s= SegmentoActual[chan];
  if(p<255) 
  if(Programa[p].Segmento[s].tipo_segmento==SEG_END)
    return TRUE;
  return FALSE;
}

////  Actualiza los Set Point de todos los canales /////
void Prog_ActualizarSetPoints(void){
byte i;
  for(i=0;i<CANTIDAD_SAL_CONTROL;i++){     
    if(Prog_State[i]==PROG_RUNNING && SegVal[i].tipo_segmento!=SEG_END)  
      ActualizarSetPointPrograma(i);
  }
}

//////////////////Devuelve el Limite del segmento para el canal
byte get_Lim_Seg(byte programa){

      byte lim_seg=0; 		  

 		  while( !is_End(programa,lim_seg) )
 		    lim_seg++;  
      
      return lim_seg;
}

//////////////////Devuelve el segmento actual corriendo en el canal channel/////////
static TSegmentos * get_ActualSegment(byte channel){
  return &Programa[ProgramaActual[channel]].Segmento[SegmentoActual[channel]];
}

byte get_iActualSegment(byte channel){
  return SegmentoActual[channel];
}

byte set_ActualSegment(byte val,byte channel){
  runPrograma(channel,ProgramaActual[channel],val,0);
  return ERR_OK;
}

byte get_iActualProgram(byte channel){
  return ProgramaActual[channel];
}
/////////////Se fija si el canal esta dentro de los valores de la tolerancia de *pSegmento//////////////////////////////////////////////////
static bool is_inside_band(const TSegmentos * pSegmento,byte canal){
int tol = pSegmento->tolerancia;
int ValProc=SENSOR_getProcVal(canal); 
 if(tol){
    
    
    switch(pSegmento->tipo_tolerancia){
      case TTOL_LOW: if((ValProc+tol)<=SetPointPrograma[canal])
                    return FALSE;
      				 break;
      case TTOL_BAND:if((ValProc+tol)<=SetPointPrograma[canal])
                    return FALSE;			 
      case TTOL_HI: if((ValProc-tol)>=SetPointPrograma[canal])
                    return FALSE;
    } 
  }
  return TRUE;
}
/////////////////////Calcula el valor del Set Point a partir de los segundos del segmento/////////////////
void Prog_CalculateSetPoint(byte canal){
bool CambioSeg=FALSE;
long int TmpSet;
char mul;
  
  switch(SegVal[canal].tipo_segmento){
    case SEG_RMP_T: TmpSet = (SegVal[canal].temperatura_f- TemperaturaAnterior[canal])*SegundosSegmento[canal];
               TmpSet /= ((long)SegVal[canal].tiempo*60);
               SetPointPrograma[canal] = (int)TmpSet+TemperaturaAnterior[canal];
    					 if(SegundosSegmento[canal] >= (long)SegVal[canal].tiempo*60)
                CambioSeg=TRUE;
   						break;
    case SEG_MESETA:		
    
    case SEG_STEP:
              SetPointPrograma[canal] = TemperaturaAnterior[canal];
              if(SegundosSegmento[canal] >= (long)SegVal[canal].tiempo*60)
                CambioSeg=TRUE;
   						break;
    
    case SEG_RMP_V:

             TmpSet =	 SegVal[canal].velocidad * SegundosSegmento[canal] /60 ;
             mul=PROG_PRESICION_VEL;
             #ifdef _APARATO_VIEJO
              mul-=SENSOR_Decimales_Mostrar(get_Sensor(canal));	 //SACAR: NO HACE FALTA SI SEPARAMOS SP CONTROL DE SP MOSTRADO
             #else
              mul-=get_Decimales(canal);
             #endif
             if(mul>0)
              TmpSet /=pow10(mul);
             else
              TmpSet *=pow10(-mul);
             
             SetPointPrograma[canal] = (int)TmpSet;
             if (pendiente_negativa)
                  SetPointPrograma[canal]*=-1;
             SetPointPrograma[canal] += TemperaturaAnterior[canal];     
             if ((pendiente_negativa &&
             SetPointPrograma[canal]<=SegVal[canal].temperatura_f) ||
             (!pendiente_negativa && 
             SetPointPrograma[canal]>=SegVal[canal].temperatura_f)
             ){
                    SetPointPrograma[canal]=SegVal[canal].temperatura_f;  
                    CambioSeg=TRUE;
                  }

    					break;
   
    case SEG_END:
    return;		
  }

  if(CambioSeg){
  CambioSeg=FALSE;
  TemperaturaAnterior[canal] = (int)SetPointPrograma[canal];
  runPrograma(canal,ProgramaActual[canal],++SegmentoActual[canal],0);    
  }  
}
/////////////////////Actualiza el Set Point Actual (Se llama a cada segundo)//////////////////////////////

void ActualizarSetPointPrograma(byte canal){

  if(! is_inside_band(&SegVal[canal],canal))
    return;
  
  ++SegundosSegmento[canal];

  Prog_CalculateSetPoint(canal);
}

////////////////// Carga los valores iniciales de un programa/////////////
//Aclaracion: nunca entra con tipo_segmento= JMP
void runPrograma(byte canal,
                 char programa, 
                 byte Segmento,
                 long segs
                 ){
TSegmentos * p,* segval;
byte ProgramaAux;
byte i=MAX_PROGRAMAS;
extern word TiempoProgramaCh[CANTIDAD_SAL_CONTROL];


  CNTR_Conect(canal);

  if (programa==-1){
    Prog_State[canal]=PROG_NO;
    SegundosSegmento[canal]=segs;
    ProgramaActual[canal]=programa;
    SegmentoActual[canal]=Segmento;
    SegmentoMostrado[canal]=Segmento+1;
    TiempoProgramaCh[canal]=0;  
    return;
  }



  if (!Segmento)  
      ProgramReturn[canal][programa].Programa=0;

  segval=&SegVal[canal];
      
    do{
    p=& Programa[programa].Segmento[Segmento];  
       
       switch(p->tipo_segmento){
         case SEG_STEP:
            SetPointPrograma[canal] = p->temperatura_f;
            break;
         case SEG_RMP_V:
         case SEG_MESETA:
         case SEG_RMP_T: 
            if (!Segmento){
              if (Programa[programa].Gral.tipo_temperatura_inicial == TEMP_INI_AMBIENTE)
                SetPointPrograma[canal]=TemperaturaAnterior[canal] = SENSOR_getProcVal(canal);
              else //SEt
                SetPointPrograma[canal]=TemperaturaAnterior[canal] = Programa[programa].Gral.temperatura_inicial;
            } 
            else 
                #if defined(jony_05_07) 
                TemperaturaAnterior[canal] = (p-1)->temperatura_f;
                #else
                #error
                #endif

          break;
         
         case SEG_JMP: 
          i--;
          ProgramReturn[canal][p->temperatura_f].Programa = programa+1;
          ProgramReturn[canal][p->temperatura_f].Segmento = Segmento;
          ProgramReturn[canal][p->temperatura_f].Ciclos = (byte)p->tiempo;
         
          programa=(byte)p->temperatura_f;
          Segmento=0;        
            if (!i)return;//ERROR ****AGREGAR MAS COSAS*****
  			  break;
         
         case SEG_END:
            if(!ProgramReturn[canal][programa].Programa){
              segval->tipo_segmento = SEG_END;
              Prog_State[canal]=PROG_ENDED;
              SegmentoMostrado[canal]=Segmento+OFFSET_SEG1;
              SetPointPrograma[canal]= (p-1)->temperatura_f;
              if(Programa[canal].Gral.OnEnd== END_DISCONECT)
                CNTR_Disconect(canal);    
              #if(is_cout==TRUE)
                cout("End ");  
              #endif
              return;
            }
            if(ProgramReturn[canal][programa].Ciclos>1){
              ProgramReturn[canal][programa].Ciclos--;
              Segmento=0;
            }else{
              Segmento=ProgramReturn[canal][programa].Segmento+1; 
              ProgramaAux=programa;
              programa=ProgramReturn[canal][programa].Programa-1;
              ProgramReturn[canal][ProgramaAux].Programa=0;     
            }
         break;
       }
    }while(p->tipo_segmento==SEG_JMP || p->tipo_segmento==SEG_END);
     
  if(p->tipo_segmento==SEG_RMP_V)
    pendiente_negativa = p->temperatura_f < TemperaturaAnterior[canal];  
           
  segval->tipo_segmento = p->tipo_segmento;
  segval->temperatura_f = p->temperatura_f;
  segval->tiempo  			= p->tiempo;

  if(Programa[programa].Gral.tipo_tolerancia!=TTOL_NO)
  {
    segval->tipo_tolerancia=Programa[programa].Gral.tipo_tolerancia;
    segval->tolerancia= Programa[programa].Gral.tolerancia;
  }else{
    segval->tipo_tolerancia = p->tipo_tolerancia; 
    segval->tolerancia = p->tolerancia;
  }
   

  set_ProgState(PROG_RUNNING,canal);
  SegundosSegmento[canal]=segs;
  ProgramaActual[canal]=programa;
  SegmentoActual[canal]=Segmento;
  SegmentoMostrado[canal]=Segmento+OFFSET_SEG1;
  #ifdef jony_15_08
  Prog_CalculateSetPoint(canal);
  #endif
}

void Prog_Stop(void){
  set_ProgState(PROG_STOPED,0);
}

void Prog_Continue(void){
  set_ProgState(PROG_RUNNING,0);
}
void Prog_reset(void){ 
  set_ProgState(PROG_RESETED,0);
}


t_prog_state get_ProgState(byte canal){
  return Prog_State[canal];  
}

void set_ProgState(t_prog_state state,byte canal){
  Prog_State[canal]=state;  
  switch(state){
    case PROG_STOPED:
      set_MainText("StoP");
      CNTR_Disconect(0);
      break;
    case PROG_RESETED:
      runPrograma(0,iPrograma[0], 0,0);
      CNTR_Disconect(0);
      set_MainText("StoP");
      break;
    case PROG_CONTINUE:
     if(Prog_State[canal]==PROG_RESETED)
      runPrograma(canal,iPrograma[0], 0,0);

    default:
      set_MainText("");
  }
}


//////////Funcion al caerse la Energia.IMPLEMENTADO COMO MACRO
/*
void GuardarPrograma(void){
(void)WriteArray(FLASH_APAGADO_START,0, (7+3*MAX_PROGRAMAS)*CANTIDAD_SAL_CONTROL, (word*)ProgramaActual);
}
*/
///////////////////////////Funcion al caerse la Energia/////
//Aclaracion: nunca entra con tipo_segmento= JMP
void ReestablecerPrograma(byte canal){
byte CondicionTmp;
word i;

for(i=0;i<(5+2*MAX_PROGRAMAS)*CANTIDAD_SAL_CONTROL;i++)
  *(((word*)ProgramaActual)+i) = *(((word*)FLASH_APAGADO_START)+i);

if(TemperaturaAnterior[canal]==0xFFFF){
 /*HUBO UN ERROR!!!!!!!!!!!(No se llegó a grabar todo en la Flash antes de que se apague el aparato)*/

    runPrograma(canal,(byte)iPrograma[canal],0,0);	    
}
   
#if !defined( PROG_SIMPLE_RSTP) || !defined(jony_24_08)	
  if( is_inside_band(get_ActualSegment(canal),canal))
      CondicionTmp=COND_CONTINUE;  		
  else
#endif
  {
    #ifdef jony_08_07 
      #ifndef prog_viejo
    CondicionTmp=(byte)Programa[ProgramaActual[canal]].Gral.condicion_emer;
    if (CondicionTmp==COND_NO)
    #endif
      CondicionTmp = (get_ActualSegment(canal))->condicion_emer;
  }
#endif

  {
    t_prog_state state=get_ProgState(canal);

    switch(CondicionTmp){
      case COND_RESET_SEG: runPrograma(canal,ProgramaActual[canal],(byte) SegmentoActual[canal],0);
      				 break;
      case COND_RESET_PROG: runPrograma(canal,ProgramaActual[canal], 0,0);
      				 break;
      case COND_END_PROG:
        runPrograma(canal,ProgramaActual[canal],get_Lim_Seg(iPrograma[canal]),0);
        break;
      case COND_CONTINUE: {
        dword segs=SegundosSegmento[canal];
        
        runPrograma(canal,ProgramaActual[canal],(byte) SegmentoActual[canal],segs);
       // SegundosSegmento[canal]= segs; 
       // Prog_CalculateSetPoint(canal);
        
      }
    }
  set_ProgState(state,canal);
  }

}

////////  FUNCIONES GET SET
/*  Programa  */
int get_Programa(byte num_cntrl){
  return iPrograma[num_cntrl]+1;
}

byte set_Programa(int val,byte num_cntrl){
  byte err= EscribirByte((word)&iPrograma[num_cntrl],val-1);
  if(!err)
    runPrograma(num_cntrl,val-1,0,0);
  return err;
}

int get_LimSup_Programa(void){
  return MAX_PROGRAMAS;
}



  #ifdef _PROGRAMADOR
  ////////////  GETs & SETs Program Running////////////
  /*  Tiempo  */
  int get_TiempoMinutos(byte num_cntrl){
    return SegundosSegmento[num_cntrl]/60;
  }

  byte set_TiempoMinutos(int val,byte num_cntrl){
    #ifdef _PROGRAMADOR
      runPrograma(num_cntrl,iPrograma[num_cntrl],SegmentoActual[num_cntrl], (long)val*60);

    #endif
    return ERR_OK;
  }
  
  ////////////  GETs & SETs Program Page///////////////
  /*  Programas */
    //Condicion OnEnd/////////////////
    byte Prg_set_OnEnd(T_OnEnd on_end,byte program){
      return EscribirByte((word)&Programa[program].Gral.OnEnd,on_end);
    }
    T_OnEnd Prg_get_OnEnd(byte program){
      return Programa[program].Gral.OnEnd;
    }
    //Temperatura inicial////////////
    byte Prg_set_TempIni(int val,byte program){
      return EscribirWord((word)&Programa[program].Gral.temperatura_inicial,val);
    }
    int Prg_get_TempIni(byte program){
      return Programa[program].Gral.temperatura_inicial;
    }
    //  Tipo Temperatura inicial  ////////////
    byte Prg_set_TipoTempIni(T_Temperatura_Ini val,byte program){
      return EscribirByte((word)&Programa[program].Gral.tipo_temperatura_inicial,val);
    }
    T_Temperatura_Ini Prg_get_TipoTempIni(byte program){
      return IFsh10_getByte((word)&Programa[program].Gral.tipo_temperatura_inicial);
    }
    //  Condicion de Emergencia General ///////
    T_CondEmer Prg_get_CondEmerGral(byte program){
      return Programa[program].Gral.condicion_emer;
    }
    byte Prg_set_CondEmerGral(T_CondEmer val,byte program){
      return EscribirByte((word)&Programa[program].Gral.condicion_emer,val);
    }
    /// Tolerancia General////////////////////
    int Prg_getToleranciaGral(byte program){
      return Programa[program].Gral.tolerancia;
    }
    byte Prg_setToleranciaGral(int val,byte program){
      return EscribirWord((word)&Programa[program].Gral.tolerancia,val);
    }
    //  Tipo Tolerancia General //////////////
    T_Tolerancia Prg_getTipoTolGral(byte program){
      return IFsh10_getByte((word)&Programa[program].Gral.tipo_tolerancia);
    }
     byte Prg_setTipoTolGral(T_Tolerancia val,byte program){
      return EscribirByte((word)&Programa[program].Gral.tipo_tolerancia,val);
    }
  /*  Segmentos */
    ///////Tipo de Segmento///////////
    T_Segmento Prg_get_TipoSeg(byte program,byte segment){
      return IFsh10_getByte((word)&Programa[program].Segmento[segment].tipo_segmento); 
    }
    byte Prg_set_TipoSeg(T_Segmento val,byte program,byte segment){ 
      byte err= EscribirByte((word)&Programa[program].Segmento[segment].tipo_segmento,val);    
      if(!err)
        if(val==SEG_MESETA)
          Prg_set_SetPoint(Prg_get_SetPoint(program,segment-1),program,segment);  
      return err;
    }
    ///////Velocidad//////////////////
    byte  Prg_set_Velocity(word val,byte program,byte segment){
      return EscribirWord((word)&Programa[program].Segmento[segment].tiempo,val);  
    }
    word Prg_get_Velocity(byte program,byte segment){
      return Programa[program].Segmento[segment].tiempo; 
    }

    ///////Set Point//////////////////
    byte Prg_set_SetPoint(int val,byte program,byte segment){
      return EscribirWord((word)&Programa[program].Segmento[segment].temperatura_f,val);
    }

    int Prg_get_SetPoint(byte program,byte segment){
      return Programa[program].Segmento[segment].temperatura_f;  
    }

    ///////Tiempo //////////////////
    byte Prg_set_Time(word val,byte program,byte segment){
      return EscribirWord((word)&Programa[program].Segmento[segment].tiempo,val);  
    }

    word Prg_get_Time(byte program,byte segment){
      return Programa[program].Segmento[segment].tiempo; 
    }
    
    /// Condicion de Emergencia ////
    T_CondEmer Prg_getCondicionEmer(byte program,byte segment){
      return IFsh10_getByte((word)&Programa[program].Segmento[segment].condicion_emer);  
    }
    
    byte Prg_setCondicionEmer(T_CondEmer val,byte program,byte segment){
      return EscribirByte((word)&Programa[program].Segmento[segment].condicion_emer,val);   
    }
    /// Tipo Tolerancia ////
    T_Tolerancia Prg_getTipoTol(byte program,byte segment){
      return IFsh10_getByte((word)&Programa[program].Segmento[segment].tipo_tolerancia);
    }
    byte Prg_setTipoTol(T_Tolerancia val,byte program,byte segment){
      return EscribirByte((word)&Programa[program].Segmento[segment].condicion_emer,val);   
    }
    
    /// Tolerancia  ////
    int Prg_getTolerancia(byte program,byte segment){
      return Programa[program].Segmento[segment].tolerancia;      
    }
    byte Prg_setTolerancia(int val,byte program,byte segment){
      return EscribirWord((word)&Programa[program].Segmento[segment].tolerancia,val);  
    }
    
    ///////Jump programa //////////
    byte Prg_set_JumpProg(word val,byte program,byte segment){
      if(val==program)
        return ERR_VALUE;
      return EscribirWord((word)&Programa[program].Segmento[segment].temperatura_f,val);  
    }

    word Prg_get_JumpProg(byte program,byte segment){
      return Programa[program].Segmento[segment].temperatura_f; 
    }
    
    int Prg_get_LimSup_JumpProg(void){
      return MAX_PROGRAMAS-1;  
    }						
    /////// Ciclos = Tiempo
    
  #endif

#endif
