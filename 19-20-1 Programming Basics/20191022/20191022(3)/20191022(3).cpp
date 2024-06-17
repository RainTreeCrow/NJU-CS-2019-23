#include <iostream>
using namespace std;

int digit(long n, int k)
{
	int i;
	for (i = 1; i < k; i++)
		n /= 10;
	return n % 10;
}

int main()
{
	long n;
	int k;
	cin >> n >> k;
	cout << digit(n, k);
	return 0;
}