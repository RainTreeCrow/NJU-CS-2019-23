#include <iostream>
using namespace std;

int main()
{
	int a, b, c, i, j;
	cin >> a >> b;
	i = a / b;
	if (i == 1)
		c = b * 2;
	else
	{
		j = 2;
		while (i % j == 0)
			j += 1;
	}
	c = b * j;
	cout << c;
	return 0;
}