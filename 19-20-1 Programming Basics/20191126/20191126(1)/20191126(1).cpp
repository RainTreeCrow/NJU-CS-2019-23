#include <iostream>
using namespace std;

int main()
{
	int n, m, i, j, x, max = 0;
	cin >> n >> m;
	int* p = new int[n * m];
	for (i = 0; i < n; i++) {
		for (j = 0; j < m; j++) {
			cin >> p[i * m + j];
		}
	}
		
	for (i = 0; i < n; i++) {
		for (j = 0; j < m - 3; j++) {
			x = p[i * m + j] * p[i * m + j + 1] * p[i * m + j + 2] * p[i * m + j + 3];
			if (x > max)
				max = x;
		}
	}
	for (j = 0; j < m; j++) {
		for (i = 0; i < n - 3; i++) {
			x = p[i * m + j] * p[(i + 1) * m + j] * p[(i + 2) * m + j] * p[(i + 3) * m + j];
			if (x > max)
				max = x;
		}

	}
	for (i = 0; i < n - 3; i++) {
		for (j = 0; j < m - 3; j++) {
			x = p[i * m + j] * p[(i + 1) * m + j + 1] * p[(i + 2) * m + j + 2] * p[(i + 3) * m + j + 3];
			if (x > max)
				max = x;
		}
	}
	for (i = 0; i < n - 3; i++) {
		for (j = n - 1; j > 3; j--) {
			x = p[i * m + j] * p[(i + 1) * m + j - 1] * p[(i + 2) * m + j - 2] * p[(i + 3) * m + j - 3];
			if (x > max)
				max = x;
		}
	}
	cout << max;
	return 0;
}