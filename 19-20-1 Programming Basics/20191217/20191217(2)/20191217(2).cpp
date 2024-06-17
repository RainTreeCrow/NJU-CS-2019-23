#include <iostream>
using namespace std;

int direction[][2] = { {0, -1}, {-1, 0}, {0, 1}, {1, 0} };

void p(int b[20][20], int x, int y, int n)
{
	int i, x0, y0;
	b[x][y] = -1;
	for (i = 0; i < 4; i++) {
		x0 = x + direction[i][0];
		y0 = y + direction[i][1];
		if (x0 >= 0 && x0 < n && y0 >= 0 && y0 < n && b[x0][y0] == 0)
			p(b, x0, y0, n);
	}
}

int main()
{
	int n, i, j, x, y;
	cin >> n;
	int b[20][20];
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++)
			cin >> b[i][j];
	}
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			if (i == 0 || i == n - 1 || j == 0 || j == n - 1) {
				if (b[i][j] == 0)
					p(b, i, j, n);
			}
		}
	}
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++)
			if (b[i][j] == -1)
				cout << '0' << ' ';
			else
				cout << '1' << ' ';
		cout << '\n';
	}
}