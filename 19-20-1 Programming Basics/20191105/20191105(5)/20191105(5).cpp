#include <iostream>
using namespace std;

int bee(int a, int b)
{
	if (b - a == 1)
		return 1;
	else if (b - a == 2)
		return 2;
	else
		return bee(a, b - 1) + bee(a, b - 2);
}

int main()
{
	int a, b;
	cin >> a >> b;
	cout << bee(a, b);
}