#include <iostream>
using namespace std;

int main()
{
	int n, a, b, c, i;
	cin >> n;
	a = n % 10, b = n;
	while (n >9)
	{
		a = n % 10, b = n, i = 1;
		do
		{
			b = b / 10;
			i = i + 1;
		} while (b > 9);
		c = b;
		do
		{
			c = c * 10;
			i = i - 1;
		} while (i > 1);
		n = (n - c) / 10;
		if (a != b) break;
	}
	if (a == b)
	{
		cout << "YES" << endl;
	}
	else
	{
		cout << "NO" << endl;
	}
	return 0;
}