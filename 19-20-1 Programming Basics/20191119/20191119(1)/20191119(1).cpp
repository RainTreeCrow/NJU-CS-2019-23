#include <iostream>
using namespace std;

int mangoes(int m, int n)
{
	if (m == 0)
		return 1;
	else if (n == 1)
		return 1;
	else if (n > m)
		return mangoes(m, m);
	else
		return mangoes(m, n - 1) + mangoes(m - n, n);
}

int main()
{
	int m, n;
	cin >> m >> n;
	cout << mangoes(m, n);
	return 0;
}