#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
	int n, i, Odd = 0, Even = 0;
	cin >> n;
	int* money = new int[n];
	for (i = 0; i < n; i++) {
		cin >> money[i];
		if (i % 2 == 0) {
			Even += money[i];
			Even = max(Odd, Even);
		}
		else {
			Odd += money[i];
			Odd = max(Odd, Even);
		}
	}
	cout << max(Odd, Even) << endl;
}