#include <iostream>
using namespace std;

int main()
{
	int k, * a;
	cin >> k;
	int left = k, num = 0;
	a = new int[k];
	for (int i = 0; i < k; i++)
		a[i] = 1;
	while (left > 1)
	{
		for (int i = 0; i < k; i++)
		{	
			if (a[i] == 1)
				num += 1;
			if (num == 3)
			{
				a[i] = 0;
				num = 0;
				left -= 1;
			}
		}
	}
	for (int i = 0; i < k; i++)
	{
		if (a[i] == 1)
			cout << i + 1;
	}
}