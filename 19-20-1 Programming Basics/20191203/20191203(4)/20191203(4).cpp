#include <iostream>
using namespace std;

void insert_sort(int x[], int num)
{
	int i, j;
	for (i = 1; i < num; i++) {
		if (x[i] < x[i - 1]) {
			int temp = x[i];
			for (j = i - 1; j >= 0 && x[j] > temp; j--)
				x[j + 1] = x[j];
			x[j + 1] = temp;
		}
	}
}

int main()
{
	int n, total = 0;
	cin >> n;
	int* age = new int[n];
	for (int i = 0; i < n; i++) {
		cin >> age[i];
		total += age[i];
	}
	insert_sort(age, n);
	for (int i = 0; i < n; i++)
		cout << age[i] << ' ';
	cout << '\n';
	cout << total / n << endl;
	return 0;
}