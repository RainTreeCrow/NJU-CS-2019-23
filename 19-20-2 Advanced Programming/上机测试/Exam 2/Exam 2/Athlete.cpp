#include "Athlete.h"

//Athlete��Ĺ��캯������������Ϊname������Ϊnationality�Ķ���
Athlete::Athlete(const char* name, const char* nationality) {
	name_ = name;
	nationailty_ = nationality;
	places_ = NULL;
}

//��Athlete����������˶�Ա���ù��ĳ���
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

//���Athlete�����Ƿ񾭹��ĳ���
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

//����Athlete���������
const char* Athlete::getName() const {
	return name_;
}

//����Athlete����Ĺ���
const char* Athlete::getNationality() const {
	return nationailty_;
}