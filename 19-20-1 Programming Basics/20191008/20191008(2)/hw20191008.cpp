#include <iostream>
using namespace std;

int main()
{
	int n, i, j, k;
	cin >> n;
	i = 1;
	while (i <= n)
	{
		j = n - i;
		if (j != 0) {
			while (j > 0)
			{
				cout << " ";
				j = j - 1;
			}
		}
		k = 0;
		while (k < i)
		{
			k = k + 1;
			cout << k;
		}
		if (k != 1)
		{
			while (k > 1)
			{
				k = k - 1;
				cout << k;
			}
		}
		cout << "\n";
		i = i + 1;
	}
	return 0;
}