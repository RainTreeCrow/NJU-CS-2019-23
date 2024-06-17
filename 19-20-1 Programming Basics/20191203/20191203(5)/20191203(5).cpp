#include <iostream>
using namespace std;

struct Student
{
	char number[20];
	char name[20];
	float english;
	float math;
	float computer;
};

int main()
{
	Student s[5];
	float english = 0, math = 0, computer = 0, max_score = 0, score = 0;
	int max_index = 0;
	for (int i = 0; i < 5; i++) {
		cin >> s[i].number >> s[i].name >> s[i].english >> s[i].math >> s[i].computer;
		english += s[i].english;
		math += s[i].math;
		computer += s[i].computer;
		score = (s[i].english + s[i].math + s[i].computer) / 3;
		if (score > max_score) {
			max_score = score;
			max_index = i;
		}
	}
	cout << english / 5 << ' ' << math / 5 << ' ' << computer / 5 << '\n';
	cout << s[max_index].number << ' ';
	cout << s[max_index].name << ' ';
	cout << s[max_index].english << ' ';
	cout << s[max_index].math << ' ';
	cout << s[max_index].computer << ' ';
	cout << max_score << endl;
	return 0;
}