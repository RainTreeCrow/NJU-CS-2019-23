#include <iostream>
using namespace std;

int main()
{
	int m, n, i, num = 0;
	cin >> m >> n;
	for (i = m; i <= n; i++)
	{
		if (i % 4 == 0 && i % 100 != 0)
			num += 1;
		else if (i % 400 == 0)
			num += 1;
	}
	cout << num;
}