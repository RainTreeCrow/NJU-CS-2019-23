#include "Administrator.h"

//Administrator��Ĺ��캯��
Administrator::Administrator() {
	atheletes_ = new Athlete * [100];
	count = 0;
}

//��Administrator���������һ��Athlete����ָ��
void Administrator::addAthlete(Athlete* athlete) {
	atheletes_[count] = athlete;
	count += 1;
}

//���ݹ�������Athlete����Ĳ�ѯ��,resultList��Athlete����ָ�����飬maxNum����������������������ز�ѯ������������Athlete���������
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

//���ݾ������з���Athlete����Ĳ�ѯ��, resultList��Athlete����ָ�����飬maxNum����������������������ز�ѯ������������Athlete���������
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