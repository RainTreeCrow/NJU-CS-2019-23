#include <iostream>
using namespace std;

int fun(int m, int k)
{
	int n, i, j, x;
	n = m, x = 0;
	for (i = 0; m >= 1; i++)
	{
		n = m % k;
		for (j = i; j > 0; j--)
			n *= 10;
		x = x + n;
		m /= k;
	}
	return x;
}

int main()
{
	int m, k;
	cin >> m >> k;
	cout << fun(m, k);
	return 0;
}