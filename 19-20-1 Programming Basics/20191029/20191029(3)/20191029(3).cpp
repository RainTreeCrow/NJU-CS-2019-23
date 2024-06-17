#include <iostream>
using namespace std;

double newton_sqrt(double a)
{
	double x, update_x;
	x = 1;
	float ε = 1.0e-8;
	update_x = (x + a / x) / 2;
	while ((update_x - x) / x >= ε || (update_x - x) / x <= -ε)
	{
		x = update_x;
		update_x = (x + a / x) / 2;
	}
	return x;
}

int main()
{
	double x;
	cin >> x;
	cout << newton_sqrt(x);
	return 0;
}