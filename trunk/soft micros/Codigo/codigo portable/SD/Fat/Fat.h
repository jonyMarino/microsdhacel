/******************************************************************************
*                                                  
*  (c) copyright Freescale Semiconductor 2008
*  ALL RIGHTS RESERVED
*
*  File Name:   Fat.c
*                                                                          
*  Description: Fat16 lite driver 
*                                                                                     
*  Assembler:   Codewarrior for HC(S)08 V6.1
*                                            
*  Version:     1.1                                                         
*                                                                                                                                                         
*  Author:      Jose Ruiz (SSE Americas)
*                                                                                       
*  Location:    Guadalajara,Mexico                                              
*                                                                                                                  
*                                                  
* UPDATED HISTORY:
*
* REV   YYYY.MM.DD  AUTHOR        DESCRIPTION OF CHANGE
* ---   ----------  ------        --------------------- 
* 1.0   2008.02.18  Jose Ruiz     Initial version
* 1.1   2008.05.02  Jose Ruiz     Initial version
* 
******************************************************************************/                                                                        
/* Freescale  is  not  obligated  to  provide  any  support, upgrades or new */
/* releases  of  the Software. Freescale may make changes to the Software at */
/* any time, without any obligation to notify or provide updated versions of */
/* the  Software  to you. Freescale expressly disclaims any warranty for the */
/* Software.  The  Software is provided as is, without warranty of any kind, */
/* either  express  or  implied,  including, without limitation, the implied */
/* warranties  of  merchantability,  fitness  for  a  particular purpose, or */
/* non-infringement.  You  assume  the entire risk arising out of the use or */
/* performance of the Software, or any systems you design using the software */
/* (if  any).  Nothing  may  be construed as a warranty or representation by */
/* Freescale  that  the  Software  or  any derivative work developed with or */
/* incorporating  the  Software  will  be  free  from  infringement  of  the */
/* intellectual property rights of third parties. In no event will Freescale */
/* be  liable,  whether in contract, tort, or otherwise, for any incidental, */
/* special,  indirect, consequential or punitive damages, including, but not */
/* limited  to,  damages  for  any loss of use, loss of time, inconvenience, */
/* commercial loss, or lost profits, savings, or revenues to the full extent */
/* such  may be disclaimed by law. The Software is not fault tolerant and is */
/* not  designed,  manufactured  or  intended by Freescale for incorporation */
/* into  products intended for use or resale in on-line control equipment in */
/* hazardous, dangerous to life or potentially life-threatening environments */
/* requiring  fail-safe  performance,  such  as  in the operation of nuclear */
/* facilities,  aircraft  navigation  or  communication systems, air traffic */
/* control,  direct  life  support machines or weapons systems, in which the */
/* failure  of  products  could  lead  directly to death, personal injury or */
/* severe  physical  or  environmental  damage  (High  Risk Activities). You */
/* specifically  represent and warrant that you will not use the Software or */
/* any  derivative  work of the Software for High Risk Activities.           */
/* Freescale  and the Freescale logos are registered trademarks of Freescale */
/* Semiconductor Inc.                                                        */ 
/*****************************************************************************/

#ifndef __Fat__
#define __Fat__

/************************* HIL ****************************/
/**********************************************************/
/* Includes */
#include "./SD/SD.h"     // SD Card Driver


/* Storage HIL */
#define GetPhysicalBlock(A,B)       (void)SD_Read_Block(A,B);     
#define StorePhysicalBLock(A,B)     (void)SD_Write_Block(A,B);
/**********************************************************/
/**********************************************************/

/* Macros */
#define ByteSwap(A)     (A=(A<<8)+(A>>8))

/* definitions */
#define MASTER_BLOCK        0x00
#define RootEntrySize       32
#define RHandler_FAT_ENTRIES 8



/*-- Directory Defines --*/
#define FILE_AVAILABLE      0x00
#define FILE_USER           0xFF

#define FILE_Erased         0xE5
#define FILE_Clear          0x00

#define AT_VOLUME           0x01
#define AT_DIRECTORY        0x02
#define AT_HIDDEN           0x04
#define AT_SYSTEM           0x08
#define AT_READONLY         0x10
#define AT_ARCHIVE          0x20


enum 
{
    READ,
    CREATE,
    MODIFY,
    NEXT_ENTRY,
    WRITE_ENTRY
};

enum 
{
    FILE_FOUND,
    FILE_NOT_FOUND,
    FILE_CREATE_OK,
    NO_FILE_ENTRY_AVAILABLE,
    NO_FAT_ENTRY_AVAIlABLE,
    ERROR_IDLE
};


/* typedef */


typedef struct _ReadHandler
{
    VUINT16  FAT_Entry;
    VUINT16  SectorOffset;
    VUINT16  Dir_Entry;
    VUINT32  File_Size;
}ReadRHandler;


typedef struct _WriteRHandler
{
    VUINT8   FileName[8];
    VUINT8   Extension[3];
    VUINT16  Dir_Entry;
    VUINT32  File_Size;
    VUINT16  BaseFatEntry;
    VUINT16  CurrentFatEntry;
    VUINT16  SectorIndex;
    VUINT16  ClusterIndex;
}WriteRHandler;



/* Root Directory Structure */
typedef struct _root_Entries
{
    VUINT8   FileName[8];
    VUINT8   Extension[3];
    VUINT8   Attributes;
    VUINT8   _Case;
    VUINT8   MiliSeconds;
    VUINT16  CreationTime;
    VUINT16  CreationDate;
    VUINT16  AccessDate;
    VUINT16  Reserved;
    VUINT16  ModificationTime;
    VUINT16  ModificationDate;
    VUINT16  ClusterNumber;
    VUINT32  SizeofFile;
}root_Entries;

/* Master Boot Record */
typedef struct _MasterBoot_Entries
{
    VUINT8   JMP_NOP[3];
    VUINT8   OEMName[8];
    VUINT16  BytesPerSector;
    VUINT8   SectorsPerCluster;
    VUINT16  ReservedSectors;
    VUINT8   FatCopies;
    VUINT16  RootDirectoryEntries;
    VUINT16  SectorsLess32MB;
    VUINT8   MediaDescriptor;
    VUINT16  SectorsPerFat;
    VUINT16  SectorsPerTrack;
    VUINT16  NumberOfHeads;
    VUINT32  HiddenSectors;                     
    VUINT32  SectorsInPartition;
    VUINT16  LogicalNumberOfPartitions;
    VUINT8   ExtendedSignature;
    VUINT32  SerialNumber;
    VUINT8   VolumeNumber[11];
    VUINT8   FatName[8];
    VUINT8   ExcecutableCode[448];
    VUINT8   ExcecutableMarker[2];
}MasterBoot_Entries;

/*
void FAT_CreateFATLinks(VUINT16);
void FAT_LS(void);
*/

/* Prototypes */
VUINT32 LWordSwap(VUINT32);
void FAT_FileClose(void);
void FAT_Read_Master_Block(void);
VUINT8 FAT_FileOpen(VUINT8*,VUINT8);
void FAT_FileWrite(VUINT8*,VUINT32);
VUINT16 FAT_FileRead(VUINT8*);
VUINT16 FAT_Entry(VUINT16,VUINT16,VUINT8);
VUINT16 FAT_SearchAvailableFAT(VUINT16);

#endif /* __Fat__ */