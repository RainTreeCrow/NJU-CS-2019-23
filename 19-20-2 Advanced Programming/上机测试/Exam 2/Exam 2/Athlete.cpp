#include "Athlete.h"

//Athlete类的构造函数，创建名字为name，国籍为nationality的对象
Athlete::Athlete(const char* name, const char* nationality) {
	name_ = name;
	nationailty_ = nationality;
	places_ = NULL;
}

//向Athlete对象中添加运动员到访过的城市
void Athlete::addVisitedPlace(const char* place) {
	Place_node* p = new Place_node;
	p->place_name = place;
	p->next = NULL;
	if (places_ == NULL)
		places_ = p;
	else {
		p->next = places_;
		places_ = p;
	}
}

//检查Athlete对象是否经过的城市
bool Athlete::checkVisitedPlace(const char* place) const {
	int i;
	bool visited = false;
	for (Place_node* p = places_; p != NULL; p = p->next) {
		for (i = 0; p->place_name[i] != '\0' && place[i] != '\0'; i++) {
			if (p->place_name[i] != place[i])
				break;
		}
		if (p->place_name[i] == '\0' && place[i] == '\0') {
			visited = true;
			break;
		}
	}
	return visited;
}

//返回Athlete对象的名字
const char* Athlete::getName() const {
	return name_;
}

//返回Athlete对象的国籍
const char* Athlete::getNationality() const {
	return nationailty_;
}