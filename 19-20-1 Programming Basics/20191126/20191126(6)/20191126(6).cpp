#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
	int n, a, b, c;
	cin >> n >> a >> b >> c;
	int* p = new int[1000];
	int mini = min(min(a, b), c), maxi = max(max(a, b), c), mid = a + b + c - mini - maxi;
	if (n % mini == 0) {
		cout << n / mini;
		return 0;
	}
	else {
		int n0 = n, i = 0;
		while (n0 > 0) {
			n0 = n - mid;
			i += 1;
			if (n0 % mini == 0) {
				cout << n0 / mini + i;
				return 0;
			}
		}
		if (n % mid == 0) {
			cout << n / mid;
			return 0;
		}
		else {
			int n0 = n, i = 0;
			while (n0 > 0) {
				n0 = n - maxi;
				i += 1;
				if (n0 % mid == 0) {
					cout << n0 / mid + i;
					return 0;
				}
			}
			if (n % maxi == 0) {
				cout << n / maxi;
				return 0;
			}
		}
	}
}