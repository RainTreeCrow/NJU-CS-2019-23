#include "Administrator.h"

//Administrator类的构造函数
Administrator::Administrator() {
	atheletes_ = new Athlete * [100];
	count = 0;
}

//向Administrator对象中添加一个Athlete对象指针
void Administrator::addAthlete(Athlete* athlete) {
	atheletes_[count] = athlete;
	count += 1;
}

//根据国籍返回Athlete对象的查询表,resultList是Athlete对象指针数组，maxNum是这个数组的最大容量，返回查询到符合条件的Athlete对象的数量
int Administrator::findAthleteByNationality(const char* nationality, Athlete** resultList, int maxNum) const {
	int i, num = 0;
	for (i = 0; i < count; i++) {
		if (strcmp(atheletes_[i]->getNationality(), nationality) == 0) {
			resultList[num] = atheletes_[i];
			num += 1;
		}
	}
	return num;
}

//根据经过城市返回Athlete对象的查询表, resultList是Athlete对象指针数组，maxNum是这个数组的最大容量，返回查询到符合条件的Athlete对象的数量
int Administrator::findAthleteByVisitedPlace(const char* place, Athlete** resultList, int maxNum) const {
	int i, num = 0;
	for (i = 0; i < maxNum; i++) {
		if (atheletes_[i]->checkVisitedPlace(place)) {
			resultList[num] = atheletes_[i];
			num += 1;
		}
	}
	return num;
}