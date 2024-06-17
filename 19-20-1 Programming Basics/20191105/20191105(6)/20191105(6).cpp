#include <iostream>
using namespace std;

bool lucky(int n)
{
	int i, j, k;
	k = 0;
	for (i = n; i > 0; i /= 10)
	{
		j = i % 10;
		if (j != 4 && j != 7)
		{
			k = 1;
			break;
		}
	}
	if (k == 1)
		return false;
	else
		return true;
}

int main()
{
	int n, x, y;
	cin >> n;
	if (lucky(n))
		cout << "YES";
	else
	{
		y = 0;
		for (x = 2; x < n; x++)
		{
			if (n % x == 0)
			{
				if (lucky(n / x))
				{
					y = 1;
					break;
				}
			}
		}
		if (y == 1)
			cout << "YES";
		else
			cout << "NO";
		return 0;
	}
}