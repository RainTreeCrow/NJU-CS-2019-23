#include <iostream>
using namespace std;

int main()
{
	int n, m, x;
	cin >> n;
	x = 0;
	while (n > 0)
	{
		m = n % 10;
		x = x * 10 + m;
		n /= 10;
	}
	cout << x;
	return 0;
}