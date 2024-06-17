#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <asm/types.h>
#include <stddef.h>
#include <unistd.h>

typedef unsigned char u8;		//1B
typedef unsigned short u16;		//2B
typedef unsigned int u32;		//4B

struct BootSector {	
    char BS_jmpBoot [3];    
	char BS_OEMName [8];    
	u16  BPB_BytsPerSec;	// num of bytes per sector
	u8   BPB_SecPerClus;	// num of sector per cluster
	u16  BPB_RsvdSecCnt;	// num of reserved sectors
	u8   BPB_NumFATs;		// num of FAT
	u16  BPB_RootEntCnt;
	u16  BPB_TotSec16;
	u8   BPB_Media;
	u16  BPB_FATSz16;
	u16  BPB_SecPerTrk;
	u16  BPB_NumHeads;
	u32  BPB_HiddSec;
	u32  BPB_TotSec32;
	u8   BS_DrvNum;
	u8   BS_Reserved1;
	u8   BS_BootSig;
	u32  BS_VolID;
	char BS_VolLab [11];
	char BS_FileSysType [8];
	char other [448];
	u16  Overflag;
};

void FormatFile(char * szFileName, int nFileLength) {
	// see if file exists
	if (access(szFileName,0) == 0) {
	    printf("file is exist in this dir");
	    return;
	}
	FILE* fp = fopen(szFileName, "wb+");	// create file
	if(fp == NULL)
		printf("文件打开失败");
	else {	
		struct BootSector bootsector;
		bootsector.BS_jmpBoot[0]=0xEB;
		bootsector.BS_jmpBoot[1]=0x00;
		bootsector.BS_jmpBoot[2]=0x90;
		strcpy(bootsector.BS_OEMName, "mkfs.fat");	
		bootsector.BPB_BytsPerSec = 0x200;
		bootsector.BPB_SecPerClus = 0x01;
		bootsector.BPB_RsvdSecCnt = 0x0001;
		bootsector.BPB_NumFATs = 0x2;
		bootsector.BPB_RootEntCnt = 0x00E0;
		bootsector.BPB_TotSec16 = 0xB40;
		bootsector.BPB_Media = 0xF0;
		bootsector.BPB_FATSz16 =  0x0009;
		bootsector.BPB_SecPerTrk =0x0012;
		bootsector.BPB_NumHeads = 0x0002;
		bootsector.BPB_HiddSec = 0x00000000;
		bootsector.BPB_TotSec32 = 0;
		bootsector.BS_DrvNum = 0;
		bootsector.BS_Reserved1 = 0;	
		bootsector.BS_BootSig = 0x29;
		bootsector.BS_VolID = 0x5a114718;
		strcpy(bootsector.BS_VolLab, "hello world");
		strcpy(bootsector.BS_FileSysType, "FAT12   ");
		bootsector.Overflag = 0xAA55;		
		fwrite(&bootsector.BS_jmpBoot[0],1,1,fp);
		fwrite(&bootsector.BS_jmpBoot[1],1,1,fp);
		fwrite(&bootsector.BS_jmpBoot[2],1,1,fp);
		fwrite(&bootsector.BS_OEMName,8,1,fp);
		fwrite(&bootsector.BPB_BytsPerSec,2,1,fp);
		fwrite(&bootsector.BPB_SecPerClus,1,1,fp);
		fwrite(&bootsector.BPB_RsvdSecCnt,2,1,fp);	
		fwrite(&bootsector.BPB_NumFATs,1,1,fp);
		fwrite(&bootsector.BPB_RootEntCnt,2,1,fp);
		fwrite(&bootsector.BPB_TotSec16,2,1,fp);
		fwrite(&bootsector.BPB_Media,1,1,fp);
		fwrite(&bootsector.BPB_FATSz16,2,1,fp);
		fwrite(&bootsector.BPB_SecPerTrk,2,1,fp);
		fwrite(&bootsector.BPB_NumHeads,2,1,fp);
		fwrite(&bootsector.BPB_HiddSec,4,1,fp);
		fwrite(&bootsector.BPB_TotSec32,4,1,fp);
		fwrite(&bootsector.BS_DrvNum,1,1,fp);
		fwrite(&bootsector.BS_Reserved1,1,1,fp);
		fwrite(&bootsector.BS_BootSig,1,1,fp);	
		fwrite(&bootsector.BS_VolID,4,1,fp);
		fwrite(&bootsector.BS_VolLab,11,1,fp);
		fwrite(&bootsector.BS_FileSysType,8,1,fp);
		fwrite(&bootsector.other,448,1,fp);
		fwrite(&bootsector.Overflag,2,1,fp);
		// move file pointer to specific position	
		fseek(fp, nFileLength-1, SEEK_SET);
		fputc(0, fp);	// put random data at the end
		fclose(fp);
	}
	
}

void testwrite(char* imagefilename, char* srcfilename, char* dstfilename) {
	if (imagefilename == NULL || srcfilename == NULL || dstfilename == NULL) {		
		return ;
	}
	char cmdcreatedir[50];
	sprintf(cmdcreatedir,"mkdir /home/mountdir%s", imagefilename);
	system(cmdcreatedir);
	// mount file
	char cmdname1[50];
	sprintf(cmdname1,"mount %s  /home/mountdir%s", imagefilename, imagefilename);
	system(cmdname1);
	// see if dir exist
	char filename[50];
	sprintf(filename,"/home/mountdir%s%s", imagefilename, dstfilename);
	if (access(filename,0)!=0){
		char cmdname2[50];
		sprintf(cmdname2,"mkdir %s", filename);
	    system(cmdname2);
	}
	// copy the file
	char cmdname3[50];
	sprintf(cmdname3,"cp %s  %s", srcfilename, filename);
	system(cmdname3);
	// unmount file
	char cmdname4[50];	
	sprintf(cmdname4,"umount /home/mountdir%s", imagefilename);
	system(cmdname4);
	char cmdrfdir[50];
	sprintf(cmdrfdir,"rm -rf /home/mountdir%s", imagefilename);
	system(cmdrfdir);
}


void testread(char* imagefilename,char* srcfilename,char* dstfilename) {
	if (imagefilename == NULL || srcfilename == NULL || dstfilename == NULL)
		return;
	char cmdcreatedir[50];
	sprintf(cmdcreatedir,"mkdir /home/mountdir%s", imagefilename);
	system(cmdcreatedir);
	// mount file
	char cmdname1[50];
	sprintf(cmdname1,"mount %s  /home/mountdir%s", imagefilename, imagefilename);
	system(cmdname1);
	char filename[50];
	sprintf(filename,"/home/mountdir%s%s", imagefilename, srcfilename);
	// copy file
	char cmdname2[50];
	sprintf(cmdname2,"cp %s  %s", filename, dstfilename);	
	system(cmdname2);
	// unmount file
	char cmdname3[50];
	sprintf(cmdname3,"umount /home/mountdir%s", imagefilename);		
	system(cmdname3);
	char cmdrfdir[50];
	sprintf(cmdrfdir,"rm -rf /home/mountdir%s", imagefilename);
	system(cmdrfdir);
}

int main(int argc,char* argv[])
{
	char fformat[] = "-f";
	char fread[] = "-mo";
	char fwrite[] = "-mi";	
	if (strcmp(fformat, argv[1]) == 0) {
		FormatFile(argv[2],512*2880);			
	}
	else if (strcmp(fread, argv[1]) == 0) {
		testread(argv[2],argv[3],argv[4]);		
	}
	else if(strcmp(fwrite, argv[1]) == 0) {
		testwrite(argv[2],argv[4],argv[3]);	
	}
	else{		
		printf("Wrong command.\n");
	}	
	return 0;
}
