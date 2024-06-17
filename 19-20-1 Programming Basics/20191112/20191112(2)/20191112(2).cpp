#include <iostream>
using namespace std;

long long int count_collatz(long long int k)
{
	int i = 1;
	while (k != 1)
	{
		if (k % 2 == 0)
			k /= 2;
		else
			k = k * 3 + 1;
		i += 1;
	}
	return i;
}

int main()
{
	long long int k, k0, n, max;
	int i;
	cin >> n;
	long long int *a = new long long int [n];
	for (k = 0; k < n; k++)
	{
		k0 = k + 1;
		for (i = 0; k0 % 2 == 0; i++)
			k0 /= 2;
		a[k] = count_collatz(k0) + i;
	}
	max = 0;
	for (k = 0; k < n; k++)
	{
		if (a[k] > max)
			max = a[k];
	}
	cout << max;
}