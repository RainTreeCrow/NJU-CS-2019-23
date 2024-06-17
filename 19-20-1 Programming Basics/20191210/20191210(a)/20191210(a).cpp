#include <iostream>
using namespace std;

int matrix[100][100];

int main()
{
	int m, n, i, j, x, y, s, max = 0;
	cin >> m >> n;
	for (i = 0; i < m; i++) {
		for (j = 0; j < n; j++)
			cin >> matrix[i][j];
	}
	for (i = 0; i < m; i++) {
		for (j = 0; j < n; j++) {
			for (x = i; x < m; x++) {
				for (y = j; y < n; y++) {
					if (matrix[x][y] == 0)
						goto L;
				}
			}
			L: s = (x - i + 1) * (y - j + 1);
			if (s > max)
				max = s;
		}
	}
	cout << max <<endl;
	return 0;
}