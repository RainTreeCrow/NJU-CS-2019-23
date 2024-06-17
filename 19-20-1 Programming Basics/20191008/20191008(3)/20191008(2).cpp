#include <iostream>
using namespace std;

int main()
{
	int n, a, b, c, d;
	cin >> n;
	a = n / 1000;
	b = (n - a * 1000) / 100;
	c = (n - a * 1000 - b * 100) / 10;
	d = (n - a * 1000 - b * 100 - c * 10);
	if (d % 2 == 0)
	{
		cout << "个位:" << d <<endl;
	}
	if (c % 2 == 0)
	{
		cout << "十位:" << c <<endl;
	}
	if (b % 2 == 0)
	{
		cout << "百位:" << b <<endl;
	}
	if (a % 2 == 0)
	{
		cout << "千位:" << a <<endl;
	}
	return 0;
}
