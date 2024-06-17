#include <iostream>
#include <cmath>
using namespace std;

int f(int n)
{
	int i, j = 0;
	for (i = 1; i <= sqrt(n); i++)
	{
		if (n % i == 0 && n != i * i)
			j += 2;
		else if (n == i * i)
			j += 1;
	}
	return j;
}


int main()
{
	int n, i, sum;
	cin >> n;
	sum = 0;
	for (i = 1; i <= n; i++)
	{
		if (f(i) % 2 != 0)
			sum++;
	}
	cout << sum;
	return 0;
}