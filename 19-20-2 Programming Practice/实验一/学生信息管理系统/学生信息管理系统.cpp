#include <iostream>
#include <fstream>
using namespace std;
#pragma warning(disable : 4996)

char ADMINISTRATOR[20] = "admin";
char ADMIN_PASSWORD[20] = "123456";

struct Course {    //课程
	char id[4];
	char name[30];
	char instrutor[20];
	int size;
	int number;
	char type[10];
	StudentNode* STU;    //学生名单
	TANode* TA;    //助教名单
	Course* next;    //便于构建课程列表
};

struct CourseNode {
	char id[4];
	char name[30];
	char instrutor[20];
	char type[10];
	char tutor[20];
	CourseNode* next;
};

struct StudentNode{
	char id[20];
	StudentNode* next;
};

struct TANode {
	char id[20];
	StudentNode* assist;
	TANode* next;
};

class CourseTable {    //系统课程信息
	Course* head;
	Course* tail;
	friend class Administrator;
	friend class Student;
public:
	CourseTable() {
		head = NULL;
		tail = NULL;
	}
	~CourseTable() {
		for (Course* p = head; p != NULL;) {
			Course* q = p;
			p = p->next;
			delete q;
		}
	}
	void displayTable() {
		cout << "****************************************************************************************" << endl;
		cout << "课程ID\t课程名称\t\t授课教师\t上限人数\t目前已选\t课程类型" << endl;
		for (Course* p = head; p != NULL; p = p->next) {
			cout << p->id << "\t" << p->name << "\t";
			if (strlen(p->name) <= 15)
				cout << "\t" << p->instrutor << "\t\t";
			else
				cout << p->instrutor << "\t\t";
			cout << p->size << "\t\t" << p->number << "\t\t" << p->type << endl;
		}
		cout << "****************************************************************************************" << endl;
	}
	void updateFile() {
		ofstream out("./currentcourse.txt");
		if (out.is_open()) {
			for (Course* p = head; p != NULL; p = p->next) {
				out << p->id << '\t' << p->name << '\t' << p->instrutor << '\t';
				out << p->size << '\t' << p->number << '\t' << p->type << '\n';

			}
			out.close();
		}
	}
};

CourseTable* TABLE = new CourseTable;

class Administrator {
	char id[20];
	char password[20];
	bool login;
	friend class User;
public:
	Administrator() {
		strcpy(id, ADMINISTRATOR);
		strcpy(password, ADMIN_PASSWORD);
		login = false;
	}
	void Menu() {
		cout << endl;
		cout << "============================================================================================" << endl;
		cout << "1.注销登录 2.录入课程信息 3.查看全部课程信息 4.增加课程 5.删除课程 6.修改课程 7.查看具体课程" << endl;
		cout << "============================================================================================" << endl;
		cout << endl;
		cout << "请选择所需的功能：";
		int i;
		cin >> i;
		while (i < 1 || i > 7) {
			cout << "输入不合法，请重新输入！" << endl;
			cout << "请选择所需的功能：";
			cin >> i;
		}
		if (i == 1)
			logOut();
		if (i == 2)
			loadCourse(TABLE);
		if (i == 3)
			displayCourse(TABLE);
		if (i == 4)
			insertCourse(TABLE);
		if (i == 5)
			deleteCourse(TABLE);
		if (i == 6)
			changeCourse(TABLE);
		if (i == 7)
			checkSpecificCourse(TABLE);
	}
	void logOut() {
		login = false;
	}
	void loadCourse(CourseTable*& t) {
		ifstream in("./current_course.txt", ios::in);
		if (in.is_open())
			cout << "请勿重复录入课程信息！" << endl;
		else {
			if (t->head == NULL) {
				L:;
				cout << "请输入需要导入的文件名称：";
				char file[30];
				cin >> file;
				ifstream in(file, ios::in);
				if (!in.is_open()) {
					cout << "找不到课程文件!" << endl;
					goto L;
				}
				else {
					while (!in.eof()) {
						Course* p = new Course;
						in >> p->id;
						p->id[3] = '\0';
						in >> p->name >> p->instrutor >> p->size >> p->number >> p->type;
						p->next = NULL;
						p->STU = NULL;
						p->TA = NULL;
						if (t->head == NULL) {
							t->head = p;
							t->tail = p;
						}
						else {
							t->tail->next = p;
							t->tail = p;
						}
					}
					in.close();
					cout << "导入成功！" << endl;
				}
			}
			else
				cout << "请勿重复录入课程信息！" << endl;
		}
	}
	void displayCourse(CourseTable* t) {
		if (t->head == NULL)
			cout << "还没有录入课程信息！" << endl;
		else
			t->displayTable();
	}
	void insertCourse(CourseTable*& t) {
		cout << "输入课程具体信息(分隔符请用空格)：";
		Course* temp = new Course;
		cin >> temp->name >> temp->instrutor >> temp->size >> temp->number >> temp->type;
		bool exist = false;
		for (Course* p = t->head; p != NULL; p = p->next) {
			if (strcmp(p->name, temp->name) == 0) {
				cout << "课程已存在！";
				exist = true;
				break;
			}
		}
		if (!exist) {
			int i = atoi(t->tail->id) + 1;
			if (i / 100) {
				temp->id[0] = (char)(i / 100 + '0');
				temp->id[1] = (char)((i - (i / 100) * 100) / 10 + '0');
				temp->id[2] = (char)(i % 10 + '0');
			}
			else if (i / 10) {
				temp->id[0] = '0';
				temp->id[1] = (char)(i / 10 + '0');
				temp->id[2] = (char)(i % 10 + '0');
			}
			else {
				temp->id[0] = '0';
				temp->id[1] = '0';
				temp->id[2] = (char)(i % 10 + '0');
			}
			temp->id[3] = '\0';
			temp->next = NULL;
			t->tail->next = temp;
			t->tail = temp;
			cout << "添加成功！" << endl;
			displayCourse(t);
			t->updateFile();
		}
	}
	void deleteCourse(CourseTable*& t) {
		cout << "输入课程编号：";
		char temp_id[4];
		cin >> temp_id;
		bool exist = false;
		Course* p, *q = t->head;
		if (strcmp(t->head->id, temp_id) == 0) {
		    if (t->head->number > 0)
			cout << "课程删除失败，目前已有学生选课！" << endl;
			else {
				p = t->head;
				t->head = t->head->next;
				p->next = NULL;
				delete p;
				cout << "课程删除成功！" << endl;
				displayCourse(t);
				t->updateFile();
			}
		}
		else {
			for (p = t->head; p != NULL; p = p->next) {
				if (strcmp(temp_id, p->id) == 0) {
					exist = true;
					break;
				}
				q = p;
			}
			if (!exist)
				cout << "课程不存在！" << endl;
			else if (p->number > 0)
				cout << "课程删除失败，目前已有学生选课！" << endl;
			else {
				q->next = p->next;
				p->next = NULL;
				delete p;
				cout << "课程删除成功！" << endl;
				displayCourse(t);
				t->updateFile();
			}
		}
	}
	void changeCourse(CourseTable*& t) {
		cout << "需要修改的课程ID：";
		char temp_id[4];
		cin >> temp_id;
		bool exist = false;
		Course* p;
		for (p = t->head; p != NULL; p = p->next) {
			if (strcmp(temp_id, p->id) == 0) {
				exist = true;
				break;
			}
		}
		if (!exist)
			cout << "课程不存在！" << endl;
		else {
			cout << "需要修改的具体字段(1.授课教师 2.容纳人数)：";
			int i;
			cin >> i;
			while (i != 1 && i != 2) {
				cout << "输入不合法，请重新输入！" << endl;
				cout << "输入操作：";
				cin >> i;
			}
			if (i == 1) {
				cout << "具体修改为：";
				char temp_instructor[20];
				cin >> temp_instructor;
				strcpy(p->instrutor, temp_instructor);
				cout << "修改成功！" << endl;
				displayCourse(t);
			}
			if (i == 2) {
				cout << "具体修改为：";
				int temp_size;
				cin >> temp_size;
				if (temp_size < p->number)
					cout << "修改失败！因为修改后的容纳人数小于目前已选人数！" << endl;
				else {
					p->size = temp_size;
					cout << "修改成功！" << endl;
					displayCourse(t);
				}
			}
			t->updateFile();
		}
	}
	void checkSpecificCourse(CourseTable* t) {
		cout << "输入检索方式(1.课程ID 2.课程名称):";
		int i;
		cin >> i;
		while (i != 1 && i != 2) {
			cout << "输入不合法，请重新输入！" << endl;
			cout << "输入检索方式(1.课程ID 2.课程名称):";
			cin >> i;
		}
		bool exist = false;
		Course* p = NULL;
		if (i == 1) {
			cout << "输入需要查看的课程ID：";
			char temp_id[4];
			cin >> temp_id;
			for (p = t->head; p != NULL; p = p->next) {
				if (strcmp(temp_id, p->id) == 0) {
					exist = true;
					break;
				}
			}
		}
		if (i == 2) {
			cout << "输入需要查看的课程名称：";
			char temp_name[30];
			cin >> temp_name;
			for (p = t->head; p != NULL; p = p->next) {
				if (strcmp(temp_name, p->name) == 0) {
					exist = true;
					break;
				}
			}
		}
		if (!exist || p == NULL)
			cout << "课程不存在！" << endl;
		else {
			cout << "========================================================================================" << endl;
			cout << p->id << "\t" << p->name << "\t";
			if (strlen(p->name) <= 15)
				cout << "\t" << p->instrutor << "\t\t";
			else
				cout << p->instrutor << "\t\t";
			cout << p->size << "\t\t" << p->number << "\t\t" << p->type << endl;
			cout << "========================================================================================" << endl;
			cout << "还希望进行以下哪项操作：1.查看选课学生名单 2.查看课程报名助教名单" << endl;
			cout << "输入操作编号：";
			int j;
			cin >> j;
			while (j != 1 && j != 2) {
				cout << "输入不合法，请重新输入！" << endl;
				cout << "输入操作编号：";
				cin >> j;
			}
			if (j == 1) {
				cout << "目前选择该门课的学生有：";
				for (StudentNode* s = p->STU; s != NULL; s = s->next)
					cout << s->id << ',';
				cout << endl;
				cout << "共计" << p->number << "名学生,距离满课还差" << p->size - p->number << "人！" << endl;
			}
			if (j == 2) {
				cout << "目前该门课的报名助教有：";
				for (TANode* s = p->TA; s != NULL; s = s->next)
					cout << s->id << ',';
				cout << endl;
			}
		}
	}
};

class Student {
	char id[20];
	char password[20];
	CourseNode* courses;
	int major;    //专业课数量
	int minor;    //非专业课数量
	int total;
	int beTA;
	bool login;
	Student* next;
	friend class User;
public:
	Student(char* i, char* word) {
		strcpy(id, i);
		strcpy(password, word);
		courses = NULL;
		major = 0;
		minor = 0;
		total = 0;
		beTA = 0;
		login = false;
		next = NULL;
	}
	void Menu() {
		cout << endl;
		cout << "========================================================================================" << endl;
		cout << "  1.注销登录 2.查看课程信息 3.选课 4.查看个人课表 5.退课 6.举手报名助教 7.选择个人助教  " << endl;
		cout << "========================================================================================" << endl;
		cout << endl;
		cout << "请选择所需的功能：";
		int i;
		cin >> i;
		while (i < 1 || i > 7) {
			cout << "输入不合法，请重新输入！" << endl;
			cout << "请选择所需的功能：";
			cin >> i;
		}
		if (i == 1)
			logOut();
		if (i == 2)
			displayCourse(TABLE);
		if (i == 3)
			addCourse(TABLE);
		if (i == 4)
			displayPersonalSchedule();
		if (i == 5)
			dropCourse(TABLE);
		if (i == 6)
			signUpForTA(TABLE);
		if (i == 7)
			selectPersonalTA(TABLE);
	}
	void logOut() {
		login = false;
	}
	void displayCourse(CourseTable* t) {
		if (t->head == NULL)
			cout << "没有可供查看的课程信息！" << endl;
		else
			t->displayTable();
	}
	void addCourse(CourseTable*& t) {
		if (total == 10)
			cout << "课程数量已达到上限！" << endl;
		else {
			cout << "输入课程ID:";
			char temp_id[4];
			cin >> temp_id;
			bool exist = false;
			Course* p = NULL;
			for (p = t->head; p != NULL; p = p->next) {
				if (strcmp(temp_id, p->id) == 0) {
					exist = true;
					break;
				}
			}
			if (!exist)
				cout << "该课程ID不存在！";
			else {
				if (p->number == p->size)
					cout << "选课失败！该课程人数已达到上限！" << endl;
				else {
					CourseNode* temp = new CourseNode;
					strcpy(temp->id, p->id);
					strcpy(temp->name, p->name);
					strcpy(temp->instrutor, p->instrutor);
					strcpy(temp->type, p->type);
					strcpy(temp->tutor, "NULL");
					temp->next = NULL;
					bool exist2 = false;
					if (courses == NULL)
						courses = temp;
					else if (atoi(courses->id) > atoi(temp->id)) {
						temp->next = courses;
						courses = temp;
					}
					else {
						CourseNode* a, * b = courses;
						for (a = courses; a != NULL; a = a->next) {
							if (atoi(a->id) > atoi(temp->id))
								break;
							if (atoi(a->id) == atoi(temp->id)) {
								exist2 = true;
								break;
							}
							b = a;
						}
						if (!exist2) {
							b->next = temp;
							temp->next = a;
						}
					}
					if (exist2)
						cout << "该课程已存在！请勿重复选课！" << endl;
					else {
						total += 1;
						if (strcmp(p->type, "专业课") == 0)
							major += 1;
						else
							minor += 1;
						StudentNode* st = new StudentNode;
						strcpy(st->id, id);
						st->next = p->STU;
						p->STU = st;
						p->number += 1;
						cout << "**************************" << endl;
						cout << "  已经添加到个人课表中！  " << endl;
						cout << "**************************" << endl;
					}
					char file[30];
					int l = strlen(id);
					for (int i = 0; i < l; i++)
						file[i] = id[i];
					file[l] = '.';
					file[l + 1] = 't';
					file[l + 2] = 'x';
					file[l + 3] = 't';
					file[l + 4] = '\0';
					ofstream out(file);
					if (out.is_open()) {
						for (CourseNode* s = courses; s != NULL; s = s->next)
							out << s->id << '\t' << s->tutor << '\n';
					}
					out.close();
					t->updateFile();
				}
			}
		}
	}
	void displayPersonalSchedule() {
		if (courses == NULL) {
			cout << "**********************" << endl;
			cout << "个人课表中还没有课程！" << endl;
			cout << "**********************" << endl;
		}
		else {
			cout << "*************************************************************************" << endl;
			cout << "课程ID\t课程名称\t\t授课教师\t课程类型\t个人助教" << endl;
			for (CourseNode* p = courses; p != NULL; p = p->next) {
				cout << p->id << "\t" << p->name << "\t";
				if (strlen(p->name) <= 15)
					cout << "\t" << p->instrutor << "\t\t";
				else
					cout << p->instrutor << "\t\t";
				if (strlen(p->type) <= 7)
					cout << p->type << "\t\t" << p->tutor << endl;
				else
					cout << p->type << "\t" << p->tutor << endl;
			}
			cout << "*************************************************************************" << endl;
			if (major < 4 || minor < 2) {
				cout << "根据学院要求：目前所选课程数不达标！";
				int x = 4 - major;
				if (x < 0)
					x = 0;
				int y = 2 - minor;
				if (y < 0)
					y = 0;
				cout << "仍差" << x << "门专业课，以及" << y << "门非专业课！请及时选课！" << endl;
			}
		}
	}
	void dropCourse(CourseTable*& t) {
		cout << "输入检索方式(1.课程ID 2.课程名称):";
		int i;
		cin >> i;
		while (i != 1 && i != 2) {
			cout << "输入不合法，请重新输入！" << endl;
			cout << "输入检索方式(1.课程ID 2.课程名称):";
			cin >> i;
		}
		bool exist = false;
		bool first = false;
		CourseNode* p = NULL, * q = courses;
		Course* w = NULL;
		if (i == 1) {
			cout << "输入需要删除的课程ID：";
			char temp_id[4];
			cin >> temp_id;
			if (strcmp(courses->id, temp_id) == 0)
				first = true;
			for (p = courses; p != NULL; p = p->next) {
				if (strcmp(temp_id, p->id) == 0) {
					exist = true;
					break;
				}
				q = p;
			}
			for (w = t->head; w != NULL; w = w->next) {
				if (strcmp(temp_id, w->id) == 0) {
					break;
				}
			}
		}
		if (i == 2) {
			cout << "输入需要查看的课程名称：";
			char temp_name[30];
			cin >> temp_name;
			if (strcmp(courses->name, temp_name) == 0)
				first = true;
			for (p = courses; p != NULL; p = p->next) {
				if (strcmp(temp_name, p->name) == 0) {
					exist = true;
					break;
				}
				q = p;
			}
			for (w = t->head; w != NULL; w = w->next) {
				if (strcmp(temp_name, w->name) == 0) {
					break;
				}
			}
		}
		if (!exist || p == NULL)
			cout << "并未选中该课程！" << endl;
		else {
			total -= 1;
			if (strcmp(p->type, "专业课") == 0)
				major -= 1;
			else
				minor -= 1;
			if (first) {
				p = courses;
				q = NULL;
				courses = courses->next;
				delete p;
			}
			else {
				q->next = p->next;
				p->next = NULL;
				delete p;
			}
			w->number -= 1;
			StudentNode* st, * su = w->STU;
			if (strcmp(w->STU->id, id) == 0) {
				StudentNode* d = w->STU;
				w->STU = w->STU->next;
				delete d;
			}
			else {
				for (st = w->STU; st != NULL; st = st->next) {
					if (strcmp(st->id, id) == 0)
						break;
					su = st;
				}
				su->next = st->next;
				st->next = NULL;
				delete st;
			}
			bool found = false;
			TANode* tt, * tu = w->TA;
			for (tt = w->TA; tt != NULL; tt = tt->next) {
				if (strcmp(tt->id, id) == 0) {
					found = true;
					break;
				}
				tu = tt;
			}
			if (found) {
				tu->next = tt->next;
				tt->next = NULL;
				delete tt->next;
				ofstream out("./assistant.txt");
				if (out.is_open()) {
					for (Course* s = t->head; s != NULL; s = s->next) {
						if (s->TA != NULL) {
							out << s->id << '\t';
							for (TANode* t = s->TA; t->next != NULL; t = t->next)
								out << s->id << ',';
							out << s->id << '\n';
						}
					}
				}
				out.close();
				found = false;
				for (tt = w->TA; tt != NULL; tt = tt->next) {
					if (strcmp(tt->id, id) == 0) {
						found = true;
						break;
					}
					tu = tt;
				}
				if (found) {
					tu->next = tt->next;
					tt->next = NULL;
					delete tt->next;
					ofstream out("./assistant.txt");
					if (out.is_open()) {
						for (Course* s = t->head; s != NULL; s = s->next) {
							if (s->TA != NULL) {
								out << s->id << '\t';
								for (TANode* t = s->TA; t->next != NULL; t = t->next)
									out << s->id << ',';
								out << s->id << '\n';
							}
						}
					}
					out.close();
				}
			}
			cout << "课程删除成功！目前所选的课程有：" << endl;
			displayPersonalSchedule();
			char file[30];
			int l = strlen(id);
			for (int i = 0; i < l; i++)
				file[i] = id[i];
			file[l] = '.';
			file[l + 1] = 't';
			file[l + 2] = 'x';
			file[l + 3] = 't';
			file[l + 4] = '\0';
			ofstream out(file);
			if (out.is_open()) {
				for (CourseNode* s = courses; s != NULL; s = s->next)
					out << s->id << '\t' << s->tutor << '\n';
			}
			out.close();
			t->updateFile();
		}
	}
	void signUpForTA(CourseTable* t) {
		if (beTA >= 2)
			cout << "每人最多只能报名2门课程助教！" << endl;
		else {
			cout << "输入检索方式(1.课程ID 2.课程名称):";
			int i;
			cin >> i;
			while (i != 1 && i != 2) {
				cout << "输入不合法，请重新输入！" << endl;
				cout << "输入检索方式(1.课程ID 2.课程名称):";
				cin >> i;
			}
			bool exist = false;
			CourseNode* p = NULL, * q;
			Course* w = NULL;
			if (i == 1) {
				cout << "输入需要报名的课程ID：";
				char temp_id[4];
				cin >> temp_id;
				for (p = courses; p != NULL; p = p->next) {
					if (strcmp(temp_id, p->id) == 0) {
						exist = true;
						break;
					}
					q = p;
				}
				for (w = t->head; w != NULL; w = w->next) {
					if (strcmp(temp_id, w->id) == 0) {
						break;
					}
				}
			}
			if (i == 2) {
				cout << "输入需要报名的课程名称：";
				char temp_name[30];
				cin >> temp_name;
				for (p = courses; p != NULL; p = p->next) {
					if (strcmp(temp_name, p->name) == 0) {
						exist = true;
						break;
					}
					q = p;
				}
				for (w = t->head; w != NULL; w = w->next) {
					if (strcmp(temp_name, w->name) == 0) {
						break;
					}
				}
			}
			if (!exist || p == NULL)
				cout << "并未选中该课程，不能报名助教！" << endl;
			else {
				beTA += 1;
				TANode* st = new TANode;
				strcpy(st->id, id);
				st->assist = NULL;
				st->next = w->TA;
				w->TA = st;
				cout << "报名助教成功！" << endl;
				ofstream out("./assistant.txt");
				if (out.is_open()) {
					for (Course* s = t->head; s != NULL; s = s->next) {
						if (s->TA != NULL) {
							out << s->id << '\t';
							TANode* ta;
							for (ta = s->TA; ta->next != NULL; ta = ta->next)
								out << ta->id << ',';
							out << ta->id << '\n';
						}
					}
				}
				out.close();
			}
		}
	}
	void selectPersonalTA(CourseTable* t) {;
		cout << "输入检索方式(1.课程ID 2.课程名称):";
		int i;
		cin >> i;
		while (i != 1 && i != 2) {
			cout << "输入不合法，请重新输入！" << endl;
			cout << "输入检索方式(1.课程ID 2.课程名称):";
			cin >> i;
		}
		bool exist = false;
		CourseNode* p = NULL, * q;
		Course* w = NULL;
		if (i == 1) {
			cout << "输入需要选择个人助教的课程ID：";
			char temp_id[4];
			cin >> temp_id;
			for (p = courses; p != NULL; p = p->next) {
				if (strcmp(temp_id, p->id) == 0) {
					exist = true;
					break;
				}
				q = p;
			}
			for (w = t->head; w != NULL; w = w->next) {
				if (strcmp(temp_id, w->id) == 0) {
					break;
				}
			}
		}
		if (i == 2) {
			cout << "输入需要选择个人助教的课程名称：";
			char temp_name[30];
			cin >> temp_name;
			for (p = courses; p != NULL; p = p->next) {
				if (strcmp(temp_name, p->name) == 0) {
					exist = true;
					break;
				}
				q = p;
			}
			for (w = t->head; w != NULL; w = w->next) {
				if (strcmp(temp_name, w->name) == 0) {
					break;
				}
			}
		}
		if (!exist || p == NULL)
			cout << "并未选中该课程，不能选择助教！" << endl;
		else {
			cout << "目前这门课的助教有：";
			TANode* ta;
			for (ta = w->TA; ta != NULL; ta = ta->next)
				cout << ta->id << ',';
			cout << endl;
			cout << "请在上述的助教中，选择你的个人助教：";
			char TAid[20];
			cin >> TAid;
			bool correct = false;
			for (ta = w->TA; ta != NULL; ta = ta->next) {
				if (strcmp(ta->id, TAid) == 0) {
					correct = true;
					break;
				}
			}
			if (correct) {
				if (strcmp(TAid, id) == 0)
					cout << "不能选择自己作为助教！" << endl;
				else {
					strcpy(p->tutor, TAid);
					StudentNode* a = new StudentNode;
					strcpy(a->id, id);
					a->next = ta->assist;
					ta->assist = a;
					cout << "已完成个人助教选择！" << endl;
				}
			}
			else
				cout << "不存在这名助教！" << endl;
			char file[30];
			int l = strlen(id);
			for (int i = 0; i < l; i++)
				file[i] = id[i];
			file[l] = '.';
			file[l + 1] = 't';
			file[l + 2] = 'x';
			file[l + 3] = 't';
			file[l + 4] = '\0';
			ofstream out(file);
			if (out.is_open()) {
				for (CourseNode* s = courses; s != NULL; s = s->next)
					out << s->id << '\t' << s->tutor << '\n';
			}
			out.close();
		}
	}
};

class User {
	Administrator* admin;
	Student* stu;
public:
	User() {
		admin = new Administrator;
		stu = NULL;
	}
	void startUp() {
		cout << "================================================" << endl;
		cout << "  1.学生登录  2.学生注册  3.管理员登录  4.退出  " << endl;
		cout << "================================================" << endl;
		cout << endl;
		cout << "输入操作：";
		int i;
		cin >> i;
		while (i != 1 && i != 2 && i != 3 && i != 4) {
			cout << "输入不合法，请重新输入！" << endl;
			cout << "输入操作：";
			cin >> i;
		}
		if (i == 1)
			studentLogIn();
		if (i == 2)
			studentSignUp();
		if (i == 3)
			adminLogIn();
		if (i == 4)
			exit(0);
	}
	void studentLogIn() {
		cout << "输入学生ID：";
		char id[20];
		cin >> id;
		cout << "输入学生个人密码：";
		char password[20];
		cin >> password;
		Student* p;
		for (p = stu; p != NULL; p = p->next) {
			if (strcmp(id, p->id) == 0)
				break;
		}
		if (p == NULL || strcmp(password, p->password) != 0) {
			cout << "学生ID或密码错误，请重新输入！" << endl;
			startUp();
		}
		else {
			cout << "*************  登陆成功！！ *************" << endl;
			p->login = true;
			while (p->login)
				p->Menu();
			startUp();
		}
	}
	void studentSignUp() {
		cout << "输入学生ID：";
		char id[20];
		cin >> id;
		cout << "输入学生个人密码：";
		char password[20];
		cin >> password;
		Student* p;
		for (p = stu; p != NULL; p = p->next) {
			if (strcmp(id, p->id) == 0)
				break;
		}
		if (p != NULL && strcmp(password, p->password) == 0) {
			cout << "注册失败！该学生ID已经存在！" << endl;
			startUp();
		}
		else {
			Student* temp = new Student(id, password);
			temp->next = stu;
			stu = temp;
			ofstream out2("./student.txt");
			if (out2.is_open()) {
				for (Student* s = stu; s != NULL; s = s->next)
					out2 << s->id << ',' << s->password << '\n';
			}
			out2.close();
			char file[30];
			int l = strlen(id);
			for (int i = 0; i < l; i++)
				file[i] = id[i];
			file[l] = '.';
			file[l + 1] = 't';
			file[l + 2] = 'x';
			file[l + 3] = 't';
			file[l + 4] = '\0';
			ofstream out(file);
			out.close();
			cout << "*********  注册成功！！登陆成功！！ *********" << endl;
			temp->login = true;
			while (temp->login)
				temp->Menu();
			startUp();
		}
	}
	void adminLogIn() {
	L:;
		cout << "输入管理员ID：";
		char id[20];
		cin >> id;
		cout << "输入管理员密码：";
		char password[20];
		cin >> password;
		if (strcmp(id, ADMINISTRATOR) == 0 && strcmp(password, ADMIN_PASSWORD) == 0) {
			cout << "*************  登陆成功！！ *************" << endl;
			admin->login = true;
			while (admin->login)
				admin->Menu();
			startUp();
		}
		else {
			cout << "管理员ID或密码错误，请重新输入！" << endl;
			goto L;
		}
	}
};

int main()
{
	User user;
	user.startUp();
	return 0;
}