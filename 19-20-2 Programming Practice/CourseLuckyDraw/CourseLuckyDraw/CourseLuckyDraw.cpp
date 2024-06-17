#include "CourseLuckyDraw.h"

#define STUNO 300
//#define IDSIZE 15



//int transfer(FILE* fs, FILE* fd)
//{
//	if (fs == NULL && fd == NULL) return -1;

//	char stuidarr[STUNO][IDSIZE];
	
//	init(fd);  //set head string "define([" for fd file
	//convert()

//	return 0;
//}

//int setHeadstrToFile(FILE* fd)
//{
//	if (fd == NULL) return -1;
	
//	char str[] = "define([";
//	fputs(str, fd);

//	return 0;
//}

int setStrToFile(FILE* fd, const char* s)
{
	if (fd == NULL) return -1;

//	char str[] = "define([";
	fputs(s, fd);
	fputs("\n", fd);

	return 0;
}