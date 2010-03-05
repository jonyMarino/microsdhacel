#include "Mydefines.h"
#include "cnfbox.h"
#include "boxes.h"
#include "PE_Types.h"
#include "Sensores.h"
#include "display.h"
#include "In1.h"
#include "IFsh10.h"
#include "FuncionVF.h"
#include "vfboxes.h"
#include "In1.h"
#include "In2.h"
extern byte BackupArray[MEM_PAGINA];
extern bool flagAlarma; 
extern word screen_cont;
bool flag_tecla_up=0;
bool flag_tecla_down=0;
extern dword rampa_mestaTime;
extern dword timeCartel;
extern byte Tecla;
word minutos = 1;
char flagCartel=1; 
char flagComCartel=FALSE; 
char unaVez=0;
char tecla_d=1;
extern byte Nletras[CANTIDAD_DISPLAYS];

char resetMst=0;
char resetRamp=0;
char cantDig=0;
char _msj[MAX_DIGITOS];
extern byte b; //variable de scrolling 
char unaVuelta=0;

//#pragma CONST_SEG DEFAULT 
//#pragma STRING_SEG DEFAULT

extern const Numerico Vrmp1;
extern const Numerico Tmpm1;
extern const Numerico Tiem1;
extern const Numerico Vrmp2;
extern const Numerico Tmpm2;
extern const Numerico Tiem2;  
extern const Numerico Vrmp3;
extern const Numerico Tmpm3;
extern const Numerico Tiem3;
extern const Numerico Vrmp4;
extern const Numerico Tmpm4;
extern const Numerico Tiem4;   
extern const Numerico Vrmp5;
extern const Numerico Tmpm5;
extern const Numerico Tiem5;
extern const Numerico Vrmp6;
extern const Numerico Tmpm6;
extern const Numerico Tiem6;  
extern const Numerico Vrmp7;
extern const Numerico Tmpm7;
extern const Numerico Tiem7;
extern const Numerico Vrmp8;
extern const Numerico Tmpm8;
extern const Numerico Tiem8;
extern const Numerico Vrmp9;
extern const Numerico Tmpm9;
extern const Numerico Tiem9;
extern const Numerico Vrmp10;
extern const Numerico Tmpm10;
extern const Numerico Tiem10;  
  
  
   /* Set vrmp1*/
/*****************/
const Numerico Vrmp1={
      NumHandler,
      &Parametros[R_Vrmp1],
      #ifdef MSJ_CORTO
      "Ur 1",
      #else
			"     UEL rAMPA1 <C/Min   ",
			#endif
			1,
			NULL,
			(PunteroF*)&Tmpm1.DirProc,
			};


 /* Set tmeseta1*/
/*****************/
const Numerico Tmpm1={
      NumHandler,
      &Parametros[R_Tmpm1],
      #ifdef MSJ_CORTO
      "<Cm1",
      #elif defined(VF_BKR)
      "     tEMPErAtUrA <C      ",
      #else
			"     tEMPEr MESEtA 1 <C  ",
			#endif
			
			DECIMALES_CANAL1,
			NULL,
			(PunteroF*)&Tiem1.DirProc,
			};


const PunteroF R_tiemeseta1[11]={

		  &Principal1.DirProc,
	  	&Principal1.DirProc,
	  	&Vrmp2.DirProc,	
		  &Vrmp2.DirProc,
		  &Vrmp2.DirProc,	
		  &Vrmp2.DirProc,
		  &Vrmp2.DirProc,	
		  &Vrmp2.DirProc,
		  &Vrmp2.DirProc,	
		  &Vrmp2.DirProc,
		  &Vrmp2.DirProc,
		  
};




 /* Set tiemeseta1*/
/*****************/
const Numerico Tiem1={
      NumHandler,
      &Parametros[R_Tiem1],
      #ifdef MSJ_CORTO
      "tim1",
      #elif defined(VF_BKR)
      "     tiEMPo Min          ",
      #else
			"     tiEMPo MESEtA 1 Min ",
			#endif
		
			0,
			&((int*)BackupArray)[R_ESP],//&PRom[R_ESP],
		  R_tiemeseta1,
		    NULL,
			};
			

   /* Set vrmp2*/
/*****************/
const Numerico Vrmp2={
      NumHandler,
      &Parametros[R_Vrmp2],
      #ifdef MSJ_CORTO
      "Ur 2",
      #else
			"     UEL rAMPA2 <C/Min   ",
			#endif
			1,
			NULL,
			(PunteroF*)&Tmpm2.DirProc,
			};


 /* Set tmeseta2*/
/*****************/
const Numerico Tmpm2={
      NumHandler,
      &Parametros[R_Tmpm2],
			#ifdef MSJ_CORTO
      "<Cm2",
      #else
			"     tEMPEr MESEtA 2 <C  ",
			#endif
			DECIMALES_CANAL1,
			NULL,
			(PunteroF*)&Tiem2.DirProc,
			};


const PunteroF R_tiemeseta2[11]={
     
      &Principal1.DirProc,
			&Principal1.DirProc,
	  	&Principal1.DirProc,	
		  &Vrmp3.DirProc,
		  &Vrmp3.DirProc,	
		  &Vrmp3.DirProc,
		  &Vrmp3.DirProc,	
		  &Vrmp3.DirProc,
		  &Vrmp3.DirProc,	
		  &Vrmp3.DirProc,
		  &Vrmp3.DirProc,
		  
};




 /* Set tiemeseta2*/
/*****************/
const Numerico Tiem2={
      NumHandler,
      &Parametros[R_Tiem2],
			#ifdef MSJ_CORTO
      "tim2",
      #else
			"     tiEMPo MESEtA 2 Min ",
			#endif
			0,
			&((int*)BackupArray)[R_ESP],//&PRom[R_ESP],
		  R_tiemeseta2,
		    NULL,
			};


   /* Set vrmp3*/
/*****************/
const Numerico Vrmp3={
      NumHandler,
      &Parametros[R_Vrmp3],
      #ifdef MSJ_CORTO
      "Ur 3",
      #else
			"     UEL rAMPA3 <C/Min   ",
			#endif
			1,
			NULL,
			(PunteroF*)&Tmpm3.DirProc,
			};


 /* Set tmeseta3*/
/*****************/
const Numerico Tmpm3={
      NumHandler,
      &Parametros[R_Tmpm3],
			#ifdef MSJ_CORTO
      "<Cm3",
      #else
			"     tEMPEr MESEtA 3 <C  ",
			#endif
			DECIMALES_CANAL1,
			NULL,
			(PunteroF*)&Tiem3.DirProc,
			};


const PunteroF R_tiemeseta3[11]={
      
      &Principal1.DirProc,
	  	&Principal1.DirProc,
	  	&Principal1.DirProc,	
		  &Principal1.DirProc,
		  &Vrmp4.DirProc,	
		  &Vrmp4.DirProc,
		  &Vrmp4.DirProc,	
		  &Vrmp4.DirProc,
		  &Vrmp4.DirProc,	
		  &Vrmp4.DirProc,
		  &Vrmp4.DirProc,
		  
};




 /* Set tiemeseta3*/
/*****************/
const Numerico Tiem3={
      NumHandler,
      &Parametros[R_Tiem3],
			#ifdef MSJ_CORTO
      "tim3",
      #else
			"     tiEMPo MESEtA 3 Min ",
			#endif
			0,
			&((int*)BackupArray)[R_ESP],//&PRom[R_ESP],
		  R_tiemeseta3,
		    NULL,
			};
			
   /* Set vrmp4*/
/*****************/
const Numerico Vrmp4={
      NumHandler,
      &Parametros[R_Vrmp4],
      #ifdef MSJ_CORTO
      "Ur 4",
      #else
			"     UEL rAMPA4 <C/Min   ",
			#endif
			1,
			NULL,
			(PunteroF*)&Tmpm4.DirProc,
			};


 /* Set tmeseta4*/
/*****************/
const Numerico Tmpm4={
      NumHandler,
      &Parametros[R_Tmpm4],
			#ifdef MSJ_CORTO
      "<Cm4",
      #else
			"     tEMPEr MESEtA 4 <C  ",
			#endif
			DECIMALES_CANAL1,
			NULL,
			(PunteroF*)&Tiem4.DirProc,
			};


const PunteroF R_tiemeseta4[11]={

		  &Principal1.DirProc,
			&Principal1.DirProc,
	  	&Principal1.DirProc,	
		  &Principal1.DirProc,
		  &Principal1.DirProc,	
		  &Vrmp5.DirProc,
		  &Vrmp5.DirProc,	
		  &Vrmp5.DirProc,
		  &Vrmp5.DirProc,	
		  &Vrmp5.DirProc,
		  &Vrmp5.DirProc,
		 
};




 /* Set tiemeseta4*/
/*****************/
const Numerico Tiem4={
      NumHandler,
      &Parametros[R_Tiem4],
			#ifdef MSJ_CORTO
      "tim4",
      #else
			"     tiEMPo MESEtA 4 Min ",
			#endif
			0,
			&((int*)BackupArray)[R_ESP],//&PRom[R_ESP],
		  R_tiemeseta4,
		    NULL,
			};
			
   /* Set vrmp5*/
/*****************/
const Numerico Vrmp5={
      NumHandler,
      &Parametros[R_Vrmp5],
      #ifdef MSJ_CORTO
      "Ur 5",
      #else
			"     UEL rAMPA5 <C/Min   ",
			#endif
			1,
			NULL,
			(PunteroF*)&Tmpm5.DirProc,
			};


 /* Set tmeseta5*/
/*****************/
const Numerico Tmpm5={
      NumHandler,
      &Parametros[R_Tmpm5],
			#ifdef MSJ_CORTO
      "<Cm5",
      #else
			"     tEMPEr MESEtA 5 <C  ",
			#endif
			DECIMALES_CANAL1,
			NULL,
			(PunteroF*)&Tiem5.DirProc,
			};


const PunteroF R_tiemeseta5[11]={

			&Principal1.DirProc,
	  	&Principal1.DirProc,	
		  &Principal1.DirProc,
		  &Principal1.DirProc,	
		  &Principal1.DirProc,
		  &Principal1.DirProc,	
		  &Vrmp6.DirProc,
		  &Vrmp6.DirProc,	
		  &Vrmp6.DirProc,
		  &Vrmp6.DirProc,
		  &Vrmp6.DirProc,
		  
};




 /* Set tiemeseta5*/
/*****************/
const Numerico Tiem5={
      NumHandler,
      &Parametros[R_Tiem5],
			#ifdef MSJ_CORTO
      "tim5",
      #else
			"     tiEMPo MESEtA 5 Min ",
			#endif
			0,
			&((int*)BackupArray)[R_ESP],//&PRom[R_ESP],
		  R_tiemeseta5,
		    NULL,
			};
			
   /* Set vrmp6*/
/*****************/
const Numerico Vrmp6={
      NumHandler,
      &Parametros[R_Vrmp6],
      #ifdef MSJ_CORTO
      "Ur 6",
      #else
			"     UEL rAMPA6 <C/Min   ",
			#endif
			1,
			NULL,
			(PunteroF*)&Tmpm6.DirProc,
			};


 /* Set tmeseta1*/
/*****************/
const Numerico Tmpm6={
      NumHandler,
      &Parametros[R_Tmpm6],
			#ifdef MSJ_CORTO
      "<Cm6",
      #else
			"     tEMPEr MESEtA 6 <C  ",
			#endif
			DECIMALES_CANAL1,
			NULL,
			(PunteroF*)&Tiem6.DirProc,
			};


const PunteroF R_tiemeseta6[11]={

			&Principal1.DirProc,
	  	&Principal1.DirProc,	
		  &Principal1.DirProc,
		  &Principal1.DirProc,	
		  &Principal1.DirProc,
		  &Principal1.DirProc,	
		  &Principal1.DirProc,
		  &Vrmp7.DirProc,	
		  &Vrmp7.DirProc,
		  &Vrmp7.DirProc,
		  &Vrmp7.DirProc,
};




 /* Set tiemeseta6*/
/*****************/
const Numerico Tiem6={
      NumHandler,
      &Parametros[R_Tiem6],
			#ifdef MSJ_CORTO
      "tim6",
      #else
			"     tiEMPo MESEtA 6 Min ",
			#endif
			0,
	  	&((int*)BackupArray)[R_ESP],//&PRom[R_ESP],
		  R_tiemeseta6,
		    NULL,
			};
			
    /* Set vrmp7*/
/*****************/
const Numerico Vrmp7={
      NumHandler,
      &Parametros[R_Vrmp7],
      #ifdef MSJ_CORTO
      "Ur 7",
      #else
			"     UEL rAMPA7 <C/Min   ",
			#endif
			1,
			NULL,
			(PunteroF*)&Tmpm7.DirProc,
			};


 /* Set tmeseta7*/
/*****************/
const Numerico Tmpm7={
      NumHandler,
      &Parametros[R_Tmpm7],
			#ifdef MSJ_CORTO
      "<Cm7",
      #else
			"     tEMPEr MESEtA 7 <C  ",
			#endif
			DECIMALES_CANAL1,
			NULL,
			(PunteroF*)&Tiem7.DirProc,
			};


const PunteroF R_tiemeseta7[11]={

			&Principal1.DirProc,
	  	&Principal1.DirProc,	
		  &Principal1.DirProc,
		  &Principal1.DirProc,	
		  &Principal1.DirProc,
		  &Principal1.DirProc,	
		  &Principal1.DirProc,
		  &Principal1.DirProc,	
		  &Vrmp8.DirProc,
		  &Vrmp8.DirProc,
		  &Vrmp8.DirProc,
};




 /* Set tiemeseta7*/
/*****************/
const Numerico Tiem7={
      NumHandler,
      &Parametros[R_Tiem7],
			#ifdef MSJ_CORTO
      "tim7",
      #else
			"     tiEMPo MESEtA 7 Min ",
			#endif
			0,
			&((int*)BackupArray)[R_ESP],//&PRom[R_ESP],
		  R_tiemeseta7,
		    NULL,
			};
			

    /* Set vrmp8*/
/*****************/
const Numerico Vrmp8={
      NumHandler,
      &Parametros[R_Vrmp8],
			#ifdef MSJ_CORTO
      "Ur 8",
      #else
			"     UEL rAMPA8 <C/Min   ",
			#endif
			1,
			NULL,
			(PunteroF*)&Tmpm8.DirProc,
			};


 /* Set tmeseta1*/
/*****************/
const Numerico Tmpm8={
      NumHandler,
      &Parametros[R_Tmpm8],
			#ifdef MSJ_CORTO
      "<Cm8",
      #else
			"     tEMPEr MESEtA 8 <C  ",
			#endif
			DECIMALES_CANAL1,
			NULL,
			(PunteroF*)&Tiem8.DirProc,
			};


const PunteroF R_tiemeseta8[11]={

	  	&Principal1.DirProc,
	  	&Principal1.DirProc,	
		  &Principal1.DirProc,
		  &Principal1.DirProc,	
		  &Principal1.DirProc,
		  &Principal1.DirProc,	
		  &Principal1.DirProc,
		  &Principal1.DirProc,	
		  &Principal1.DirProc,
		  &Vrmp9.DirProc,
		  &Vrmp9.DirProc,
};




 /* Set tiemeseta8*/
/*****************/
const Numerico Tiem8={
      NumHandler,
      &Parametros[R_Tiem8],
			#ifdef MSJ_CORTO
      "tim8",
      #else
			"     tiEMPo MESEtA 8 Min ",
			#endif
			0,
			&((int*)BackupArray)[R_ESP],//&PRom[R_ESP],
		  R_tiemeseta8,
		    NULL,
			};
			

   /* Set vrmp9*/
/*****************/
const Numerico Vrmp9={
      NumHandler,
      &Parametros[R_Vrmp9],
			#ifdef MSJ_CORTO
      "Ur 9",
      #else
			"     UEL rAMPA9 <C/Min   ",
			#endif
			1,
			NULL,
			(PunteroF*)&Tmpm9.DirProc,
			};


 /* Set tmeseta9*/
/*****************/
const Numerico Tmpm9={
      NumHandler,
      &Parametros[R_Tmpm9],
			#ifdef MSJ_CORTO
      "<Cm9",
      #else
			"     tEMPEr MESEtA 9 <C  ",
			#endif
			DECIMALES_CANAL1,
			NULL,
			(PunteroF*)&Tiem9.DirProc,
			};


const PunteroF R_tiemeseta9[11]={

		  &Principal1.DirProc,
		  &Principal1.DirProc,
	  	&Principal1.DirProc,	
		  &Principal1.DirProc,
		  &Principal1.DirProc,	
		  &Principal1.DirProc,
		  &Principal1.DirProc,	
		  &Principal1.DirProc,
		  &Principal1.DirProc,	
		  &Principal1.DirProc,
		  &Vrmp10.DirProc,
};




 /* Set tiemeseta9*/
/*****************/
const Numerico Tiem9={
      NumHandler,
      &Parametros[R_Tiem9],
			#ifdef MSJ_CORTO
      "tim9",
      #else
			"     tiEMPo MESEtA 9 Min ",
			#endif
			0,
			&((int*)BackupArray)[R_ESP],//&PRom[R_ESP],
		  R_tiemeseta9,
		    NULL,
			};
			

   /* Set vrmp10*/
/*****************/
const Numerico Vrmp10={
      NumHandler,
      &Parametros[R_Vrmp10],
			#ifdef MSJ_CORTO
      "Ur10",
      #else
			"     UEL rAMPA10 <C/Min  ",
			#endif
			1,
			NULL,
			(PunteroF*)&Tmpm10.DirProc,
			};


 /* Set tmeseta10*/
/*****************/
const Numerico Tmpm10={
      NumHandler,
      &Parametros[R_Tmpm10],
			#ifdef MSJ_CORTO
      "<Cm0",
      #else
			"     tEMPEr MESEtA 10 <C ",
			#endif
			DECIMALES_CANAL1,
			NULL,
			(PunteroF*)&Tiem10.DirProc,
			};



 /* Set tiemeseta1*/
/*****************/
const Numerico Tiem10={
      NumHandler,
      &Parametros[R_Tiem],
			#ifdef MSJ_CORTO
      "tim0",
      #else
			"     tiEMPo MESEtA 10 Min",
			#endif
			0,
			NULL,
		  (PunteroF*)&Principal1.DirProc,
		    NULL,
			};
			
			
/* Procesador de las pantallas  */
/*****************************************************/
void vitroFusionHandler(void){
char repet=0;


  #ifdef MSJ_CORTO
    char new_text[5];
  
    
    if(VFmod==RMPVF || flag_tecla_up==1){
     
       flag_tecla_up=0;
       
       new_text[0]='r'; 
       new_text[1]='m';
       
       if((EtapaCorr)/10){
          new_text[2]=(EtapaCorr)/10+'0'; 
          new_text[3]=(EtapaCorr)%10+'0';
      } else  { 
          new_text[3]=(EtapaCorr+'0');
          new_text[2]=' ';   
      }
       new_text[4]='\0';
       
       if(resetRamp==0){
         resetRamp=1;
         resetMst=0; 
         PasarASCII("    ",1);   //borro la pantalla una ves
         //ResetScroll();
       }
       
    }else {
       
       new_text[0]='m';
       new_text[1]='S';
       if((EtapaCorr)/10){
          new_text[2]=(EtapaCorr)/10+'0'; 
          new_text[3]=(EtapaCorr)%10+'0';
      } else  {  
          new_text[3]=(EtapaCorr+'0');
          new_text[2]=' '; 
      } 
       
       new_text[4]='\0'; 
         
       if(resetMst==0){
         resetRamp=0;
         resetMst=1;
         //PasarASCII("    ",1);   //borro la pantalla una ves 
         //ResetScroll();
       } 
       
    }
  #elif(defined(VF) && !defined(VF_BKR))
    char new_text[22];
  
    
    if(VFmod==RMPVF || flag_tecla_up==1){
     
       flag_tecla_up=0;
       
       new_text[0]=' '; 
       new_text[1]=' ';
       new_text[2]=' ';
       new_text[3]=' ';
       new_text[4]=' ';
       new_text[5]='r';
       new_text[6]='A';
       new_text[7]='m';
       new_text[8]='P';
       new_text[9]='A';
       if((EtapaCorr)/10){
          new_text[10]=(EtapaCorr)/10+'0'; 
          new_text[11]=(EtapaCorr)%10+'0';
      } else  { 
          new_text[10]=(EtapaCorr+'0');
          new_text[11]=' ';   
      }
       
       new_text[12]=' ';
       new_text[13]=' ';
       new_text[14]=' ';
       new_text[15]=' ';
       new_text[16]=' ';
       new_text[17]=' ';
       new_text[18]=' ';
       new_text[19]=' ';
       new_text[20]=' ';
       new_text[21]='\0';
       
       if(resetRamp==0){
         resetRamp=1;
         resetMst=0; 
         PasarASCII("    ",1);   //borro la pantalla una ves
         ResetScroll();
       }
       
    }else {
       if(rampa_mestaTime>(60*minutos))
         minutos++;
     
       new_text[0]=' ';
       new_text[1]=' ';
       new_text[2]=' ';
       new_text[3]=' ';
       new_text[4]=' ';
       new_text[5]='m';
       new_text[6]='E';
       new_text[7]='S';
       new_text[8]='E';
       new_text[9]='t';
       new_text[10]='A';
       if((EtapaCorr)/10){
          new_text[11]=(EtapaCorr)/10+'0'; 
          new_text[12]=(EtapaCorr)%10+'0';
      } else  {  
          new_text[11]=(EtapaCorr+'0');
          //new_text[7]=' '; 
      } 
         new_text[12]=' ';
       
       if((minutos)/100){
          new_text[13]=(minutos)/100+'0';
          new_text[14]=((minutos)%100)/10+'0'; 
          new_text[15]=(minutos)%10+'0';
          new_text[16]='m';
          new_text[17]='i';
          new_text[18]='n';
          new_text[19]=' ';
          new_text[20]=' ';
          new_text[21]='\0';
       } else if((minutos/10) && (minutos/100) != 1) {
         // new_text[9]=' ';
          new_text[13]=(minutos)/10+'0'; 
          new_text[14]=(minutos)%10+'0';
          new_text[15]='m';
          new_text[16]='i';
          new_text[17]='n';
          new_text[18]=' ';
          new_text[19]=' ';
          new_text[20]=' ';
          new_text[21]='\0';
       }else{
          //new_text[9]=' ';
          //new_text[10]=' ';  
          new_text[13]=(minutos+'0');
          new_text[14]='m';
          new_text[15]='i';
          new_text[16]='n';
          new_text[17]=' ';
          new_text[18]=' ';
          new_text[19]=' ';
          new_text[20]=' ';
          new_text[21]='\0';
       }
       
       
       if(resetMst==0){
         resetRamp=0;
         resetMst=1;
         PasarASCII("    ",1);   //borro la pantalla una ves 
         ResetScroll();
       } 
       
    }
 #elif defined(VF_BKR)
   
    char new_text[22];
  
    
    if(VFmod==RMPVF || flag_tecla_up==1){
     
       flag_tecla_up=0;
       
       new_text[0]=' '; 
       new_text[1]=' ';
       new_text[2]=' ';
       new_text[3]=' ';
       new_text[4]=' ';
       new_text[5]='C';
       new_text[6]='A';
       new_text[7]='L';
       new_text[8]='E';
       new_text[9]='n';
       new_text[10]='t';
       new_text[11]='A';
       new_text[12]='n';
       new_text[13]='d';
       new_text[14]='o';
       new_text[15]=' ';
       new_text[16]=' ';
       new_text[17]=' ';
       new_text[18]=' ';
       new_text[19]=' ';
       new_text[20]=' ';
       new_text[21]='\0';
       
       if(resetRamp==0){
         resetRamp=1;
         resetMst=0; 
         PasarASCII("    ",1);   //borro la pantalla una ves
         ResetScroll();
       }
       
    }else {
       if(rampa_mestaTime>(60*minutos))
         minutos++;
     
       new_text[0]=' ';
       new_text[1]=' ';
       new_text[2]=' ';
       new_text[3]=' ';
       new_text[4]=' ';
       new_text[5]='F';
       new_text[6]='i';
       new_text[7]='n';
       new_text[8]='A';
       new_text[9]='L';
       new_text[10]=' ';
       new_text[11]='E';
       new_text[12]='n';
       new_text[13]=' ';
       
       if((Ti_MES-minutos+1)/100){
          new_text[14]=(Ti_MES-minutos+1)/100+'0';
          new_text[15]=((Ti_MES-minutos+1)%100)/10+'0'; 
          new_text[16]=(Ti_MES-minutos+1)%10+'0';
          new_text[17]=' ';
          new_text[18]='m';
          new_text[19]='i';
          new_text[20]='n';
          new_text[21]='\0';
       } else if(((Ti_MES-minutos+1)/10) && ((Ti_MES-minutos+1)/100) != 1) {
         // new_text[9]=' ';
          new_text[14]=(Ti_MES-minutos+1)/10+'0'; 
          new_text[15]=(Ti_MES-minutos+1)%10+'0';
          new_text[16]=' ';
          new_text[17]='m';
          new_text[18]='i';
          new_text[19]='n';
          new_text[20]=' ';
          new_text[21]='\0';
       }else{
          //new_text[9]=' ';
          //new_text[10]=' ';  
          new_text[14]=((Ti_MES-minutos+1)+'0');
          new_text[15]=' ';
          new_text[16]='m';
          new_text[17]='i';
          new_text[18]='n';
          new_text[19]=' ';
          new_text[20]=' ';
          new_text[21]='\0';
       }
       
       
       if(resetMst==0){
         resetRamp=0;
         resetMst=1;
         PasarASCII("    ",1);   //borro la pantalla una ves 
         ResetScroll();
       } 
       
    }
  #endif 
  #ifdef VF   
    set_MainText(new_text);
  #endif  
    
    //PasarASCII(new_text,1);
  }

/********************Proceso de las teclas(inicio y fin)***************************/



void ProcesoTeclasVF(void){

 CantEtapas = PRom[R_ESP];

if(is_box_principal==1 && flagCartel!=0){
  
/* proceso Tecla UP */  // siempre pone la variable "NroEtapas" en 1 para inicar
#ifdef LLAVES_EXT
	if (Tecla=='u' || !In1_GetVal()){
#else
	 if (Tecla=='u'){
#endif	 
	   tecla_d=0; 
	   EtapaCorr = 1;
	   flag_tecla_up=1;
	   rampa_mestaTime=0;
     VFstatus = RUNVF;
     #ifndef MSJ_CORTO
     PasarASCII("    ",1);   //borro la pantalla una ves 
	   ResetScroll();
	   #endif
	   
  }
	/* proceso Tecla down */ // incrementa la variable "NroEtapas" (si es cero no)
#ifdef LLAVES_EXT	
	if (Tecla=='d' || !In2_GetVal()){
#else
  if (Tecla=='d'){ 
#endif    
	   #ifdef VF_BKR
     if(flagAlarma==TRUE){ // si la alarma esta conectada y se presiona "down" se desconecta
      flagAlarma=FALSE;    // esto es asi solo en el aparato "VF_BKR"
      tecla_d=1;   
     }
     #else
     tecla_d=0;
     #endif
	   
	   if(EtapaCorr!=0 && EtapaCorr<CantEtapas){
	    EtapaCorr++;
	    VFmod=RMPVF;
	    tempActVF = PRom[R_Tmpm1+EtapaCorr-2];
	    rampa_mestaTime=0;
	    minutos=1;
	    flag_tecla_down=1;
	    #ifndef MSJ_CORTO
	    PasarASCII("    ",1);   //borro la pantalla una ves 
	    ResetScroll();
	    #endif
	    
	   }
	   else{
	    tempActVF=0;
	    minutos=1;
	    VFstatus = ENDVF;
	    #ifndef MSJ_CORTO
	    PasarASCII("    ",1);   //borro la pantalla una ves 
	    ResetScroll();
	    #endif
	    
	   }
	}
	}

}

/************************Carteles******************************************/

bool cartelesHandler (){
 
 if(timeCartel<=REP_TIME && flagCartel!=1){
 // flagComCartel=TRUE;
 #ifndef MSJ_CORTO 
  if(unaVez==0){
    PasarASCII("    ",1);   //borro la pantalla una ves
    unaVez=1 ;
  }
 #endif
  flagComCartel=TRUE;
 #ifdef MSJ_CORTO
  set_MainText("Pcom");
 #else 
  set_MainText("    ProGrAmA comPLEto    ");
  //muestraUnaVez ("PrOGrAmA cOmPLEtO");
 #endif
  
  return 0;   
 }else {
   flagComCartel=FALSE;
   timeCartel=0;
   unaVez=0;
   return 1;
 }
}

/**************************************************************************/

void muestraUnaVez (char * msj){
 
 char i,k;
 
 _msj[0]=' ';
 _msj[1]=' ';
 _msj[2]=' ';
 _msj[3]=' ';
// _msj[4]=' ';
 
 if(unaVez==0){
    PasarASCII("    ",1);   //borro la pantalla una ves
    unaVez=1 ;
    unaVuelta=0;
    
  for(i=4,k=0;msj[k]!='\0'&&i<MAX_DIGITOS;i++,k++){
   
    _msj[i]=msj[k];
  
 }    
   cantDig=k;
 }
 
  if(b<cantDig && unaVuelta ==0){
    set_MainText(_msj);
    
  }else{
    unaVuelta=1;
    PasarASCII("    ",1);   //borro la pantalla una ves 
     
  }
} 
