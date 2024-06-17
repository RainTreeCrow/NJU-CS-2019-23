#include <iostream>
using namespace std;

int main()
{
	long long int n, m, i, max = 2;
	int j;
	cin >> n;
	while (n > 2 && n % 2 == 0)
		n /= 2;
	if (n > 2)
	{
		for (m = 3; m <= n; m += 2)
		{
			if (n % m == 0)
			{
				j = 0;
				for (i = 3; i * i <= m; i += 2)
				{
					if (m % i == 0)
					{
						j = 1;
						break;
					}
				}
				if (j == 0)
					max = m;
			}
		}
	}
	cout << max;
}