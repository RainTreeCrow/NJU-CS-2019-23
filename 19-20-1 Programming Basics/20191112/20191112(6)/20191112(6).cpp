#include <iostream>
#include <cmath>
using namespace std;

int main()
{
	int i, j, count0 = 0, count1 = 0;
	long long int n;
	cin >> n;
	while (n > 0) {
		if (n % 2 == 0)
			count0 += 1;
		else
			count1 += 1;
		n /= 2;
	}
	cout << abs(count0 - count1);
	return 0;
}