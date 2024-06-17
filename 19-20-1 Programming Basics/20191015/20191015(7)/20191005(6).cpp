#include <iostream>
using namespace std;

int f(long long int n)
{
	int i = 0;
	while (n != 1)
	{
		if (n % 2 == 0)
			n = n / 2;
		else
			n = 3 * n + 1;
		i += 1;
	}
	return i;
}

int main()
{
	long long int a, b, x, max = 0;
	cin >> a >> b;
	while (a <= b)
	{
		x = f(a);
		a += 1;
		if (x > max)
			max = x;
	}
	cout << max;
	return 0;
}