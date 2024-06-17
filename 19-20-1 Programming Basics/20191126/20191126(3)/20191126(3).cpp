#include <iostream>
using namespace std;

int* Min(const int a[], int num)
{
	int min = a[0], min_index = 0;
	for (int i = 0; i < num; i++) {
		if (a[i] < min) {
			min = a[i];
			min_index = i;
		}
	}
	int* p = new int[num];
	for (int i = 0; i < num; i++)
		p[i] = a[i];
	p[min_index] = 0;
	return p;
}

int main()
{
	int *a = new int[1000];
	int n = 0;
	for(int i = 0; ; i++){
		cin >> a[i];
		if (a[i] == -1)
			break;
		n += 1;
	}
	int* b = Min(a, n);
	for (int j = 0; j < n; j++) {
		cout << b[j] << ' ';
	}
	return 0;
}