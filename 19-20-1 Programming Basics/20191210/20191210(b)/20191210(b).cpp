#include <iostream>
using namespace std;

struct Student {
	int id;
	char name[20];
	int score[3];
	int all;
};

int join(Student* A, int N, Student* B, int M, Student* ALL) {
	int i, j, l, sum, k = N;
	for (i = 0; i < N; i++) {
		ALL[i] = A[i];
		sum = 0;
		for (int l = 0; l < 3; l++)
			sum += ALL[i].score[l];
		ALL[i].all = sum;
	}
	for (j = 0; j < M; j++) {
		bool notin = true;
		for (i = 0; i < N; i++) {
			if (A[i].id == B[j].id)
				notin = false;
		}
		if (notin) {
			ALL[k] = B[j];
			sum = 0;
			for (l = 0; l < 3; l++)
				sum += ALL[k].score[l];
			ALL[k].all = sum;
			k += 1;
		}
	}
	int s = k;
	return s;
}

void sort(Student* ALL, int S) {
	int i, j;
	for (i = 0; i < S; i++) {
		for (j = 0; j < S - i - 1; j++) {
			if (ALL[j].all < ALL[j + 1].all || (ALL[j].all == ALL[j + 1].all && ALL[j].id > ALL[j + 1].id)) {
				Student temp = ALL[j + 1];
				ALL[j + 1] = ALL[j];
				ALL[j] = temp;
			}
		}
	}
}

void display(Student* ALL, int S) {
	for (int i = 0; i < S; i++) {
		cout << ALL[i].id << ' ' << ALL[i].name << ' ';
		for (int j = 0; j < 3; j++)
			cout << ALL[i].score[j] << ' ';
		cout << ALL[i].all << endl;
	}
}

int main()
{
	int n, m, i, j;
	cin >> n >> m;
	Student *A = new Student[n];
	Student *B = new Student[m];
	Student* ALL = new Student[m + n];
	for (i = 0; i < n; i++) {
		cin >> A[i].id >> A[i].name;
		for (j = 0; j < 3; j++)
			cin >> A[i].score[j];
	}
	for (i = 0; i < m; i++) {
		cin >> B[i].id >> B[i].name;
		for (j = 0; j < 3; j++)
			cin >> B[i].score[j];
	}
	int S = join(A, n, B, m, ALL);
	sort(ALL, S);
	display(ALL, S);
	return 0;
}