#pragma once

struct Place_node {
	const char* place_name;
	Place_node* next;
};

class Athlete {
	const char* name_;
	const char* nationailty_;
	Place_node* places_;
	friend class Administrator;
public:
	Athlete(const char* name, const char* nationality);
	void addVisitedPlace(const char* place);
	bool checkVisitedPlace(const char* place) const;
	const char* getName() const;
	const char* getNationality() const;
};