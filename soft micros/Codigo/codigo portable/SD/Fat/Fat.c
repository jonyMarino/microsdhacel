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

/* Includes */
#include "Fat.h"

/* File Handlers */
WriteRHandler WHandler;
ReadRHandler RHandler;

/* File Buffers */
VUINT8 ag8FATReadBuffer[512];
VUINT8 ag8FATWriteBuffer[512];

/* Global Variables */
VUINT16 u16FAT_Sector_Size;
VUINT16 u16FAT_Cluster_Size;
VUINT16 u16FAT_FAT_BASE;
VUINT16 u16FAT_Root_BASE;
VUINT16 u16FAT_Data_BASE;
VUINT16 u16Main_Offset=0;

/***************************************************************************************/
VUINT32 LWordSwap(VUINT32 u32DataSwap)
{
    VUINT32 u32Temp;
    u32Temp= (u32DataSwap & 0xFF000000) >> 24;
    u32Temp+=(u32DataSwap & 0xFF0000)   >> 8;
    u32Temp+=(u32DataSwap & 0xFF00)     << 8;
    u32Temp+=(u32DataSwap & 0xFF)       << 24;
    return(u32Temp);    
}

/***************************************************************************************/
void FAT_Read_Master_Block(void)
{
    MasterBoot_Entries *pMasterBoot;

    while(ag8FATReadBuffer[0]!= 0xEB && ag8FATReadBuffer[1]!=0x3C && ag8FATReadBuffer[2]!=0x90) 
    {
        GetPhysicalBlock(u16Main_Offset++,&ag8FATReadBuffer[0]);
    }
    u16Main_Offset--;

    pMasterBoot=(MasterBoot_Entries*)ag8FATReadBuffer;
    u16FAT_Cluster_Size=pMasterBoot->SectorsPerCluster;
    u16FAT_Sector_Size=ByteSwap(pMasterBoot->BytesPerSector);
    u16FAT_FAT_BASE=  u16Main_Offset+ByteSwap(pMasterBoot->ReservedSectors);
    u16FAT_Root_BASE= (ByteSwap(pMasterBoot->SectorsPerFat)<<1)+u16FAT_FAT_BASE;
    u16FAT_Data_BASE= (ByteSwap(pMasterBoot->RootDirectoryEntries) >>4)+u16FAT_Root_BASE;
}
/***************************************************************************************/
/*void FAT_LS(void)
{
    VUINT8 u8Counter;
    root_Entries *sFileStructure;                                   

    GetPhysicalBlock(u16FAT_Root_BASE,ag8FATReadBuffer);
    sFileStructure = (root_Entries*)&ag8FATReadBuffer[RootEntrySize];
    while(sFileStructure->FileName[0]!=FILE_Clear)
    {
        if(sFileStructure->FileName[0]!=FILE_Erased)
        {
            Terminal_Send_String((VUINT8*)"\r\n");
            for(u8Counter=0;u8Counter<8;u8Counter++)
                if(sFileStructure->FileName[u8Counter]!=' ')
                    Terminal_Send_Byte(sFileStructure->FileName[u8Counter]);
            Terminal_Send_Byte('.');
            for(u8Counter=0;u8Counter<3;u8Counter++)
                if(sFileStructure->Extension[u8Counter]!=' ')
                    Terminal_Send_Byte(sFileStructure->Extension[u8Counter]);
        }
        sFileStructure++;    
    }
}
*/

/***************************************************************************************/
void FAT_FileClose(void)
{
    root_Entries *sFileStructure;
    VUINT16 *pu16FATPointer;
    VUINT8 u8Counter;
    VUINT32 u32Sector;
    VUINT16 u16Offset;
    
    /* Directory Entry*/
    u32Sector=WHandler.Dir_Entry/(u16FAT_Sector_Size>>5);
    u16Offset=WHandler.Dir_Entry%(u16FAT_Sector_Size>>5);
    
    GetPhysicalBlock(u16FAT_Root_BASE+u32Sector,ag8FATReadBuffer);
    sFileStructure=(root_Entries*)ag8FATReadBuffer;
    sFileStructure+=u16Offset;

    // FileName
    for(u8Counter=0;u8Counter<8;u8Counter++)
        sFileStructure->FileName[u8Counter]=WHandler.FileName[u8Counter];

    // Entension
    for(u8Counter=0;u8Counter<3;u8Counter++)
        sFileStructure->Extension[u8Counter]=WHandler.Extension[u8Counter];


    // Attributes
    sFileStructure->Attributes=0x20;
    sFileStructure->_Case=0x18;
    sFileStructure->MiliSeconds=0xC6;
    
    // Date & Time Information
    sFileStructure->CreationTime=0x2008;
    sFileStructure->CreationDate=0x2136;
    sFileStructure->AccessDate=0x2136;
    sFileStructure->ModificationTime=0x2008;
    sFileStructure->ModificationDate=0x2136;
    
    // Fat entry and file Size
    sFileStructure->ClusterNumber=ByteSwap(WHandler.BaseFatEntry);
    
    sFileStructure->SizeofFile=LWordSwap(WHandler.File_Size); 

    StorePhysicalBLock(u16FAT_Root_BASE+u32Sector,ag8FATReadBuffer)
    
    /* FAT Table */
    u32Sector=WHandler.CurrentFatEntry/(u16FAT_Sector_Size>>1);
    u16Offset=WHandler.CurrentFatEntry%(u16FAT_Sector_Size>>1);

    GetPhysicalBlock(u16FAT_FAT_BASE+u32Sector,ag8FATReadBuffer);
    
    pu16FATPointer=(VUINT16*)ag8FATReadBuffer;
    pu16FATPointer+=u16Offset;
    *pu16FATPointer=0xFFFF;     // Write Final Cluster    

    StorePhysicalBLock(u16FAT_FAT_BASE+u32Sector,ag8FATReadBuffer)
}

/***************************************************************************************/
VUINT16 FAT_SearchAvailableFAT(VUINT16 u16CurrentFAT)
{
    VUINT16 *pu16DataPointer;
    VUINT16 u16FatEntry=0;
    VUINT16 u16Sector=0;
    VUINT16 u16byteSector;
    
    u16Sector=u16FAT_FAT_BASE;
    while(u16Sector < (((u16FAT_Root_BASE-u16FAT_FAT_BASE)>>1)+u16Main_Offset))
    {        GetPhysicalBlock(u16Sector++,ag8FATReadBuffer);
        pu16DataPointer=(VUINT16*)ag8FATReadBuffer;
        u16byteSector=0;
        
        while(u16byteSector<u16FAT_Sector_Size)
        {
            if(*pu16DataPointer==0x0000)
                if(u16FatEntry!=u16CurrentFAT)
                    return(u16FatEntry);
            pu16DataPointer++;
            u16FatEntry++;
            u16byteSector++;
        }
    }
    return(0);  // Return 0 if no more FAT positions available
}

/***************************************************************************************/
VUINT16 FAT_Entry(VUINT16 u16FatEntry,VUINT16 u16FatValue, VUINT8 u8Function)
{
    VUINT16 *pu16DataPointer;
    
    VUINT16 u16Block;
    VUINT8 u8Offset;
    
    u16Block = u16FatEntry / (u16FAT_Sector_Size>>1);
    u8Offset = (VUINT8)(u16FatEntry % (u16FAT_Sector_Size >>1));

    GetPhysicalBlock(u16FAT_FAT_BASE+u16Block,ag8FATReadBuffer);
    pu16DataPointer=(VUINT16*)ag8FATReadBuffer;
    pu16DataPointer+=u8Offset;

    if(u8Function==NEXT_ENTRY)
        return(ByteSwap(*pu16DataPointer));
    
    if(u8Function==WRITE_ENTRY)
    {
        *pu16DataPointer=ByteSwap(u16FatValue);
        StorePhysicalBLock(u16FAT_FAT_BASE+u16Block,ag8FATReadBuffer);
        return(0x00);
    }
                
}

/***************************************************************************************/
void FAT_FileWrite(const VUINT8 *pu8DataPointer,VUINT32 u32Size)
{
    VUINT32 u32SectorToWrite;
    VUINT8 *pu8ArrayPointer;
    VUINT16 u16TempFat;
    VUINT8  u8ChangeSector=1;

    while(u32Size)
    {
        if(u8ChangeSector)
        {
            u32SectorToWrite= u16FAT_Data_BASE + WHandler.ClusterIndex + (WHandler.CurrentFatEntry-2)*u16FAT_Cluster_Size;
            GetPhysicalBlock(u32SectorToWrite,ag8FATWriteBuffer); 
            pu8ArrayPointer=ag8FATWriteBuffer+WHandler.SectorIndex;
            u8ChangeSector=0;
        }
        
        while(WHandler.SectorIndex<u16FAT_Sector_Size  &&  u32Size)
        {
            u32Size--;    
            WHandler.SectorIndex++;
            WHandler.File_Size++;
            *pu8ArrayPointer++=*pu8DataPointer++;    
        }
        
        StorePhysicalBLock(u32SectorToWrite,ag8FATWriteBuffer);     // Write Buffer to Sector
    
        /* Check Sector Size */
        if(WHandler.SectorIndex == u16FAT_Sector_Size)
        {
            WHandler.SectorIndex=0;
            WHandler.ClusterIndex++;    
            u8ChangeSector=1;
        }
    
        /* Check Cluster Size */
        if(WHandler.ClusterIndex == u16FAT_Cluster_Size)
        {
            asm(BGND);
            WHandler.ClusterIndex=0;
            u16TempFat=FAT_SearchAvailableFAT(WHandler.CurrentFatEntry);   
            (void)FAT_Entry(WHandler.CurrentFatEntry,u16TempFat,WRITE_ENTRY);
            WHandler.CurrentFatEntry=u16TempFat;
            u8ChangeSector=1;
        }
    }
}

/***************************************************************************************/
VUINT16 FAT_FileRead(VUINT8 *pu8UserBuffer)
{
    VUINT32 u32SectorToRead; 
    VUINT16 u16BufferSize;

    if(RHandler.File_Size==0)
        return(0);
    
    asm(BGND);
    
    
    u32SectorToRead= u16FAT_Data_BASE + ((RHandler.FAT_Entry-2)*u16FAT_Cluster_Size)+RHandler.SectorOffset;
    GetPhysicalBlock(u32SectorToRead,pu8UserBuffer);
    

    if(RHandler.File_Size > u16FAT_Sector_Size)
    {
        RHandler.File_Size-=u16FAT_Sector_Size;
        u16BufferSize=512;
    }
    else
    {
        u16BufferSize=(VUINT16)RHandler.File_Size;
        RHandler.File_Size=0;
    }
    
    if(RHandler.SectorOffset < (u16FAT_Cluster_Size)-1)
        RHandler.SectorOffset++;        
    else
    {
            RHandler.SectorOffset=0;
            RHandler.FAT_Entry = FAT_Entry(RHandler.FAT_Entry,0,NEXT_ENTRY); // Get Next FAT Entry
    }
    return(u16BufferSize);    
}



/***************************************************************************************/
void FAT_FileNameOrganizer(const VUINT8 *pu8FileName,VUINT8 *pu8Destiny)
{
    VUINT8 u8Counter=0;    
    
    while(u8Counter<12)
    {
        if(*pu8FileName != '.')
            *pu8Destiny++=*pu8FileName++;
        else
        {
            if(u8Counter<8)
                *pu8Destiny++=0x20;
            else
                pu8FileName++;    
        }
        u8Counter++;
    }
}

/***************************************************************************************/
VUINT8 FAT_FileOpen(const VUINT8 *pu8FileName,VUINT8 u8Function)
{
    
    VUINT16 u16Temporal;
    VUINT8  u8FileName[11];
    VUINT8  u8Counter=0;
    VUINT8  u8Flag=FALSE;
    VUINT16 u16Index;
    VUINT16 u16Block;
    VUINT16 u16BlockNum=u16FAT_Data_BASE-u16FAT_Root_BASE;
    VUINT8  u8ErrorCode=ERROR_IDLE;
    VUINT8  *pu8Pointer;
    root_Entries *sFileStructure;                                   
    
    FAT_FileNameOrganizer(pu8FileName,&u8FileName[0]);
    
    u16Block=0;
    
    while(u16Block < u16BlockNum && u8ErrorCode==ERROR_IDLE)
    {
    
        GetPhysicalBlock(u16FAT_Root_BASE+u16Block,ag8FATReadBuffer);
        sFileStructure = (root_Entries*)ag8FATReadBuffer;

        u16Index=0;
        while(u16Index<u16FAT_Sector_Size && u8ErrorCode==ERROR_IDLE)    
        {
            /* If Read or Modify Function */
            if(u8Function==READ || u8Function==MODIFY)
            {
                if(sFileStructure->FileName[0]==FILE_Clear) 
                    u8ErrorCode=FILE_NOT_FOUND;
        
                if(sFileStructure->FileName[0] == u8FileName[0])
                {
                    u8Flag=TRUE;
                    u8Counter=0;
                    while(u8Flag==TRUE && u8Counter < 10)
                    {
                        u8Counter++;
                        if(sFileStructure->FileName[u8Counter] != u8FileName[u8Counter])
                            u8Flag=FALSE;    
                    }
                    if(u8Flag==TRUE)
                    {
                        /* If Read Function */
                        if(u8Function==READ)
                        {
                            RHandler.Dir_Entry=(u16Block*RootEntrySize)+((u16Index)/RootEntrySize);
                            RHandler.File_Size=LWordSwap(sFileStructure->SizeofFile);
                            RHandler.FAT_Entry=ByteSwap(sFileStructure->ClusterNumber);
                            RHandler.SectorOffset=0;
                            u8ErrorCode=FILE_FOUND;
                        } 
                        /* If Modify Function */
                        else
                        {
                            pu8Pointer=WHandler.FileName;
                            for(u8Counter=0;u8Counter<11;u8Counter++)
                                *pu8Pointer++=u8FileName[u8Counter];
                            WHandler.Dir_Entry=(u16Block*RootEntrySize)+((u16Index)/RootEntrySize);
                            WHandler.File_Size=LWordSwap(sFileStructure->SizeofFile);
                            WHandler.BaseFatEntry=ByteSwap(sFileStructure->ClusterNumber);
                            
                            if(WHandler.BaseFatEntry != 0)
                            {
                                u16Temporal=WHandler.BaseFatEntry;
                                do
                                {
                                    WHandler.CurrentFatEntry=WHandler.BaseFatEntry;
                                    WHandler.BaseFatEntry=FAT_Entry(WHandler.CurrentFatEntry,0,NEXT_ENTRY);
                                }while(WHandler.BaseFatEntry!=0xFFFF);
                                WHandler.BaseFatEntry=u16Temporal;
                            } 
                            else
                            {
                                WHandler.BaseFatEntry=FAT_SearchAvailableFAT(0);
                                WHandler.CurrentFatEntry=WHandler.BaseFatEntry;
                            }
                            
                            u16Temporal=(VUINT16)WHandler.File_Size % (u16FAT_Sector_Size<<4);
                            WHandler.ClusterIndex= u16Temporal/u16FAT_Sector_Size;
                            WHandler.SectorIndex=  u16Temporal%u16FAT_Sector_Size;
                            u8ErrorCode=FILE_FOUND;
                        }
                    }
                }
            }

            /* If Write function */
            if(u8Function==CREATE)
            {
                if(sFileStructure->FileName[0]==FILE_Clear || sFileStructure->FileName[0]==FILE_Erased) 
                {
                    
                    pu8Pointer=WHandler.FileName;
                    for(u8Counter=0;u8Counter<11;u8Counter++)
                        *pu8Pointer++=u8FileName[u8Counter];

                    WHandler.Dir_Entry=(u16Block*RootEntrySize)+((u16Index)/RootEntrySize);
                    WHandler.File_Size=0;
                    WHandler.BaseFatEntry=FAT_SearchAvailableFAT(0);
                    WHandler.CurrentFatEntry=WHandler.BaseFatEntry;
                    WHandler.ClusterIndex=0;
                    WHandler.SectorIndex=0;
        
                    if(WHandler.BaseFatEntry)
                        u8ErrorCode=FILE_CREATE_OK;
                    else
                        u8ErrorCode=NO_FAT_ENTRY_AVAIlABLE;
                }
            }
            sFileStructure++;
            u16Index+=RootEntrySize;
        }
        u16Block++;
    }
    if(u16BlockNum==u16Block)
        u8ErrorCode=NO_FILE_ENTRY_AVAILABLE;
    
    return(u8ErrorCode);

}