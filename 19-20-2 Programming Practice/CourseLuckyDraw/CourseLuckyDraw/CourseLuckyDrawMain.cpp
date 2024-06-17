#pragma warning(disable : 4996)

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "CourseLuckyDraw.h"

#define FILEOPFAIL -1
#define FILEOPSUCCESS 0

int main()
{
	FILE* fps, *fpd;
	const char strHead[] = "define([";
	const char strTail[] = "])";
	
	char strStuID[IDSIZE];
	char strRtn[2];
	char strStuBuffer[IDSIZE + 3];
	char stuIDSArr[IDARRSIZE][IDSIZE];
	char stuIDDArr[IDARRSIZE][IDSIZE];

	fps = fopen("../html5-luckydraw-benke-2020/UndergraduateSTUID.txt", "r");
	if (fps == NULL)
	{
		printf("File open failed\n");
		return 0;
	}
	fpd = fopen("../html5-luckydraw-benke-2020/boys-and-girls.js", "w");
	if (fpd == NULL)
	{
		printf("File open failed\n");
		return 0;
	}


	//set string to file head
	if (setStrToFile(fpd, strHead) == FILEOPFAIL)
	{
		printf("File operator failed\n");
		return 0;
	}
	else
		printf("String %s is inserted into FILE head\n", strHead);
	
	//read StuID array from File
	int count = 0;

//	while (fgets(strStuID, sizeof(strStuID)+1, fps))
//	{
		//stuIDArr[count] = new char[sizeof(strStuID) + 1];
		//stuIDArr[count] = (char*)malloc(sizeof(strStuID)+1);
//		strcpy(stuIDSArr[count], strStuID);

//		printf("%s\n", stuIDSArr[count]);

//		count++;
//	}
//	printf("count=%d\n", count);

	
	while (!feof(fps))
	{
		memset(strStuID, 0, sizeof(strStuID));
		fgets(strStuID, sizeof(strStuID), fps); // °üº¬ÁË\n
		strcpy(stuIDSArr[count], strStuID);
		
		printf("%s\n", stuIDSArr[count]);
		
		fgets(strRtn, sizeof(strRtn), fps);
		count++;
		//printf("%s", strStuID);
	}
	printf("count=%d\n", count);

	//for(int i=0; i<)

	//write stuID array to File
	for (int i = 0; i < count; i++)
	{
		strStuBuffer[0] = '\"';
		strcpy((strStuBuffer + 1), stuIDSArr[i]);
		strcat(strStuBuffer, "\",");

		printf("strStuBuffer is %s\n", strStuBuffer);
	
		strcpy(stuIDDArr[i], strStuBuffer);
		fputs(stuIDDArr[i], fpd);
		fputs("\n", fpd);

	}

	
	//transfer StuID string to "StuID", string


	//set string to file tail
	if (setStrToFile(fpd, strTail) == FILEOPFAIL)
	{
		printf("File operator failed\n");
		return 0;
	}
	else
		printf("String % s is inserted into FILE tail\n", strTail);


	//transfer(fps, fpd);
	//char** str;

	fclose(fps);
	fclose(fpd);
	
		
	return 0;
}