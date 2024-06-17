#include <iostream>
#include <cassert>
using namespace std;

int other(int n);

int direction(int n)
{
	if (n == 1)
		return 1;
	else
		return direction(n - 1) + other(n - 1);
}

int other(int n)
{
	if (n == 1)
		return 2;
	else
		return direction(n - 1) * 2 + other(n - 1);
}

int main()
{
	int n, m;
	cin >> n;
	assert(n <= 20);
	m = direction(n) + other(n);
	cout << m;
	return 0;
}