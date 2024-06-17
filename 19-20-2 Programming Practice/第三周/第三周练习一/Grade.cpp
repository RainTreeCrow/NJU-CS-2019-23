#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#pragma warning( disable : 4996 )

struct Student {
	char* name;
	char* id;
	int math;
	int chinese;
	int english;
	int total;
	Student* next;
};

void input_data(Student*& head, Student*& tail) {
	printf("%s\n", "Please input the infomation below into file grade, data!");
	printf("%s\n\n", "End with name's value equal \'E\'");
	printf("%s\n", "Name\tNo\tMath\tChi\tEng");
	char line[100], temp1[5], temp2[5], temp3[5];
	char ch;
	int i1, i2, i3, i4, i5, j, count;
	while (1) {
		count = 0;
		while ((ch = getchar()) != '\n') {
			line[count] = ch;
			count += 1;
		}
		line[count] = '\0';
		if (line[0] == 'E' && line[1] == '\0')
			break;
		Student* stu = new Student;
		stu->name = new char[30];
		stu->id = new char[20];

		j = 0;
		for (i1 = 0; line[i1] != ' '; i1++) {
			stu->name[j] = line[i1];
			j += 1;
		}
		stu->name[j] = '\0';

		j = 0;
		for (i2 = i1 + 1; line[i2] != ' '; i2++) {
			stu->id[j] = line[i2];
			j += 1;
		}
		stu->id[j] = '\0';

		j = 0;
		for (i3 = i2 + 1; line[i3] != ' '; i3++) {
			temp1[j] = line[i3];
			j += 1;
		}
		temp1[j] = '\0';
		stu->math = atoi(temp1);

		j = 0;
		for (i4 = i3 + 1; line[i4] != ' '; i4++) {
			temp2[j] = line[i4];
			j += 1;
		}
		temp2[j] = '\0';
		stu->chinese = atoi(temp2);

		j = 0;
		for (i5 = i4 + 1; line[i5] != '\0'; i5++) {
			temp3[j] = line[i5];
			j += 1;
		}
		temp3[j] = '\0';
		stu->english = atoi(temp3);

		stu->next = NULL;
		if (head == NULL) {
			head = stu;
			tail = stu;
		}
		else {
			tail->next = stu;
			tail = stu;
		}
	}
}

void display_data(Student* head) {
	printf("%s\n", "Name\t\tNo\t\tMath\tChi\tEng");
	for (Student* s = head; s != NULL; s = s->next) {
		if (strlen(s->name) > 6)
			printf("%s\t%s\t%d\t%d\t%d\n", s->name, s->id, s->math, s->chinese, s->english);
		else
			printf("%s\t\t%s\t%d\t%d\t%d\n", s->name, s->id, s->math, s->chinese, s->english);
	}
}

void fill_dat(Student* head) {
	FILE* fp = NULL;
	fp = fopen("./grade.dat", "wb");
	if (fp == NULL) {
		printf("Error! \n");
		exit(-1);
	}
	else
		printf("grade.dat has been created. \n");
	for (Student* s = head; s != NULL; s = s->next) {
		fprintf(fp, "%s %s %d %d %d\n", s->name, s->id, s->math, s->chinese, s->english);
	}
	fclose(fp);
}

void printBinaryFile() {
	printf("%s", "Display students\' information:\n");
	FILE* fp = NULL;
	fp = fopen("./grade.dat", "rb");
	if (fp == NULL) {
		printf("Error! \n");
		exit(-1);
	}
	else
		printf("grade.dat has been opened. \n");
	char line[100];
	for (int i = 0; i < 100; i++)
		line[i] = '\0';
	fgets(line, 99, fp);
	while (!feof(fp)) {
		printf("%s", line);
		fgets(line, 99, fp);

	}
	fclose(fp);
}

void read_dat(Student*& dat_head, Student*& dat_tail) {
	printf("%s", "Construct data and display into screen:\n");
	FILE* fp = NULL;
	fp = fopen("./grade.dat", "rb");
	if (fp == NULL) {
		printf("Error! \n");
		exit(-1);
	}
	else
		printf("grade.dat has been opened. \n");

	char line[100], temp1[5], temp2[5], temp3[5];
	char ch;
	int i1, i2, i3, i4, i5, j, count;
	while (!feof(fp)) {
		count = 0;
		ch = fgetc(fp);
		if (ch == EOF)
			break;
		while (ch != '\n') {
			line[count] = ch;
			count += 1;
		}
		line[count] = '\0';
		if (line[0] == '\0')
			break;
		Student* stu = new Student;
		stu->name = new char[30];
		stu->id = new char[20];

		j = 0;
		for (i1 = 0; line[i1] != ' '; i1++) {
			stu->name[j] = line[i1];
			j += 1;
		}
		stu->name[j] = '\0';

		j = 0;
		for (i2 = i1 + 1; line[i2] != ' '; i2++) {
			stu->id[j] = line[i2];
			j += 1;
		}
		stu->id[j] = '\0';

		j = 0;
		for (i3 = i2 + 1; line[i3] != ' '; i3++) {
			temp1[j] = line[i3];
			j += 1;
		}
		temp1[j] = '\0';
		stu->math = atoi(temp1);

		j = 0;
		for (i4 = i3 + 1; line[i4] != ' '; i4++) {
			temp2[j] = line[i4];
			j += 1;
		}
		temp2[j] = '\0';
		stu->chinese = atoi(temp2);

		j = 0;
		for (i5 = i4 + 1; line[i5] != '\0'; i5++) {
			temp3[j] = line[i5];
			j += 1;
		}
		temp3[j] = '\0';
		stu->english = atoi(temp3);

		stu->next = NULL;
		if (dat_head == NULL) {
			dat_head = stu;
			dat_tail = stu;
		}
		else {
			dat_tail->next = stu;
			dat_tail = stu;
		}
	}
	fclose(fp);
	display_data(dat_head);
}

void sort_data(Student*& head){
	Student* s, * t;
	char* temp_name = new char[30];
	char* temp_id = new char[30];
	int temp_m, temp_c, temp_e, temp_t;
	for (s = head; s != NULL; s = s->next) {
		s->total = s->math + s->chinese + s->english;
	}
	for (s = head; s != NULL; s = s->next) {
		for (t = s->next; t != NULL; t = t->next) {
			if (s->total < t->total) {
				temp_name = s->name;
				s->name = t->name;
				t->name = temp_name;
				temp_id = s->id;
				s->id = t->id;
				t->id = temp_id;
				temp_m = s->math;
				s->math = t->math;
				t->math = temp_m;
				temp_c = s->chinese;
				s->chinese = t->chinese;
				t->chinese = temp_c;
				temp_e = s->english;
				s->english = t->english;
				t->english = temp_e;
				temp_t = s->total;
				s->total = t->total;
				t->total = temp_t;
			}
		}
	}
	FILE* fp = NULL;
	fp = fopen("./grade.txt", "w");
	if (fp == NULL) {
		printf("Error! \n");
		exit(-1);
	}
	else
		printf("Write into the grade_update.txt. \n");
	for (Student* s = head; s != NULL; s = s->next) {
		fprintf(fp, "%s %s %d %d %d %d\n", s->name, s->id, s->math, s->chinese, s->english, s->total);
	}
	fclose(fp);
}

void change_name(Student*& head) {
	printf("%s\n", "Please choose which line you will revise:");
	printf("%s\n", "Please input what name you want to revise:");
	int i;
	char new_name[30];
	scanf("%d", &i);
	scanf("%s", new_name);
	int count = 0;
	Student* s;
	for (s = head; s != NULL; s = s->next) {
		count += 1;
		if (count == i) {
			s->name = new_name;
			break;
		}
	}
	FILE* fp = NULL;
	fp = fopen("./grade.dat", "wb");
	if (fp == NULL) {
		printf("Error! \n");
		exit(-1);
	}
	else
		printf("grade.dat has been created. \n");
	for (Student* s = head; s != NULL; s = s->next) {
		fprintf(fp, "%s %s %d %d %d\n", s->name, s->id, s->math, s->chinese, s->english);
	}
	fclose(fp);
}

int main() {
	Student* head = NULL;
	Student* tail = NULL;
	input_data(head, tail);
	//display_data(head);
	fill_dat(head);
	printBinaryFile();
	sort_data(head);
	change_name(head);
	return 0;
}