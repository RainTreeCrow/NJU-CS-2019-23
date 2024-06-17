#include <iostream>
using namespace std;

int main()
{
	float x, x0, x1, x2, ZERO = 1.0e-6;
	int i;
	cin >> x;
	x0 = x * x * x / (3 * 1);
	x1 = x;
	x2 = x - x0;
	i = 1;
	while (x1 - x2 >= ZERO || x2 - x1 >= ZERO)
	{
		x0 = x0 * x * x * (2 * i + 1) / (2 * i + 3) / (i + 1);
		x1 = x2;
		if (i % 2 == 0)
			x2 = x1 - x0;
		else
			x2 = x1 + x0;
		i += 1;
	}
	cout << x2;
}