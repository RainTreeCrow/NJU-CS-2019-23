#include <iostream>
using namespace std;

bool Ascending(int a, int b)
{
	if (a > b)
		return true;
	else
		return false;
}

bool Descending(int a, int b)
{
	if (a < b)
		return true;
	else
		return false;
}

void Sort(int d[], int n, bool (*compr)(int x, int y))
{
	int i, j;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n - i - 1; j++)
			if ((*compr)(d[j], d[j + 1])) {
				int temp = d[j];
				d[j] = d[j + 1];
				d[j + 1] = temp;
			}
	}
}

int main()
{
	int n, i;
	cin >> n;
	int* l = new int[n];
	for (i = 0; i < n; i++)
		cin >> l[i];
	Sort(l, n, Ascending);
	for (i = 0; i < n; i++)
		cout << ' ' << l[i];
	cout << '\n';
	Sort(l, n, Descending);
	for (i = 0; i < n; i++)
		cout << ' ' << l[i];
	return 0;
}