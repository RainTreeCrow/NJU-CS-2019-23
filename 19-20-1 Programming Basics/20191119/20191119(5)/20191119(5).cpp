#include <iostream>
using namespace std;

int main()
{
	int n, i, neg = 0, zero = 0, neg_min = -10000001, abs_min = 10000001;
	int m[100];
	cin >> n;
	for (i = 0; i < n; i++)
	{
		cin >> m[i];
		if (m[i] < abs_min)
			abs_min = m[i];
		if (m[i] < 0)
		{
			neg += 1;
			if (m[i] > neg_min)
				neg_min = m[i];
		}	
		else if (m[i] == 0)
			zero += 1;
	}
	if (neg % 2 != 0)
		cout << neg_min;
	else if (zero != 0)
		cout << 0;
	else
		cout << abs_min;
}