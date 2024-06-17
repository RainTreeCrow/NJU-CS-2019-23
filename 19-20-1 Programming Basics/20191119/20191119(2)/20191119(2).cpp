#include <iostream>
using namespace std;

int d(int n)
{
	int i, sum = 1;
	for (i = 2; i * i <= n; i++)
	{
		if (n == i * i)
			sum += i;
		else if (n % i == 0)
			sum = sum + i + n / i;
	}
	return sum;
}

int main()
{
	int N, i, k = 0;
	cin >> N;
	for (i = 1; i <= N; i++)
	{
		if (d(d(i)) == i && d(i) != i)
			k += i;
	}
	cout << k;
	return 0;
}