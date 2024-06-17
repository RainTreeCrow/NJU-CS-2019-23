#include <iostream>
using namespace std;

int main()
{
	int n, i, j, num = 0;
	cin >> n;
	int (*c)[2] = new int[n * (n - 1)][2];
	for (i = 2; i < n; i++) {
		for (j = 1; j < i; j++) {
			if (j == 1 || i % j != 0) {
				c[num][0] = j;
				c[num][1] = i;
				num += 1;
			}
		}
	}
	cout << ' ' << num <<endl;
	for (i = 0; i < num; i++)
		cout << ' ' << c[i][0] << '/' << c[i][1];
	return 0;
}