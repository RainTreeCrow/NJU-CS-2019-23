#include <iostream>
#include <cstring>
#include "Athlete.h"
#include "Athlete.cpp"
#include "Administrator.h"
#include "Administrator.cpp"
#pragma warning( disable : 4996 )
using namespace std;

int main()
{
	Athlete* athlete = new Athlete("James", "America"); //创建一个Athlete对象，名字为"James"，国籍为"America"
	athlete->addVisitedPlace("Tokyo"); //登记James曾前往过Tokyo
	athlete->addVisitedPlace("Washington"); //登记James曾前往过Washington
	cout << athlete->getName() << ' '; //获取James的名字
	cout << athlete->getNationality() << ' '; //获取James的国籍
	bool check = athlete->checkVisitedPlace("Tokyo"); //检查James是否曾前往过Tokyo
	cout << check << endl;
	Administrator* admin = new Administrator();//创建一个Administrator对象
	admin->addAthlete(athlete);//将athlete登记到admin中
	const int MAXATH = 100;
	Athlete* resultList[MAXATH];//创建Athlete对象指针数组
	int resultNum = admin->findAthleteByNationality("America", resultList, MAXATH);//查询国籍是"America"的运动员
	for (int i = 0; i < resultNum; ++i) {
		cout << resultList[i]->getName() << endl;//输出上述查找到的运动员的姓名
	}
	return 0;
}