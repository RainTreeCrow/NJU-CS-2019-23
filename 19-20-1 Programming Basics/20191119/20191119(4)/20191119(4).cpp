#include <iostream>
using namespace std;

int* sort(int x[], int num)
{
	int i, j, temp;
	for (i = num; i > 1; i--)
	{
		for (j = 0; j < i - 1; j++)
		{
			if (x[j] > x[j + 1])
			{
				temp = x[j];
				x[j] = x[j + 1];
				x[j + 1] = temp;
			}
		}
	}
	return x;
}

int main()
{
	int t, i, j, sum;
	int n[100], m[100][100];
	cin >> t;
	for (i = 0; i < t; i++)
	{
		cin >> n[i];
		for (j = 0; j < n[i]; j++)
			cin >> m[i][j];
	}
	for (i = 0; i < t; i++)
	{
		sum = 0;
		for (j = 0; j < n[i]; j++)
			sum += (n[i] - j) * sort(m[i], n[i])[j];
		cout << sum << '\n';
	}
	return 0;
}