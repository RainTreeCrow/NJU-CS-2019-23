#include <iostream>
#include <cmath>
using namespace std;

void CalArea(double a, double b, double c)
{
	double p, s;
	p = (a + b + c) / 2;
	s = sqrt(p * (p - a) * (p - b) * (p - c));
	cout << s;
}

int main()
{
	double a, b, c;
	cin >> a >> b >> c;
	CalArea(a, b, c);
	return 0;
}