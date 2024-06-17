#pragma once
#include "Athlete.h"

class Administrator {
	Athlete** atheletes_;
	int count;
public:
	Administrator();
	void addAthlete(Athlete* athlete);
	int findAthleteByNationality(const char* nationality, Athlete** resultList, int maxNum) const;
	int findAthleteByVisitedPlace(const char* place, Athlete** resultList, int maxNum) const;
};