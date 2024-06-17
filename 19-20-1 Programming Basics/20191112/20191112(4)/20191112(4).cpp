#include <iostream>
using namespace std;

int apples(int m, int n)
{
	if (n == 1)
		return 1;
	else if (m == 0)
		return 1;
	else if (n > m)
		return apples(m, m);
	else
		return apples(m, n - 1) + apples(m - n, n);
}

int main()
{
	int m, n;
	cin >> m >> n;
	cout << apples(m, n);
}